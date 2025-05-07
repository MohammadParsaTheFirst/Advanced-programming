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

private:
    const Circuit& circuit;

    Eigen::MatrixXd G, B, C, D, A;
    Eigen::VectorXd J, E, z;
    Eigen::VectorXd nodeVoltages;
    Eigen::VectorXd voltageSourceCurrents;

    Eigen::VectorXd prevNodeVoltages;
    double currentTime;

    void initializeTransient();
    void updateTransient(double timeStep);

    void combineMNAMatrix();
};

#endif // MATRIX_ANALYZER_H
