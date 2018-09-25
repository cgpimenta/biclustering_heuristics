#ifndef TENG_CHAN_H
#define TENG_CHAN_H

#include <vector>
#include "matrix.h"
#include "bicluster.h"


void weightedCorrBicluster(MatrixT& data, double alpha, double threshold);
std::vector<Bicluster> runTengChan(const std::vector<std::vector<double> >& dataMatrix, double alpha, double threshold, int max);

#endif