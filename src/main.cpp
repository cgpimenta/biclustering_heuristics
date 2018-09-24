#include <iostream>
#include <vector>
#include "readcsv.h"
#include "bicluster.h"
#include "cheng_church.h"
#include "teng_chan.h"


int main(int argc, char **argv) {
    std::string inputFile = argv[1];
    std::vector<std::vector<double> > dataMatrix = readCSV(inputFile, ',');

    double maxResidue = 0.005;
    double threshold = 2.0;
    int numClusters = 4;

    std::cout << "Cheng & Church\n";
    // Cheng & Church:
    std::vector<Bicluster> sols = runChengChurch(dataMatrix, maxResidue, threshold, numClusters);
    printBiclusters(sols);
    std::cout << "Done Cheng & Church\n";
    std::cout << "Found " << sols.size() << " biclusters." << std::endl;

    std::cout << "Teng & Chan\n";
    // Teng & Chan:
    std::vector<Bicluster> biclusters = runTengChan(dataMatrix, 0.2, 0.5, numClusters);
    printBiclusters(biclusters);
    std::cout << "Done Teng & Chan\n";
    std::cout << "Found " << biclusters.size() << " biclusters." << std::endl;


   // Constructive heuristic 1:
    // TODO
    
    // Constructive heuristic 2:
    // TODO

    return 0;
}

