#ifndef CHENG_CHURCH_H
#define CHENG_CHURCH_H

#include "readcsv.h"

class Solution {
public:
    Rows<int> rows;
    Rows<double> rowMeans;
    Cols<int> cols;
    Cols<double> colMeans;
    double matrixMean;
};

void runChengChurch(Matrix &dataMatrix, double maxResidue); 
void singleNodeDeletion(Matrix &dataMatrix, Solution &sol, double maxResidue);

void initSolution(Solution &sol, Matrix &dataMatrix);
double rcResidue(Matrix &dataMatrix, Solution &sol, std::string dim);
double residueScore(Matrix &dataMatrix, Solution &sol);
double getRCMean(Matrix &dataMatrix, int idx, Solution &sol, std::string dim);
double getMatrixMean(Matrix &dataMatrix, Solution &sol);
void removeRCbyResidue(Matrix &dataMatrix, Solution &sol);

#endif