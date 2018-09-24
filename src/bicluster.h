#ifndef BICLUSTER_H
#define BICLUSTER_H

#include <vector>
#include <ostream>

// typedef std::pair<std::vector<int>, std::vector<int> > Bicluster;

struct Bicluster{
    std::vector<int> rows;
    std::vector<int> cols;
    double variance;

    Bicluster();
    Bicluster(const std::vector<int>&, const std::vector<int>&);
    friend std::ostream& operator<<(std::ostream&, const Bicluster&);
};

void printBiclusters(std::vector<Bicluster>& biclusters);
double getBiclusterVariance(Bicluster &bicluster, std::vector<std::vector<double> >& dataMatrix);

#endif