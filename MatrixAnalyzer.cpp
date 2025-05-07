#include "MatrixAnalyzer.h"

MatrixAnalyzer::MatrixAnalyzer(const Circuit& circuit)
    : circuit(circuit) {}

void MatrixAnalyzer::buildDCMatrix() {
    int numNodes = circuit.getNodes().size() - 1;  // Ground is node 0
    int numVoltageSources = circuit.getVoltageSources().size();
    int matrixSize = numNodes + numVoltageSources;

    G.resize(numNodes, numNodes);
    B.resize(numNodes, numVoltageSources);
    C.resize(numVoltageSources, numNodes);
    D.resize(numVoltageSources, numVoltageSources);
    J.resize(numNodes);
    E.resize(numVoltageSources);

    G.setZero();
    B.setZero();
    C.setZero();
    D.setZero();
    J.setZero();
    E.setZero();

    for (const auto& resistor : circuit.getResistors()) {
        int n1 = resistor->getNode1();
        int n2 = resistor->getNode2();
        double g = 1.0 / resistor->getValue();

        if (n1 != 0) G(n1 - 1, n1 - 1) += g;
        if (n2 != 0) G(n2 - 1, n2 - 1) += g;
        if (n1 != 0 && n2 != 0) {
            G(n1 - 1, n2 - 1) -= g;
            G(n2 - 1, n1 - 1) -= g;
        }
    }

    for (int i = 0; i < numVoltageSources; ++i) {
        const auto& vs = circuit.getVoltageSources()[i];
        int n1 = vs->getNode1();
        int n2 = vs->getNode2();

        if (n1 != 0) {
            B(n1 - 1, i) = 1;
            C(i, n1 - 1) = 1;
        }
        if (n2 != 0) {
            B(n2 - 1, i) = -1;
            C(i, n2 - 1) = -1;
        }

        E(i) = vs->getValue();
    }

    for (const auto& cs : circuit.getCurrentSources()) {
        int n1 = cs->getNode1();
        int n2 = cs->getNode2();
        double current = cs->getValue();

        if (n1 != 0) J(n1 - 1) -= current;
        if (n2 != 0) J(n2 - 1) += current;
    }

    combineMNAMatrix();
}

void MatrixAnalyzer::combineMNAMatrix() {
    int numNodes = G.rows();
    int numVS = E.size();

    A.resize(numNodes + numVS, numNodes + numVS);
    z.resize(numNodes + numVS);

    A.block(0, 0, numNodes, numNodes) = G;
    A.block(0, numNodes, numNodes, numVS) = B;
    A.block(numNodes, 0, numVS, numNodes) = C;
    A.block(numNodes, numNodes, numVS, numVS) = D;

    z.head(numNodes) = J;
    z.tail(numVS) = E;
}

void MatrixAnalyzer::solveDC() {
    Eigen::VectorXd solution = A.fullPivLu().solve(z);

    int numNodes = circuit.getNodes().size() - 1;
    nodeVoltages = solution.head(numNodes);
    voltageSourceCurrents = solution.tail(solution.size() - numNodes);
}

void MatrixAnalyzer::printSolution() const {
    std::cout << "DC Solution:" << std::endl;

    std::cout << "Node Voltages:" << std::endl;
    for (int i = 0; i < nodeVoltages.size(); ++i) {
        std::cout << "Node " << (i + 1) << ": " << nodeVoltages(i) << " V" << std::endl;
    }

    if (!voltageSourceCurrents.empty()) {
        std::cout << "Voltage Source Currents:" << std::endl;
        for (int i = 0; i < voltageSourceCurrents.size(); ++i) {
            std::cout << circuit.getVoltageSources()[i]->getName() << ": "
                      << voltageSourceCurrents(i) << " A" << std::endl;
        }
    }
}

void buildTransientMatrix(double timeStep) {
    MatrixAnalyzer::buildDCMatrix(); // Start with DC matrix

    // Add capacitor contributions
    for (const auto& capacitor : circuit.getCapacitors()) {
        int n1 = capacitor->getNode1();
        int n2 = capacitor->getNode2();
        double conductance = capacitor->getValue() / timeStep;

        if (n1 != 0) {
            G(n1-1, n1-1) += conductance;
        }
        if (n2 != 0) {
            G(n2-1, n2-1) += conductance;
        }
        if (n1 != 0 && n2 != 0) {
            G(n1-1, n2-1) -= conductance;
            G(n2-1, n1-1) -= conductance;
        }

        // Add contribution to J vector from previous time step
        // (This would require storing previous voltages)
    }

    // Add inductor contributions similarly

    combineMNAMatrix();
}

void solveTransient(double timeStep, double totalTime) {
    int steps = static_cast<int>(totalTime / timeStep);

    // Initialize previous voltages (would need to store these)

    for (int step = 0; step < steps; ++step) {
        buildTransientMatrix(timeStep);
        solveDC();

        // Update previous voltages for next step
        // ...
    }
}

void MatrixAnalyzer::buildTransientMatrix(double timeStep) {
    buildDCMatrix(); // Start with DC matrix

    // Add capacitor contributions
    for (const auto& capacitor : circuit.getCapacitors()) {
        int n1 = capacitor->getNode1();
        int n2 = capacitor->getNode2();
        double g = capacitor->getValue() / timeStep;

        if (n1 != 0) {
            G(n1-1, n1-1) += g;
            J(n1-1) += g * prevNodeVoltages(n1-1);
        }
        if (n2 != 0) {
            G(n2-1, n2-1) += g;
            J(n2-1) += g * prevNodeVoltages(n2-1);
        }
        if (n1 != 0 && n2 != 0) {
            G(n1-1, n2-1) -= g;
            G(n2-1, n1-1) -= g;
            J(n1-1) -= g * prevNodeVoltages(n2-1);
            J(n2-1) -= g * prevNodeVoltages(n1-1);
        }
    }

    combineMNAMatrix();
}

void MatrixAnalyzer::solveTransient(double timeStep, double totalTime) {
    initializeTransient();
    int steps = static_cast<int>(totalTime / timeStep);

    for (int step = 0; step < steps; ++step) {
        buildTransientMatrix(timeStep);
        solveDC();
        updateTransient(timeStep);
        currentTime += timeStep;

        // Print or store results as needed
        printSolution();
    }
}