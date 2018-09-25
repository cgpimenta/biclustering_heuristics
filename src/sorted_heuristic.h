#ifndef SORTEDH_H
#define SORTEDH_H

#include <vector>
#include "matrix.h"
#include "bicluster.h"


std::vector<Bicluster> runSortedHeuristic(const std::vector<std::vector<double> >& dataMatrix, double threshold, int max);

#endif