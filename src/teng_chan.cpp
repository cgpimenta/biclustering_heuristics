#include <vector>
#include <iostream>

typedef std::vector<std::vector<double> > Matrix;



void update_feature_weight(std::vector<double>& feature_weight, const td::vector<bool>& flag_vector, double alpha){
    double total_sum = 0;
    for(int i = 0; i < feature_weight.size(); i++){
        total_sum = (feature_weight[i] & flag_vector[i]);
    }

    for(int i = 0; i < feature_weight.size(); i++){
        feature_weight[i] *= (alpha + (flag_vector[i] ? 0 : ((1 - alpha) / (1 - total_sum))));
    }
}



std::vector<double> dominant_set(const Matrix& A, double epsilon){
    double distance, row_sum, total_sum, aux;

    epsilon *= epsilon;

    std::vector<double> x(A.size(), 1. / A.size());
    std::vector<double> new_x(x.size());

    do{
        total_sum = 0;
        distance = 0;

        for(int i = 0; i < A.size(); i++){
            row_sum = 0;
            for(int j = 0; j < A[i].size(); j++){
                row_sum += A[i][j] * x[j];
            }
            new_x[i] = x[i] * row_sum;
            total_sum += new_x[i];
        }

        for(int i = 0; i < x.size(); i++){
            aux = x[i];
            x[i] = new_x[i] / total_sum;
            aux -= x[i];

            distance += (aux * aux);
        }

    }while(distance > epsilon);

    return x;
}


double correlation_coefficient(const std::vector<double>& a, const std::vector<double>& b, const std::vector<double>& weight){
    double mab, ma, mb, ma2, mb2;
    int size = a.size();

    mab = ma = mb = ma2 = mb2 = 0;

    for(int i = 0; i < size; i++){
        mab += weight[i] * a[i] * b[i];
        ma += weight[i] * a[i];
        mb += weight[i] * b[i];
        ma2 += weight[i] * a[i] * a[i];
        mb2 += weight[i] * b[i] * b[i];
    }

    return (mab - ma * mb) / sqrt((ma2 - (ma * ma)) * (mb2 - (mb * mb)));
}


//Input: the initial gene expression data matrix data, f, a and the Threshold,
// void weightedCorrBicluster(Matrix data, std::vector<bool> flag_vector, double alpha, double threshold){
//     int n, m;
//     n = data.size();
//     m = data[0].size();


//     std::vector<double> feature_weight_vector(m, 1/m);                  // initialize the feature vector for the m conditions.

//     while(biclusters could be found){
//         for(int i = 0; i < 4; i++){
//             update_feature_weight(feature_weight_vector, flag_vector, alpha);
//             similarity_matrix = weighted_corr(data, feature_weight);            // compute the similarity matrix
//             std::vector<double> sorting_vector = dominant_set(similarity_matrix);                        // use dominant set approach to find the sorting vector
//             sorted_data = sort(data, sorting_vector);               // sort the rows of matrix data
//             data = transpose(sorted_data);
//             feature_weight_vector = sorting_vector;                 //update the feature weight vector
//         }
//         [newflag, BI] = find_bicluster(data, threshold);            //extract the bicluster from the sorted data matrix
//         Output BI;
//         flag_vector = newflag; // update the flag vector
//     }
// }


int main(){

    std::vector<std::vector<double> > A = {{2.,4.},{8.,4.}};

    for(auto& row : A){
        for(auto &e : row){
            std::cout << e << ' ';
        }
        std::cout << std::endl;
    }

    std::vector<double> x = dominant_set(A, 1e-4);

    for(auto &e : x){
        std::cout << e << ' ';
    }
    std::cout << std::endl;
}