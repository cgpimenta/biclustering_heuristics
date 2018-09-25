#ifndef SORTEDH_H
#define SORTEDH_H

#include <vector>
#include "matrix.h"
#include "bicluster.h"

// Input: the initial gene expression data matrix data, f, a and the Threshold,
void sortedBicluster(MatrixT& data, std::vector<Bicluster>& biclusters, double threshold, int max);

std::vector<Bicluster> runSortedHeuristic(const std::vector<std::vector<double> >& dataMatrix, double threshold, int max);

#endif