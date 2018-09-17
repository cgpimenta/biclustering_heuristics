#include <iostream>
#include <vector>
#include "readcsv.h"
#include "cheng_church.h"

int main(int argc, char **argv) {
    std::string inputFile = argv[1];
    Matrix dataMatrix = readCSV(inputFile, ',');

    double maxResidue = 0.05;

    // Cheng & Church:
    runChengChurch(dataMatrix, maxResidue);
    
    // Teng:
    // TODO
    
    // Constructive heuristic 1:
    // TODO
    
    // Constructive heuristic 2:
    // TODO

    return 0;
}