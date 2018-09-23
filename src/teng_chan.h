#ifndef TENG_CHAN_H
#define TENG_CHAN_H

#include <vector>
#include "matrix.h"

typedef std::pair<std::vector<int>, std::vector<int> > Bicluster;

void weightedCorrBicluster(Matrix& data, double alpha, double threshold, Bicluster& bicluster);

#endif