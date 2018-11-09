#include <iostream>
#include "grasp.h"
#include "local_search.h"
#include "sorted_heuristic.h"

// Bicluster randomGreedyHeuristic(const std::vector<std::vector<double> >& dataMatrix, double threshold) {
//     return runSortedHeuristic(dataMatrix, threshold, 1, true);
// }

Bicluster grasp(const std::vector<std::vector<double> >& dataMatrix, int numIter, double threshold, const Bicluster& seed) {
    Bicluster bestSol = seed;

    for (int i = 0; i < numIter; i++) {
        // std::cout << "iteration:" << i << std::endl;
        // Bicluster initialSol = randomGreedyHeuristic(dataMatrix, threshold);
        std::vector<Bicluster> initialVector = runSortedHeuristic(dataMatrix, threshold, 1, true);
        // std::cout << i << ".1" << std::endl;
        // initialVector.push_back(initialSol);
        // std::cout << i << ".2" << std::endl;
        // std::cout << i << ".3" << std::endl;
        Bicluster newSol = local_search(dataMatrix, initialVector)[0];
        // std::cout << i << ".4" << std::endl;
        if (newSol.variance < bestSol.variance) {
            bestSol = newSol;
        }
        // std::cout << i << ".5" << std::endl;
    }

    return bestSol;
}

std::vector<Bicluster> runGraspHeuristic(const std::vector<std::vector<double> >& dataMatrix, int numBiclusters, int numIter, double threshold, const Bicluster &seed) {
    std::vector<Bicluster> biclusters;

    for (int i = 0; i < numBiclusters; i++) {
        biclusters.push_back(grasp(dataMatrix, numIter, threshold, seed));
    }

    return biclusters;
}
