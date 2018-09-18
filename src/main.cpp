#include <iostream>
#include <vector>
#include "readcsv.h"
#include "cheng_church.h"

int main(int argc, char **argv) {
    std::string inputFile = argv[1];
    std::vector<std::vector<double> > dataMatrix = readCSV(inputFile, ',');

    double maxResidue = 0.005;
    double threshold = 2.0;
    int numClusters = 4;

    // Cheng & Church:
    std::vector<Solution> sols = runChengChurch(dataMatrix, maxResidue, threshold, numClusters);
    printBiclusters(sols);
    
    // Teng:
    // TODO
    
    // Constructive heuristic 1:
    // TODO
    
    // Constructive heuristic 2:
    // TODO

    return 0;
}
