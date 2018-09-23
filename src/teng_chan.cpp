#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <iostream>
#include "matrix.h"


#define ITERATIONS 4

typedef std::pair<std::vector<int>, std::vector<int> > Bicluster;

typedef std::pair<std::vector<bool>, std::vector<bool> > Flags;


template <typename T>
void print(const std::vector<T>& v){
    for(auto &e : v){
        std::cout << e << ' ';
    }
    std::cout << std::endl;
}

template <typename T>
void print(const std::vector<std::vector<T> >& A){
    for(auto& row : A){
        for(auto &e : row){
            std::cout << e << ' ';
        }
        std::cout << std::endl;
    }
}


void update_feature_weight(std::vector<double>& feature_weight, const std::vector<bool>& flag_vector, double alpha){
    double total_sum = 0;
    int size = feature_weight.size();
    for(int i = 0; i < size; i++){
        if(flag_vector[i]){
            total_sum = feature_weight[i];
        }
    }

    for(int i = 0; i < size; i++){
        feature_weight[i] *= (alpha + (flag_vector[i] ? 0 : ((1 - alpha) / (1 - total_sum))));
    }
}


double weighted_correlation_coefficient(int a, int b, const std::vector<double>& corr_coeff, const std::vector<std::vector<double> >& corr_coeff2){
    double ma = corr_coeff[a];
    double mb = corr_coeff[b];
    double mab = corr_coeff2[a][b];
    double ma2 = corr_coeff2[a][a];
    double mb2 = corr_coeff2[b][b];

    double numerator = (mab - ma * mb);
    double denominator = sqrt((ma2 - (ma * ma)) * (mb2 - (mb * mb)));
    return  (!denominator) ? 0 : (numerator / denominator);
}


void corr_coeff_matrix(const Matrix& data, const std::vector<double>& weight, std::vector<double>& corr_coeff, std::vector<std::vector<double> >& corr_coeff2){
    std::pair<int, int> dimension = data.dimension();

    for(int i = 0; i < dimension.first; i++){
        for(int j = 0; j < dimension.second; j++){
            corr_coeff[i] += weight[j] * data(i,j);

            for(int k = i; k < dimension.first; k++){
                corr_coeff2[i][k] += weight[j] * data(i,j) * data(k,j);
                corr_coeff2[k][i] = corr_coeff2[i][k];
            }
        }
    }
}


void weighted_corr(const Matrix& data, const std::vector<double>& feature_weight, std::vector<std::vector<double> >& similarity_matrix){
    std::pair<int, int> dimension = data.dimension();

    std::vector<double> corr_coeff(dimension.first);
    std::vector<std::vector<double> > corr_coeff2(dimension.first, std::vector<double>(dimension.first));

    corr_coeff_matrix(data, feature_weight, corr_coeff, corr_coeff2);

    for (int i = 0; i < (dimension.first - 1); i++){
        similarity_matrix[i][i] = 1;
        for (int j = i + 1; j < dimension.first; j++){
            similarity_matrix[i][j] = similarity_matrix[j][i] = weighted_correlation_coefficient(i, j, corr_coeff, corr_coeff2);
        }
    }
    similarity_matrix[dimension.first-1][dimension.first-1] = 1;
}


void dominant_set(const std::vector<std::vector<double> >& A, double epsilon, std::vector<double>& x){
    double distance, row_sum, total_sum, aux;

    epsilon *= epsilon;

    int size = A.size();
    std::fill(x.begin(), x.end(), 1. / size);
    std::vector<double> new_x(size);

    do{
        total_sum = 0;
        distance = 0;

        for(int i = 0; i < size; i++){
            row_sum = 0;
            for(int j = 0; j < (int)A[i].size(); j++){
                row_sum += A[i][j] * x[j];
            }
            new_x[i] = x[i] * row_sum;
            total_sum += new_x[i];
        }

        for(int i = 0; i < size; i++){
            aux = x[i];
            x[i] = new_x[i] / total_sum;
            aux -= x[i];

            distance += (aux * aux);
        }

    }while(distance > epsilon);
}



bool find_bicluster(Matrix& data, double threshold, Bicluster& bicluster, Flags& flag){

    std::pair<int, int> dimension = data.dimension();
    bool found = false;

    double coeff, sum_x, sum_y, sum_xx, sum_yy, sum_xy;

    int rows = dimension.first;
    int cols = dimension.second;

    for(int k = 0; k < 2; k++){
        for(int i = rows - 1; i > 0; i--){
            coeff = sum_x = sum_y = sum_xx = sum_yy = sum_xy = 0;

            for(int j = 0; j < cols; j++){
                sum_x += data(i, j);
                sum_y += data(i - 1, j);
                sum_xx += data(i, j) * data(i, j);
                sum_yy += data(i - 1, j) * data(i - 1, j);
                sum_xy += data(i, j) * data(i - 1, j);
            }

            double numerator = (sum_xy - sum_x * sum_y / cols);
            double denominator = sqrt((sum_xx - (sum_x * sum_x) / cols) * (sum_yy - (sum_y * sum_y) / cols));
            coeff = (!denominator) ? 0 : (numerator / denominator);

            bicluster.first.push_back(data.get_row_index(i));
            flag.first[data.get_row_index(i)] = true;

            if(coeff > threshold){
                found = true;
                break;
            }
        }

        data.transpose();
        std::swap(rows, cols);
        bicluster.first.swap(bicluster.second);
        flag.first.swap(flag.second);
    }

    return found;
}


// Input: the initial gene expression data matrix data, f, a and the Threshold,
void weightedCorrBicluster(Matrix& data, double alpha, double threshold, Bicluster& bicluster){
    bool biclusters_exists = true;
    Flags flag;

    std::pair<int, int> dimension = data.dimension();
    int n = dimension.first;
    int m = dimension.second;

    flag.first = std::vector<bool>(n);
    flag.second = std::vector<bool>(m);

    std::vector<double> feature_weight(m, m);        // initialize the feature vector for the m conditions.
    std::vector<double> sorting_vector(n);

    std::vector<std::vector<double> > similarity_matrix(n, std::vector<double>(n));
    std::vector<std::vector<double> > alt_similarity_matrix(m, std::vector<double>(m));


    while(biclusters_exists){
        for(int i = 0; i < ITERATIONS; i++){
            // std::cout << data << std::endl;

            update_feature_weight(feature_weight, flag.first, alpha);
            // print<double>(feature_weight);
            // std::cout << std::endl;

            // std::cout << "similarity_matrix: ";
            // print<double>(similarity_matrix);
            // std::cout << std::endl;
            
            weighted_corr(data, feature_weight, similarity_matrix);     // compute the similarity matrix
            // std::cout << "similarity_matrix: ";
            // print<double>(similarity_matrix);
            // std::cout << std::endl;

            dominant_set(similarity_matrix, 1e-04, sorting_vector);     // use dominant set approach to find the sorting vector
            // std::cout << "sorting_vector: ";
            // print<double>(sorting_vector);
            // std::cout << std::endl;

            // std::cout << data << std::endl;
            data.weighted_row_sort(sorting_vector);             // sort the rows of matrix data
            // std::cout << data << std::endl;

            data.transpose();
            flag.first.swap(flag.second);
            std::swap(n, m);
            // std::cout << "feature_weight: " << feature_weight.size() << " sorting_vector: " << sorting_vector.size() << std::endl;

            feature_weight.swap(sorting_vector);                    //update the feature weight vector
            // std::cout << "feature_weight: " << feature_weight.size() << std::endl;
            similarity_matrix.swap(alt_similarity_matrix);
        }

        biclusters_exists = find_bicluster(data, threshold, bicluster, flag);        //extract the bicluster from the sorted data matrix
    }
}


int main(){

    std::vector<std::vector<double> > A = {{2.,4.,3.},{8.,4.,2.}};

    Matrix B(A);

    // weightedCorrBicluster(B, 0.2, 0.1);
    std::cout << B << std::endl;
    Bicluster bb;
    weightedCorrBicluster(B, 0.2, 0.01, bb);
    print(bb.first);
    print(bb.second);


    // std::vector<int> index(5);
    // std::iota(index.begin(), index.end(), 0);
    
    // std::vector<double> weight = {5.,4.,3.,2.,1.};
    // print<int>(index);

    // std::sort(index.begin(), index.end(), 
    //   [&weight](const int &i, const int &j) { return weight[i] < weight[j]; });

    // print<int>(index);
    // std::sort(index.begin(), index.end(), 
    //   [&weight](const int &i, const int &j) { return weight[i] < weight[j]; });

    // print<int>(index);
    // B.transpose();
    // std::cout << B << std::endl;

    // std::vector<double> weight = {5., 1., 3.};

    // std::vector<double> weight2 = {5., 1.};

    // for(auto &e : weight){
    //     std::cout << e << ' ';
    // }
    // std::cout << std::endl;
    // std::cout << std::endl;


    // B.weighted_row_sort(weight);

    // std::cout << B << std::endl;

    // B.transpose();

    // std::cout << B << std::endl;

    // B.weighted_row_sort(weight2);

    // std::cout << B << std::endl;


    // for(auto& row : A){
    //     for(auto &e : row){
    //         std::cout << e << ' ';
    //     }
    //     std::cout << std::endl;
    // }

    // std::vector<double> x = dominant_set(A, 1e-4);

    // for(auto &e : x){
    //     std::cout << e << ' ';
    // }
    // std::cout << std::endl;

    // Matrix similarity_matrix(A.size(), std::vector<double>(A.size()));


    // weighted_corr(A, weight, similarity_matrix);


    // for(auto& row : similarity_matrix){
    //     for(auto &e : row){
    //         std::cout << e << ' ';
    //     }
    //     std::cout << std::endl;
    // }

}