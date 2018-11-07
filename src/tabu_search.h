#ifndef TABU_SEARCH_H
#define TABU_SEARCH_H

#include <vector>
#include "bicluster.h"
#include "tabu_list.h"

std::vector<Bicluster> tabu_search_bicluster(const std::vector<std::vector<double> >& dataMatrix, std::vector<Bicluster> &initial_solution,
                                             unsigned int max_list_size, int max_iterations);

#endif