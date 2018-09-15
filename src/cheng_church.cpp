#include "cheng_church.h"
#include "cmath"

long double residueScore(Matrix dataMatrix, Rows rows, Cols cols) {
    long double sqResidue = 0.0;
    double residue, rowMean, colMean, matrixMean;

    matrixMean = getMatrixMean(dataMatrix, rows, cols);

    for (int &row: rows) {
        rowMean = getRowMean(dataMatrix, row, cols);

        for (int &col: cols) {
            colMean = getColMean(dataMatrix, rows, col);
            residue = dataMatrix[row][col] - rowMean - colMean + matrixMean;
            sqResidue += residue * residue;
        }
    }

    return sqResidue / (rows.size() + cols.size());
}

double getRowMean(Matrix dataMatrix, int row, Cols cols) {
    double sumRow = 0.0;

    for (int &col: cols) {
        sumRow += dataMatrix[row][col];
    }

    return sumRow / cols.size();
}

double getColMean(Matrix dataMatrix, Rows rows, int col) {
    double sumCol = 0.0;

    for (int &row: rows) {
        sumCol += dataMatrix[row][col];
    }

    return sumCol / rows.size();
}

double getMatrixMean(Matrix dataMatrix, Rows rows, Cols cols) {
    double sumMatrix = 0.0;

    for (int &row: rows) {
        for (int &col: cols) {
            sumMatrix += dataMatrix[row][col];
        }
    }

    return sumMatrix / (rows.size() + cols.size());
}