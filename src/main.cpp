#include <iostream>
#include <numeric>
#include "readcsv.h"
#include "cheng_church.h"

int main(int argc, char **argv) {
    std::string inputFile = argv[1];
    Matrix dataMatrix = readCSV(inputFile, ',');

    int numRows = dataMatrix.size();
    int numCols = dataMatrix[0].size();

    Rows rows(numRows);
    std::iota(rows.begin(), rows.end(), 0);

    Cols cols(numCols);
    std::iota(cols.begin(), cols.end(), 0);

    // std::cout << dataMatrix.size() << std::endl;
    // std::cout << dataMatrix[0].size() << std::endl;

    long double sqResidueScore = residueScore(dataMatrix, rows, cols);
    std::cout << sqResidueScore << std::endl;

    // Cheng & Church:
    // TODO
    
    // Teng:
    // TODO
    
    // Constructive heuristic 1:
    // TODO
    
    // Constructive heuristic 2:
    // TODO

    return 0;
}