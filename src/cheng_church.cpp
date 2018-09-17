#include <algorithm>
#include <limits>
#include <numeric>
#include "cheng_church.h"

void runChengChurch(Matrix &dataMatrix, double maxResidue) {
    Solution sol;
    initSolution(sol, dataMatrix);

    singleNodeDeletion(dataMatrix, sol, maxResidue);
}

void singleNodeDeletion(Matrix &dataMatrix, Solution &sol, double maxResidue) {
    sol.matrixMean = getMatrixMean(dataMatrix, sol);
    double sqResidue;

    // Get mean of all the rows:
    for (int &row: sol.rows) {
        sol.rowMeans[row] = getRCMean(dataMatrix, row, sol, "row");
    }

    // Get mean of all the columns:
    for (int &col: sol.cols) {
        sol.colMeans[col] = getRCMean(dataMatrix, col, sol, "col");
    }

    // Get mean of the matrix:
    sol.matrixMean = getMatrixMean(dataMatrix, sol);

    sqResidue = residueScore(dataMatrix, sol);

    // If bicluster is already good enough, return:
    if (sqResidue <= maxResidue) return;

    // Remove row or column with largest residue:
    removeRCbyResidue(dataMatrix, sol);
 

}

void initSolution(Solution &sol, Matrix &dataMatrix) {
    int numRows = dataMatrix.size();
    int numCols = dataMatrix[0].size();

    Rows<int> rows(numRows);
    std::iota(rows.begin(), rows.end(), 0);
    sol.rows = rows;
    sol.rowMeans = Rows<double>(numRows);

    Cols<int> cols(numCols);
    std::iota(cols.begin(), cols.end(), 0);
    sol.cols = cols;
    sol.colMeans = Cols<double>(numCols);

    sol.matrixMean = 0.0;
}

double rcResidue(Matrix &dataMatrix, int idx, Solution &sol, std::string dim) {
    double sqResidue = 0.0;
    double residue, rowMean, colMean;

    if (dim == "row" || dim == "rows") {
        rowMean = sol.rowMeans[idx];
        for (int &col: sol.cols) {
            colMean = sol.colMeans[col];
            residue = dataMatrix[idx][col] - rowMean - colMean + sol.matrixMean;
            sqResidue += residue * residue;
        }

        return sqResidue / sol.cols.size();
    } 

    else if (dim == "col" || dim == "cols") {
        colMean = sol.colMeans[idx];
        for (int &row: sol.rows) {
            rowMean = sol.rowMeans[row];
            residue = dataMatrix[row][idx] - rowMean - colMean + sol.matrixMean;
            sqResidue += residue * residue;
        }

        return sqResidue / sol.rows.size(); 
    }

    std::cout << "Wrong dimension: " << dim << std::endl;
    return 0.0;
}

double residueScore(Matrix &dataMatrix, Solution &sol) {
    double sqResidue = 0.0;
    double residue, rowMean, colMean;

    for (int &row: sol.rows) {
        rowMean = sol.rowMeans[row];

        for (int &col: sol.cols) {
            colMean = sol.colMeans[col];

            residue = dataMatrix[row][col] - rowMean - colMean + sol.matrixMean;
            sqResidue += residue * residue;
        }
    }

    return sqResidue / (sol.rows.size() * sol.cols.size());
}

double getRCMean(Matrix &dataMatrix, int idx, Solution &sol, std::string dim) {
    double sum = 0.0;

    if (dim == "row" || dim == "rows") {
        for (int &col: sol.cols) {
            sum += dataMatrix[idx][col];
        }

        return sum / sol.cols.size();
    } 

    else if (dim == "col" || dim == "cols") {
        for (int &row: sol.rows) {
            sum += dataMatrix[row][idx];
        }

        return sum / sol.rows.size();
    }

    std::cout << "Wrong dimension: " << dim << std::endl;
    return 0.0;
}

double getMatrixMean(Matrix &dataMatrix, Solution &sol) {
    double sumMatrix = 0.0;

    for (int &row: sol.rows) {
        for (int &col: sol.cols) {
            sumMatrix += dataMatrix[row][col];
        }
    }

    return sumMatrix / (sol.rows.size() * sol.cols.size());
}

void removeRCbyResidue(Matrix &dataMatrix, Solution &sol) {
    double negInf = std::numeric_limits<double>::lowest();

    // Find row with largest residue:
    double maxRowResidue = negInf;
    double rowResidue = 0.0;
    int maxRowIdx = -1;
    for (int &row: sol.rows) {
        rowResidue = rcResidue(dataMatrix, row, sol, "row");
        if (rowResidue > maxRowResidue) {
            maxRowResidue = rowResidue;
            maxRowIdx = row;
        }
    }

    // Find column with largest residue:
    double maxColResidue = negInf;
    double colResidue = 0.0;
    int maxColIdx = -1;
    for (int &col: sol.cols) {
        colResidue = rcResidue(dataMatrix, col, sol, "col");
        if (colResidue > maxColResidue) {
            maxColResidue = colResidue;
            maxColIdx = col;
        }
    }

    // Remove row or column with largest residue:
    if (maxRowResidue > maxColResidue && maxRowIdx != -1) {
        sol.rows.erase(std::remove(sol.rows.begin(), sol.rows.end(), maxRowIdx), sol.rows.end());
    } else if (maxColResidue >= maxRowResidue && maxColIdx != -1) {
        sol.cols.erase(std::remove(sol.cols.begin(), sol.cols.end(), maxColIdx), sol.cols.end());
    }

}