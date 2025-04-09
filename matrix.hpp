#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <cstdint>
#include <vector>
#include <cstddef>

// all of your function definitions should be in this file now

template<typename Data>
class Matrix {
protected:
    size_t size;
    Data** data;
public:
    Matrix(std::size_t N);
    Matrix(std::vector<std::vector<Data>> nums);

    Matrix operator+(const Matrix &rhs) const;
    Matrix operator*(const Matrix &rhs) const;
    void set_value(std::size_t i, std::size_t j, Data n);
    Data get_value(std::size_t i, std::size_t j) const;
    Data get_size() const;
    Data sum_diagonal_major() const;
    Data sum_diagonal_minor() const;
    void swap_rows(std::size_t r1, std::size_t r2);
    void swap_cols(std::size_t c1, std::size_t c2);
    void print_matrix() const;
};

#endif // __MATRIX_HPP__
