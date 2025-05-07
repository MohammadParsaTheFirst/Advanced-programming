#ifndef MATRIX_ANALYZER_H
#define MATRIX_ANALYZER_H

#include "Circuit.h"
#include <Eigen/Dense>
#include <iostream>

class MatrixAnalyzer {
public:
    MatrixAnalyzer(const Circuit& circuit);

    void buildDCMatrix();
    void solveDC();
    void printSolution() const;

    // Add these new methods
    void buildTransientMatrix(double timeStep);
    void solveTransient(double timeStep, double totalTime);

private:
    const Circuit& circuit;

    Eigen::MatrixXd G, B, C, D, A;
    Eigen::VectorXd J, E, z;
    Eigen::VectorXd nodeVoltages;
    Eigen::VectorXd voltageSourceCurrents;

    // Add these for transient analysis
    Eigen::VectorXd prevNodeVoltages;
    double currentTime;

    void combineMNAMatrix();
    void initializeTransient();
    void updateTransient(double timeStep);
};

#endif // MATRIX_ANALYZER_H