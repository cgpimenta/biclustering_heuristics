#include <iostream>
#include "grasp.h"
#include "local_search.h"
#include "sorted_heuristic.h"

Bicluster randomGreedyHeuristic(const std::vector<std::vector<double> >& dataMatrix, double threshold) {
    return runSortedHeuristic(dataMatrix, threshold, 1, true)[0];
}

Bicluster grasp(const std::vector<std::vector<double> >& dataMatrix, int numIter, double threshold, const Bicluster& seed) {
    Bicluster bestSol = seed;

    for (int i = 0; i < numIter; i++) {
        Bicluster initialSol = randomGreedyHeuristic(dataMatrix, threshold);
        std::vector<Bicluster> initialVector;
        initialVector.push_back(initialSol);

        Bicluster newSol = local_search(dataMatrix, initialVector)[0];

        if (newSol.variance < bestSol.variance) {
            bestSol = newSol;
        }
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
