#ifndef GRASP_H
#define GRASP_H

#include <vector>
#include "matrix.h"
#include "bicluster.h"

std::vector<Bicluster> runGraspHeuristic(const std::vector<std::vector<double> >& dataMatrix, int numBiclusters, int numIter, double threshold, const Bicluster &seed);


#endif