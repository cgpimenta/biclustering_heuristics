#include "bicluster.h"
#include <iostream>


Bicluster::Bicluster(){
    this->rows = std::vector<int>();
    this->cols = std::vector<int>();
}



Bicluster::Bicluster(const std::vector<int>& rows, const std::vector<int>& cols){
    this->rows = std::vector<int>(rows);
    this->cols = std::vector<int>(cols);
}



std::ostream& operator<<(std::ostream& out, const Bicluster& bicluster){
        // Print number of rows:
        out << "Number of rows: " << bicluster.rows.size() << std::endl;
        
        // Print rows:
        // out << "Rows:" << std::endl;
        // for (const int &row: bicluster.rows) {
        //     out << row << " ";
        // } out << std::endl;

        // Print number of cols:
        out << "Number of columns: " << bicluster.cols.size() << std::endl;

        // Print columns:
        // out << "Columns:" << std::endl;
        // for (const int &col: bicluster.cols) {
        //     out << col << " ";
        // } out << std::endl;

    return out;
}


void printBiclusters(std::vector<Bicluster>& biclusters) {
    unsigned int i = 1;

    for (Bicluster &bc: biclusters) {
        std::cout << "Bicluster " << i << "\n\n";

        std::cout << bc;
        std::cout << "\n--------------------------\n\n";

        i++;
    }
}
