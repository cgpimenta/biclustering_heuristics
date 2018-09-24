#include "bicluster.h"
#include <iostream>


Bicluster::Bicluster(){
    this->rows = std::vector<int>();
    this->cols = std::vector<int>();
    this->variance = 0;
}



Bicluster::Bicluster(const std::vector<int>& rows, const std::vector<int>& cols){
    this->rows = std::vector<int>(rows);
    this->cols = std::vector<int>(cols);
    this->variance = 0;
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
        
        // Print variance:
        out << "Variance: " << bicluster.variance << std::endl;

        // Print quality:
        out << "Quality index: "; 
        out << (bicluster.rows.size() * bicluster.cols.size() / bicluster.variance);
        out << std::endl;

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

double getBiclusterMean(Bicluster &bicluster, std::vector<std::vector<double> >& dataMatrix) {
    int numRows = bicluster.rows.size();
    int numCols = bicluster.cols.size();

    double sum = 0;

    for (const int &row: bicluster.rows) {
        for (const int &col: bicluster.cols) {
            sum += dataMatrix[row][col];
        }
    }

    return sum / (numRows + numCols);
}

double getBiclusterVariance(Bicluster &bicluster, std::vector<std::vector<double> >& dataMatrix) {
    int numRows = bicluster.rows.size();
    int numCols = bicluster.cols.size();

    double biclusterMean = getBiclusterMean(bicluster, dataMatrix);

    double sum = 0;
    double deviation;

    for (const int &row: bicluster.rows) {
        for (const int &col: bicluster.cols) {
            deviation = dataMatrix[row][col] - biclusterMean;
            sum += deviation * deviation;
        }
    }

    return sum / (numRows + numCols);
}