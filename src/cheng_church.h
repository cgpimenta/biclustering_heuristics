#ifndef CHENG_CHURCH_H
#define CHENG_CHURCH_H

#include <utility>
#include "readcsv.h"
#include "matrix.h"
#include "bicluster.h"


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


std::vector<Bicluster> runChengChurch(Matrix &dataMatrix, double maxResidue, double threshold, int numClusters);

#endif
