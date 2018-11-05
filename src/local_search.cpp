#include "local_search.h"
#include <algorithm>
#include <iostream>

bool diff1_Neighborhood(const std::vector<std::vector<double> >& dataMatrix, Bicluster &solution, double threshold){
    int size;
    std::vector<int> outside_solution;
    double variance = solution.variance;
    // Bicluster new_solution(solution);

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
    // std::cout << new_solution.rows.size() << ' ' << outside_solution.size() << std::endl;
    for (unsigned int i = 0; i < solution.rows.size(); i++){
        for (unsigned int j = 0; j < outside_solution.size(); j++){
            // std::cout << i << ' ' << j << std::endl;
            std::swap(solution.rows[i], outside_solution[j]);
            double new_variance = getBiclusterVariance(solution, dataMatrix);

            if((variance - new_variance) > threshold){
                // std::cout << "variance: " << variance << " diff_variance: " << new_variance << std::endl;
                // solution.rows = new_solution.rows;
                solution.variance = new_variance;
                return true;
            }

            std::swap(solution.rows[i], outside_solution[j]);
        }
    }

    size = dataMatrix[0].size();
    std::sort(solution.cols.begin(), solution.cols.end());
    hash = std::vector<bool>(size);
    for(auto &e: solution.cols){
        hash[e] = true;
    }
    outside_solution.clear();
    for(int i = 0; i < size; i++){
        if(!hash[i]){
            outside_solution.push_back(i);
        }
    }

    // std::cout << new_solution.rows.size() << ' ' << outside_solution.size() << std::endl;
    for (unsigned int i = 0; i < solution.cols.size(); i++){
        for (unsigned int j = 0; j < outside_solution.size(); j++){
            // std::cout << i << ' ' << j << std::endl;
            std::swap(solution.cols[i], outside_solution[j]);
            double new_variance = getBiclusterVariance(solution, dataMatrix);

            if((variance - new_variance) > threshold){
                // std::cout << "variance: " << variance << " diff_variance: " << new_variance << std::endl;
                // solution.rows = new_solution.rows;
                solution.variance = new_variance;
                return true;
            }

            std::swap(solution.cols[i], outside_solution[j]);
        }
    }

    return false;
}


std::vector<Bicluster> local_search(const std::vector<std::vector<double> >& dataMatrix, std::vector<Bicluster> &initial_solution){
    for(Bicluster &bi : initial_solution){
        while(diff1_Neighborhood(dataMatrix, bi, 0));

    }
    return initial_solution;
}