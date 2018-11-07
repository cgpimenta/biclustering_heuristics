#ifndef TABU_LIST_H
#define TABU_LIST_H

#include <list>
#include <vector>
#include "bicluster.h"

class TabuList{
private:
    int row_size;
    int col_size;
    std::list<std::pair< std::vector<bool>, std::vector<bool> > > tabu_list;
public:

    TabuList(int row_size, int col_size);

    bool contains(const Bicluster&);

    void push(const Bicluster&);
    void removeFirst();

    inline unsigned int size() const { return tabu_list.size(); };

};

#endif