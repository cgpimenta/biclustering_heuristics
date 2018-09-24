#include "bicluster.h"

void printBiclusters(std::vector<Bicluster>& biclusters) {
    unsigned int i = 1;

    for (Bicluster &bc: biclusters) {
        std::cout << "Bicluster " << i << "\n\n";

        // Print number of rows:
        std::cout << "Number of rows: " << bc.first.size() << std::endl;
        
        // Print rows:
        // std::cout << "Rows:" << std::endl;
        // for (int &row: bc.first) {
        //     std::cout << row << " ";
        // } std::cout << std::endl;

        // Print number of cols:
        std::cout << "Number of columns: " << bc.second.size() << std::endl;

        // Print columns:
        // std::cout << "Columns:" << std::endl;
        // for (int &col: bc.second) {
        //     std::cout << col << " ";
        // } std::cout << std::endl;
        

        std::cout << "\n--------------------------\n\n";

        i++;
    }
}