#include "tabu_list.h"
#include <iostream>

TabuList::TabuList(int row_size, int col_size){
    this->row_size = row_size;
    this->col_size = col_size;
}


bool TabuList::contains(const Bicluster& solution){
    int row_size = this->row_size;
    int col_size = this->col_size;

    std::vector<bool> solution_row(row_size);
    std::vector<bool> solution_col(col_size);

    for(auto &e: solution.rows){
        solution_row[e] = true;
    }

    for(auto &e: solution.cols){
        solution_col[e] = true;
    }

    for(auto &tabu : this->tabu_list){
        bool same_row = true;
        bool same_col = true;

        for(int i = 0; i < row_size; i++){
            if(solution_row[i] != tabu.first[i]){
                same_row = false;
                break;
            }
        }

        for(int i = 0; i < col_size; i++){
            if(solution_col[i] != tabu.second[i]){
                same_col = false;
                break;
            }
        }

        if(same_row && same_col){
            return true;
        }
    }
    return false;
}


void TabuList::push(const Bicluster& solution){
    int row_size = this->row_size;
    int col_size = this->col_size;

    this->tabu_list.push_back(std::pair< std::vector<bool>, std::vector<bool> >
        (std::vector<bool>(row_size),std::vector<bool>(col_size)));

    for(auto &e: solution.rows){
        this->tabu_list.back().first[e] = true;
    }

    for(auto &e: solution.cols){
        this->tabu_list.back().second[e] = true;
    }
}


void TabuList::removeFirst(){
    this->tabu_list.pop_front();
}
