#ifndef CHENG_CHURCH_H
#define CHENG_CHURCH_H

#include <utility>
#include "readcsv.h"

typedef std::vector<std::vector<double> > Matrix;

template<typename T>
using Rows = std::vector<T>;

template<typename T>
using Cols = std::vector<T>;

typedef std::pair<double, double> pdd;

class Solution {
public:
    Rows<int> rows;
    Rows<double> rowMeans;
    Rows<int> deletedRows;

    Cols<int> cols;
    Cols<double> colMeans;
    Cols<int> deletedCols;

    double matrixMean;

    double residue;

    Solution() {}

    Solution(const Solution &obj) {
        rows = obj.rows;
        rowMeans = obj.rowMeans;
        deletedRows = obj.deletedRows;

        cols = obj.cols;
        colMeans = obj.colMeans;
        deletedCols = obj.deletedCols;

        matrixMean = obj.matrixMean;
    }
};

std::vector<Solution> runChengChurch(Matrix &dataMatrix, double maxResidue, double threshold, int numClusters);
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
void printBiclusters(std::vector<Solution> &solutions);

#endif
