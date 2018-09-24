#ifndef TENG_CHAN_H
#define TENG_CHAN_H

#include <vector>
#include "matrix.h"

typedef std::pair<std::vector<int>, std::vector<int> > Bicluster;

void weightedCorrBicluster(MatrixT& data, double alpha, double threshold, std::vector<Bicluster>&);
std::vector<Bicluster> runTengChan(std::vector<std::vector<double> >& dataMatrix, double alpha, double threshold);

#endif