#include "tabu_search.h"
#include <algorithm>
#include <iostream>

bool diff1_tabu(const std::vector<std::vector<double> >& dataMatrix, Bicluster &solution, TabuList& tabu_list){
    int size;
    std::vector<int> outside_solution;
    double min_variance = solution.variance;

    bool found = false;
    std::pair<int, int> best_solution;

    size = dataMatrix.size();
    std::sort(solution.rows.begin(), solution.rows.end());
    std::vector<bool> hash(size);
    for(auto &e: solution.rows){
        hash[e] = true;
    }
    for(int i = 0; i < size; i++){
        if(!hash[i]){
            outside_solution.push_back(i);
        }
    }

    for (unsigned int i = 0; i < solution.rows.size(); i++){
        for (unsigned int j = 0; j < outside_solution.size(); j++){
            std::swap(solution.rows[i], outside_solution[j]);
            if(!tabu_list.contains(solution)){
                double new_variance = getBiclusterVariance(solution, dataMatrix);

                if(new_variance < min_variance){
                    min_variance = new_variance;
                    best_solution = std::make_pair(i,j);
                    found = true;
                }
            }
            std::swap(solution.rows[i], outside_solution[j]);
        }
    }

    if(found){
        int i = best_solution.first;
        int j = best_solution.second;
        std::swap(solution.rows[i], outside_solution[j]);
        solution.variance = min_variance;
    }

    return found;
}




void tabu_search(const std::vector<std::vector<double> >& dataMatrix,
                 Bicluster& solution,
                 unsigned int max_list_size, int max_iterations){

    TabuList tabu_list(dataMatrix.size(), dataMatrix[0].size());
    tabu_list.push(solution);

    Bicluster new_solution;

    for(int i = 0; i < max_iterations; i++){
        new_solution = solution;
        if(diff1_tabu(dataMatrix, new_solution, tabu_list)){
            if(new_solution.variance < solution.variance){
                solution = new_solution;
            }

            tabu_list.push(new_solution);
            if(tabu_list.size() > max_list_size){
                tabu_list.removeFirst();
            }
        }
    }
}


std::vector<Bicluster> tabu_search_bicluster(const std::vector<std::vector<double> >& dataMatrix, std::vector<Bicluster> &initial_solution,
                                             unsigned int max_list_size, int max_iterations){
    for(Bicluster &bi : initial_solution){
        tabu_search(dataMatrix, bi, max_list_size, max_iterations);
    }
    return initial_solution;
}