#include <iostream>
#include <vector>
#include "readcsv.h"
#include "cheng_church.h"
#include "teng_chan.h"


int main(int argc, char **argv) {
    std::string inputFile = argv[1];
    std::vector<std::vector<double> > dataMatrix = readCSV(inputFile, ',');

    double maxResidue = 0.005;
    double threshold = 2.0;
    int numClusters = 4;

    // Cheng & Church:
    std::vector<Bicluster> sols = runChengChurch(dataMatrix, maxResidue, threshold, numClusters);
    printBiclusters(sols);
    
    // Teng & Chan:
    std::vector<Bicluster> biclusters = runTengChan(dataMatrix, 0.2, threshold);
    for(auto &bi : biclusters){
        for(auto &row: bi.first){
            std::cout << row << ' ';
        }
        std::cout << std::endl;
        for(auto &row: bi.second){
            std::cout << row << ' ';
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    
    // Constructive heuristic 1:
    // TODO
    
    // Constructive heuristic 2:
    // TODO

    return 0;
}

