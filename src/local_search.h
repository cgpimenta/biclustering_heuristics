#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include <vector>
#include "matrix.h"
#include "bicluster.h"

std::vector<Bicluster> local_search(const std::vector<std::vector<double> >& dataMatrix, std::vector<Bicluster> &initial_solution);

#endif