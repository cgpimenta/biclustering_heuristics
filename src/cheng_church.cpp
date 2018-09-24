#include <algorithm>
#include <limits>
#include <numeric>
#include <random>
#include "cheng_church.h"

std::vector<Solution> runChengChurchAux(Matrix &dataMatrix, double maxResidue, double threshold, int numClusters);
Solution singleNodeDeletion(Matrix &dataMatrix, Solution &sol, double maxResidue);
Solution multipleNodeDeletion(Matrix &dataMatrix, Solution &sol, double maxResidue, double threshold);
Solution nodeAdition(Matrix &dataMatrix, Solution &sol);
void initSolution(Solution &sol, Matrix &dataMatrix);
double rcResidue(Matrix &dataMatrix, int idx, Solution &sol, std::string dim);
double residueScore(Matrix &dataMatrix, Solution &sol);
double getRCMean(Matrix &dataMatrix, int idx, Solution &sol, std::string dim);
double getMatrixMean(Matrix &dataMatrix, Solution &sol);
void removeRCbyResidue(Matrix &dataMatrix, Solution &sol);
void removeRC(Solution &sol, int idx, std::string dim);
double rowResidueAux(Matrix &dataMatrix, int idx, Solution &sol);
void addInvRow(Matrix &dataMatrix, int row, Solution &sol);
void replaceElements(Matrix &dataMatrix, Solution &solAux, Solution &solB, pdd matrixMaxMin);
pdd getMatrixMaxMin(Matrix &dataMatrix);

/* ---------- Exported functions ---------- */

std::vector<Bicluster> runChengChurch(Matrix &dataMatrix, double maxResidue, double threshold, int numClusters) {
    std::vector<Solution> solAux = runChengChurchAux(dataMatrix, maxResidue, threshold, numClusters);

    std::vector<Bicluster> solutions;
    for (const auto &sol: solAux) {
        Bicluster bi(sol.rows, sol.cols);
        solutions.push_back(bi);
    }

    return solutions;
}

/* ---------- Other functions ---------- */

std::vector<Solution> runChengChurchAux(Matrix &dataMatrix, double maxResidue, double threshold, int numClusters) {
    // Get max and min value in matrix:
    pdd matrixMaxMin = getMatrixMaxMin(dataMatrix);
    std::cout << "min: " << matrixMaxMin.first << std::endl;
    std::cout << "max: " << matrixMaxMin.second << std::endl;

    // Vector to store the biclusters:
    std::vector<Solution> solutions(numClusters);

    Solution solA, solAux, solB, solC, solD;
    initSolution(solA, dataMatrix);

    solAux = solA;

    std::cout << "\nOriginal matrix:" << std::endl;
    std::cout << "Num rows = " << solA.rows.size() << std::endl; 
    std::cout << "Num cols = " << solA.cols.size() << "\n-----------------------\n";

    for (int i = 0; i < numClusters; i++) {

        solB = multipleNodeDeletion(dataMatrix, solAux, maxResidue, threshold);  // Algorithm 2
        
        solC = solB;
        solC = singleNodeDeletion(dataMatrix, solB, maxResidue);                 // Algorithm 1
        
        solD = solC;
        solD = nodeAdition(dataMatrix, solC);                                    // Algorithm 3

        solD.residue = residueScore(dataMatrix, solD);

        // Save bicluster:
        solutions[i] = solD;

        // Replace elements in solAux also in solD by with random numbers:
        replaceElements(dataMatrix, solAux, solD, matrixMaxMin);

        solAux = solD;
    }

    return solutions;
}

Solution singleNodeDeletion(Matrix &dataMatrix, Solution &sol, double maxResidue) {
    Solution solAux = sol;

    solAux.matrixMean = getMatrixMean(dataMatrix, solAux);
    double sqResidue;

    // Get mean of all the rows:
    for (int &row: solAux.rows) {
        solAux.rowMeans[row] = getRCMean(dataMatrix, row, solAux, "row");
    }

    // Get mean of all the columns:
    for (int &col: solAux.cols) {
        solAux.colMeans[col] = getRCMean(dataMatrix, col, solAux, "col");
    }

    // Get mean of the matrix:
    solAux.matrixMean = getMatrixMean(dataMatrix, solAux);

    // Get mean squared residue score:
    sqResidue = residueScore(dataMatrix, solAux);

    // If bicluster is already good enough, return:
    if (sqResidue <= maxResidue) return solAux;

    // Remove row or column with largest residue:
    removeRCbyResidue(dataMatrix, solAux);

    return solAux;
}

Solution multipleNodeDeletion(Matrix &dataMatrix, Solution &sol, double maxResidue, double threshold) {
    Solution solAux = sol;

    unsigned int minSize = 50;

    if (solAux.rows.size() < minSize || solAux.cols.size() < minSize) {
        return solAux;
    }

    solAux.matrixMean = getMatrixMean(dataMatrix, solAux);
    double sqResidue;

    // Get mean of all the rows:
    for (int &row: solAux.rows) {
        solAux.rowMeans[row] = getRCMean(dataMatrix, row, solAux, "row");
    }

    // Get mean of all the columns:
    for (int &col: solAux.cols) {
        solAux.colMeans[col] = getRCMean(dataMatrix, col, solAux, "col");
    }

    // Get mean of the matrix:
    solAux.matrixMean = getMatrixMean(dataMatrix, solAux);

    // Get mean squared residue score:
    sqResidue = residueScore(dataMatrix, solAux);

    // If bicluster is already good enough, return:
    if (sqResidue <= maxResidue) return solAux;

    // Delete rows with residue >= threshold * matrix_residue
    for (int &row: solAux.rows) {
        if (rcResidue(dataMatrix, row, solAux, "row") > threshold * sqResidue) {
            removeRC(solAux, row, "row");
        }
    }

    // Recompute column and matrix means and residue score:
    for (int &col: solAux.cols) {
        solAux.colMeans[col] = getRCMean(dataMatrix, col, solAux, "col");
    }
    solAux.matrixMean = getMatrixMean(dataMatrix, solAux);
    sqResidue = residueScore(dataMatrix, solAux);

    // Delete columns with residue >= threshold * matrix_residue
    for (int &col: solAux.cols) {
        if (rcResidue(dataMatrix, col, solAux, "col") > threshold * sqResidue) {
            removeRC(solAux, col, "col");
        }
    }

    return solAux;
}

Solution nodeAdition(Matrix &dataMatrix, Solution &sol) {
    Solution solAux = sol;

    solAux.matrixMean = getMatrixMean(dataMatrix, solAux);
    double sqResidue;

    // Get mean of all the rows:
    for (int &row: solAux.rows) {
        solAux.rowMeans[row] = getRCMean(dataMatrix, row, solAux, "row");
    }

    // Get mean of all the columns:
    for (int &col: solAux.cols) {
        solAux.colMeans[col] = getRCMean(dataMatrix, col, solAux, "col");
    }

    // Get mean of the matrix:
    solAux.matrixMean = getMatrixMean(dataMatrix, solAux);

    // Get mean squared residue score:
    sqResidue = residueScore(dataMatrix, solAux);

    // Add deleted columns with residue <= matrix_residue:
    for (int &col: sol.deletedCols) {
        if (rcResidue(dataMatrix, col, sol, "col") <= sqResidue) {
            solAux.cols.push_back(col);
            solAux.deletedCols.erase(
                std::remove(solAux.deletedCols.begin(), solAux.deletedCols.end(), col), 
                solAux.deletedCols.end());
        }
    }

    // Recompute column and matrix means and residue score:
    for (int &col: solAux.cols) {
        solAux.colMeans[col] = getRCMean(dataMatrix, col, solAux, "col");
    }
    solAux.matrixMean = getMatrixMean(dataMatrix, solAux);
    sqResidue = residueScore(dataMatrix, solAux);

    // For each row not in solution, add its inverse if 
    // residueAux <= matrix_residue:
    for (int &row: sol.deletedRows) {
        if (rowResidueAux(dataMatrix, row, sol) <= sqResidue) {
            addInvRow(dataMatrix, row, solAux);
        }
    }

    return solAux; 
}

void initSolution(Solution &sol, Matrix &dataMatrix) {
    int numRows = dataMatrix.size();
    int numCols = dataMatrix[0].size();

    Rows<int> rows(numRows);
    std::iota(rows.begin(), rows.end(), 0);
    sol.rows = rows;
    sol.rowMeans = Rows<double>(numRows);
    sol.deletedRows = Rows<int>();

    Cols<int> cols(numCols);
    std::iota(cols.begin(), cols.end(), 0);
    sol.cols = cols;
    sol.colMeans = Cols<double>(numCols);
    sol.deletedCols = Cols<int>();

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
        removeRC(sol, maxRowIdx, "row");
    } else if (maxColResidue >= maxRowResidue && maxColIdx != -1) {
        removeRC(sol, maxColIdx, "col");
    }
}

void removeRC(Solution &sol, int idx, std::string dim) {
    if (dim == "row" || dim == "rows") {
        sol.rows.erase(std::remove(sol.rows.begin(), sol.rows.end(), idx), sol.rows.end());
        sol.deletedRows.push_back(idx);
    } else if (dim == "col" || dim == "cols") {
        sol.cols.erase(std::remove(sol.cols.begin(), sol.cols.end(), idx), sol.cols.end());
        sol.deletedCols.push_back(idx);
    } else {
        std::cout << "Wrong dimension: " << dim << std::endl;
    }
}

double rowResidueAux(Matrix &dataMatrix, int idx, Solution &sol) {
    double sqResidue = 0.0;
    double residue, rowMean, colMean;

    rowMean = sol.rowMeans[idx];
    for (int &col: sol.cols) {
        colMean = sol.colMeans[col];
        residue = -dataMatrix[idx][col] + rowMean - colMean + sol.matrixMean;
        sqResidue += residue * residue;
    }

    return sqResidue / sol.cols.size();
}

void addInvRow(Matrix &dataMatrix, int row, Solution &sol) {
    std::vector<double> rowAux = dataMatrix[row];

    std::transform(
        rowAux.begin(), rowAux.end(), rowAux.begin(), 
        [](double d) -> double { return -d; });

    dataMatrix.push_back(rowAux);
    sol.rows.push_back(dataMatrix.size() + 1);
}

void replaceElements(Matrix &dataMatrix, Solution &solAux, Solution &solD, pdd matrixMaxMin) {
    std::default_random_engine generator;

    double minVal = matrixMaxMin.first;
    double maxVal = matrixMaxMin.second;

    for (int &row: solAux.rows) {
        if (std::find(solD.rows.begin(), solD.rows.end(), row) == solD.rows.end()) {
            continue;
        }
        for (int &col: solAux.cols) {
            if (std::find(solD.cols.begin(), solD.cols.end(), col) == solD.cols.end()) {
                std::uniform_real_distribution<double> distribution(2*minVal, 2*maxVal);

                dataMatrix[row][col] = distribution(generator);
            }
        }
    }
}

std::pair<double, double> getMatrixMaxMin(Matrix &dataMatrix) {
    double minVal = std::numeric_limits<double>::max();
    double maxVal = std::numeric_limits<double>::lowest();

    int numRows = dataMatrix.size();
    int numCols = dataMatrix[0].size();

    double el;

    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            el = dataMatrix[row][col];

            if (el < minVal) minVal = el;
            else if (el > maxVal) maxVal = el;
        }
    }

    return std::pair<double, double>(minVal, maxVal);
}
