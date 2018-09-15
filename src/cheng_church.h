#ifndef CHENG_CHURCH_H
#define CHENG_CHURCH_H

#include "readcsv.h"

long double residueScore(Matrix dataMatrix, Rows rows, Cols cols);
double getRowMean(Matrix dataMatrix, int row, Cols cols);
double getColMean(Matrix dataMatrix, Rows rows, int col);
double getMatrixMean(Matrix dataMatrix, Rows rows, Cols cols);

#endif