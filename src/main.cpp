#include <iostream>
#include "readcsv.h"

int main(int argc, char **argv) {
    std::string inputFile = argv[1];
    Matrix dataMatrix = readCSV(inputFile, ',');

    for (auto &row: dataMatrix) {
        for (auto &el: row) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}