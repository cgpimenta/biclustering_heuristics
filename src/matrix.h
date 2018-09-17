#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <ostream>


class Matrix{
private:
    std::vector<std::vector<double> > matrix;
    std::vector<int> row_index;
    std::vector<int> col_index;
    bool is_transposed;
    int rows, cols;

public:
    Matrix(int rows, int cols);
    Matrix(const std::vector<std::vector<double> >&);

    inline unsigned int size() { return this->matrix.size(); }

    inline std::pair<int, int> dimension() const{
        return (this->is_transposed) ? std::pair<int, int>(cols, rows) : std::pair<int, int>(rows, cols);
    }


    inline void transpose() { this->is_transposed = !this->is_transposed; };

    inline std::vector<double>& operator[](int i) { return matrix[i]; };
    inline const std::vector<double>& operator[](int i) const { return matrix[i]; };

    double& operator()(int i, int j){
        return (this->is_transposed) ?
            matrix[row_index[j]][col_index[i]] :
            matrix[row_index[i]][col_index[j]];
    }

    const double& operator()(int i, int j) const {
        return (this->is_transposed) ?
            matrix[row_index[j]][col_index[i]] :
            matrix[row_index[i]][col_index[j]];
    }


    void resetIndex();

    void weighted_row_sort(const std::vector<double>& weight);


    friend std::ostream& operator<<(std::ostream&, const Matrix&);
};


#endif