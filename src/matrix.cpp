#include "matrix.h"
#include <numeric>
#include <algorithm>


MatrixT::MatrixT(int rows, int cols){
    this->matrix = std::vector<std::vector<double>>(rows, std::vector<double>(cols));
    this->is_transposed = false;
    this->rows = rows;
    this->cols = cols;

    this->row_index = std::vector<int>(rows);
    this->col_index = std::vector<int>(cols);

    this->resetIndex();
}


MatrixT::MatrixT(const std::vector<std::vector<double> > &matrix){
    this->matrix = matrix;
    this->is_transposed = false;
    this->rows = matrix.size();
    this->cols = matrix[0].size();

    this->row_index = std::vector<int>(rows);
    this->col_index = std::vector<int>(cols);

    this->resetIndex();
}


void MatrixT::resetIndex(){
    std::iota(this->row_index.begin(), this->row_index.end(), 0);
    std::iota(this->col_index.begin(), this->col_index.end(), 0);
}


void MatrixT::weighted_row_sort(const std::vector<double>& weight){
    std::vector<int> &line_index = (this->is_transposed) ? this->col_index : this->row_index;

    std::vector<int> index(line_index.size());
    std::iota(index.begin(), index.end(), 0);

    std::vector<int> new_index(line_index.size());
    
    // std::cout << "weight ";
    // for(auto &e : weight){
    //     std::cout << e << ' ';
    // }
    // std::cout << std::endl;

    // std::cout << "Index ";
    // for(auto &e : line_index){
    //     std::cout << e << ' ';
    // }
    // std::cout << std::endl;
    // for(auto &e : index){
    //     std::cout << e << ' ';
    // }
    // std::cout << std::endl;
    // std::cout << std::endl;

    std::sort(index.begin(), index.end(), 
          [&weight](const int &i, const int &j) { return weight[i] < weight[j]; });

    for(unsigned int i = 0; i < line_index.size(); i++){
        // std::cout << "index[" << i << "]=" << index[i] << ". line_index[" << index[i] << "]=" << line_index[index[i]] << std::endl;
        new_index[i] = line_index[index[i]];
    }

    line_index = new_index;
}


std::ostream& operator<<(std::ostream& out, const MatrixT& m){
    int first_size = (m.is_transposed) ? m.cols : m.rows;
    int second_size = (m.is_transposed) ? m.rows : m.cols;

    for(int i = 0; i < first_size; i++){
        for(int j = 0; j < second_size; j++){
            out << m(i, j) << ' ';
        }
        out << std::endl;
    }

    return out;
}
