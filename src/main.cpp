#include <iostream>
#include <vector>
#include "readcsv.h"
#include "bicluster.h"
#include "cheng_church.h"
#include "teng_chan.h"
#include "sorted_heuristic.h"
#include "local_search.h"
#include "tabu_search.h"
#include "grasp.h"
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <cstdlib>

int main(int argc, char **argv) {
    std::string inputFile = argv[1];
    float threshold_sorted = atoi(argv[2]);
    std::vector<std::vector<double> > dataMatrix = readCSV(inputFile, ',');
    clock_t t;

    double maxResidue = 0.005;
    double threshold = 1.05;
    int numClusters = 1;
    std::cout << "Cheng & Church\n";
    // Cheng & Church:
    t = clock();
    std::vector<Bicluster> sols = runChengChurch(dataMatrix, maxResidue, threshold, numClusters);
    t = clock() - t;
    std::cout << "Running time: " << ((float)t)/CLOCKS_PER_SEC << "s\n";
    printBiclusters(sols);
    std::cout << "Done Cheng & Church\n";
    std::cout << "Found " << sols.size() << " biclusters." << std::endl;

    std::cout << "Teng & Chan\n";
    // Teng & Chan:
    t = clock();
    std::vector<Bicluster> biclusters = runTengChan(dataMatrix, 0.2, 0.5, numClusters);
    t = clock() - t;
    std::cout << "Running time: " << ((float)t)/CLOCKS_PER_SEC << "s\n";
    printBiclusters(biclusters);
    std::cout << "Done Teng & Chan\n";
    std::cout << "Found " << biclusters.size() << " biclusters." << std::endl;

    std::cout << "Sorted heuristic\n";
    // Constructive heuristic 1:
    t = clock();
    std::vector<Bicluster> sortedBi = runSortedHeuristic(dataMatrix, threshold_sorted, 1, false);
    t = clock() - t;
    std::cout << "Running time: " << ((float)t)/CLOCKS_PER_SEC << "s\n";
    printBiclusters(sortedBi);
    std::cout << "Done Sorted heuristic\n";
    std::cout << "Found " << sortedBi.size() << " biclusters." << std::endl;

    // std::cout << "Local search heuristic\n";
    // // Local Search:
    // t = clock();
    // std::vector<Bicluster> localBi = local_search(dataMatrix, sortedBi);
    // t = clock() - t;
    // std::cout << "Running time: " << ((float)t)/CLOCKS_PER_SEC << "s\n";
    // printBiclusters(localBi);
    // std::cout << "Done Local search heuristic\n";
    // std::cout << "Found " << localBi.size() << " biclusters." << std::endl;

    // Tabu Search:
    std::cout << "Tabu search Metaheuristic\n";
    t = clock();
    std::vector<Bicluster> tabuBi = tabu_search_bicluster(dataMatrix, sortedBi, 100, 50);
    t = clock() - t;
    std::cout << "Running time: " << ((float)t)/CLOCKS_PER_SEC << "s\n";
    printBiclusters(tabuBi);
    std::cout << "Done Tabu search Metaheuristic\n";
    std::cout << "Found " << tabuBi.size() << " biclusters." << std::endl;

    // GRASP:
    std::cout << "\nGRASP\n";
    t = clock();
    std::vector<Bicluster> graspBi = runGraspHeuristic(dataMatrix, 1, 10, threshold_sorted, sortedBi[0]);
    t = clock() - t;
    std::cout << "Running time: " << ((float)t)/CLOCKS_PER_SEC << "s\n";
    printBiclusters(graspBi);
    std::cout << "Done GRASP heuristic\n";
    std::cout << "Found " << graspBi.size() << " biclusters." << std::endl;

    return 0;
}
