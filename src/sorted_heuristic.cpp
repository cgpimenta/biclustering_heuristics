#include <climits>
#include "sorted_heuristic.h"
#include "runningstat.h"
#include <iostream>

#define ITERATIONS 2
#define MIN_SIZE 4


void get_sorting_vector(const MatrixT& data, std::vector<double>& sorting_vector){
    std::pair<int, int> dimension = data.dimension();
    int rows = dimension.first;
    int cols = dimension.second;

    for(int i = 0; i < rows; i++){
        double max_value = 0;
        for (int j = 0; j < cols; j++){
            max_value = std::max(max_value, data(i, j));
        }
        sorting_vector[i] = max_value;
    }
}


bool find_bicluster(MatrixT& data, double threshold, Bicluster& bicluster){
    std::pair<int, int> dimension = data.dimension();
    int row_index = dimension.first - 1;
    int col_index = dimension.second - 1;

    RunningStat rs_rows, rs_cols;
    rs_rows.Push(data(row_index, col_index));
    rs_cols.Push(data(row_index, col_index));
    bicluster.rows.push_back(data.get_row_index(row_index));
    bicluster.cols.push_back(data.get_col_index(col_index));

    int total_size = 1;

    while(row_index > 0 && col_index > 0){
        for(int i = dimension.first - 1; i >= row_index; i-- ){
            rs_rows.Push(data(i, col_index - 1));
            if(rs_rows.Variance() > threshold){
                break;
            }
        }
        double row_variance = rs_rows.Variance();

        for(int j = dimension.second - 1; j >= col_index; j-- ){
            rs_cols.Push(data(row_index - 1, j));
            if(rs_cols.Variance() > threshold){
                break;
            }
        }
        double col_variance = rs_cols.Variance();
        std::cout << "Total size: " << total_size << ". col_variance: " << col_variance << " - row_variance: " << row_variance << std::endl;
        if(row_variance > threshold && col_variance > threshold){
            return (total_size > MIN_SIZE);
        }

        if(row_variance > col_variance){
            for(int j = dimension.second - 1; j >= col_index; j-- ){
                data(row_index - 1, j) = INT_MIN;
            }
            bicluster.rows.push_back(data.get_row_index(--row_index));
            rs_rows = rs_cols;
        }
        else{
            for(int i = dimension.first - 1; i >= row_index; i-- ){
                data(i, col_index - 1) = INT_MIN;
            }
            bicluster.cols.push_back(data.get_col_index(--col_index));
            rs_cols = rs_rows;
        }
        total_size++;

        std::cout << bicluster;
        std::cout << "Variance: " << getBiclusterVariance(bicluster, data.getRawMatrix()) << std::endl;
    }
    return true;
}


// Input: the initial gene expression data matrix data, f, a and the Threshold,
void sortedBicluster(MatrixT& data, double threshold, std::vector<Bicluster>& biclusters, int max){

    std::pair<int, int> dimension = data.dimension();
    int n = dimension.first;
    int m = dimension.second;

    std::vector<double> sorting_vector(n);
    std::vector<double> alt_sorting_vector(m);

    for(int iteration = 0; iteration < max; iteration++){
        std::cout << "Iteration " << iteration << std::endl;
        for(int i = 0; i < ITERATIONS; i++){
            std::cout << "------- " << i << ".1" << std::endl;
            get_sorting_vector(data, sorting_vector);     // use dominant set approach to find the sorting vector
            std::cout << "------- " << i << ".2" << std::endl;
            data.weighted_row_sort(sorting_vector);             // sort the rows of matrix data
            std::cout << "------- " << i << ".3" << std::endl;

            data.transpose();
            sorting_vector.swap(alt_sorting_vector);                    //update the feature weight vector
        }
        if(data(n-1, m-1) == INT_MIN){
            break;
        }

        Bicluster bicluster;
        if(find_bicluster(data, threshold, bicluster)){
            bicluster.variance = getBiclusterVariance(bicluster, data.getRawMatrix());        //extract the bicluster from the sorted data matrix
            biclusters.push_back(bicluster);
        }
    }
}


std::vector<Bicluster> runSortedHeuristic(const std::vector<std::vector<double> >& dataMatrix, double threshold, int max){
    std::vector<Bicluster> biclusters;
    MatrixT data(dataMatrix);
    sortedBicluster(data, threshold, biclusters, max);
    return biclusters;
}
