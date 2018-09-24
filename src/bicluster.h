#ifndef BICLUSTER_H
#define BICLUSTER_H

#include <vector>
#include <iostream>

typedef std::pair<std::vector<int>, std::vector<int> > Bicluster;

void printBiclusters(std::vector<Bicluster>& biclusters);

#endif