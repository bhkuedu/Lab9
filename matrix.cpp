#include "matrix.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstddef>
// implementation of functions declared in matrix.hpp goes here
// function definitions for a class have their names prefixed with
// the class name and "::"


// e.g. for the constructor:

// construct matrix of size n (columns and rows)
template<typename Data>
Matrix<Data>::Matrix(size_t n) {
    this->size = n; // Set rows/columns size
    data = new Data*[n]; // allocate data on heap for rows
    
    for (size_t i = 0; i < n; ++i) { // iterate through rows to allocate columns
        data[i] = new Data[n]; // allocate column on heap
        std::fill(data[i], data[i] + n, 0); // fill column with 0s
    }
} 

// e.g. for a member function:

// Prints matrix out
template<typename Data>
void Matrix<Data>::print_matrix() const {
    size_t max_width = 0;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            size_t width = std::to_string(data[i][j]).length();
            if (width > max_width) {
                max_width = width;
            }
        }
    }
    
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            std::cout << std::setw(max_width) << data[i][j] << " "; // output individual matrix elements
        }
        std::cout << std::endl; // Print newline so we can move on to the next row
    }
}


// Instantiate matrix from vector of values 
template<typename Data>
Matrix<Data>::Matrix(std::vector<std::vector<Data>> nums) {
    size = nums.size();
    data = new Data*[size];
    
    for (size_t i = 0; i < size; ++i) {
        data[i] = new Data[size];

        if (nums[i].size() != size)
            throw std::invalid_argument("Row size does not match column size!");
        
        for (size_t j = 0; j < size; ++j) {
            data[i][j] = nums[i][j]; // Because we're using 
        }
    }
} 

template<typename Data>
Matrix<Data> Matrix<Data>::operator+(const Matrix<Data> &rhs) const {
    if (this->get_size() != rhs.get_size())
        throw std::invalid_argument("Matrices are not the same size!");
    Matrix result(rhs.size); // Create new matrix of same size

    
    
    for (size_t i = 0; i < rhs.size; ++i) {
        for (size_t j = 0; j < rhs.size; ++j) {
            result.data[i][j] = rhs.data[i][j] + this->data[i][j]; // We add every element from A (this) and B (rhs) to create the element for our new matrix
        }

    }
    return result; // Return new matrix (result of addition)
}

template<typename Data>
Matrix<Data> Matrix<Data>::operator*(const Matrix<Data> &rhs) const {
    if (this->get_size() != rhs.get_size()) // Don't need to check rows or columns size because our matrices are all square ones!
        throw std::invalid_argument("Matrices are not the same size!");

    Matrix<Data> result(this->size); // Create new matrix (will be same size bc of how matrix multiplication works with same-sized square matrices)
    
    for (size_t i = 0; i < this->size; ++i) { // Iterate over row of this matrix
        for (size_t j = 0; j < rhs.size; ++j) { // Iterate over column of other matrix
            // As per how matrix multiplication works, every element or our other matrix will correspond to the row of the first matrix and the column of the second multiplied.
            // The row, and column, in this sense, are decided by the position of the element we're trying to calculate
            // So, element i, j is the summation of the smaller elements we find from i and j!
            for (size_t element = 0; element < this->size; ++element) {
                result.data[i][j] += this->data[i][element] * rhs.data[element][j];
            }
        }
    }
    
    return result; // Return new matrix (result of multiplicatio)
}

template<typename Data>
void Matrix<Data>::set_value(std::size_t i, std::size_t j, Data value) {
    if (i < 0 || j < 0 || i >= this->get_size() || j >= this->get_size())
        throw std::out_of_range("Out of range of matrix!");
    
    this->data[i][j] = value; // sets value at row i, column j to 'value'

    // this->print_matrix();
}

template<typename Data>
Data Matrix<Data>::get_value(std::size_t i, std::size_t j) const {
    if (i < 0 || j < 0 || i >= this->get_size() || j >= this->get_size())
        throw std::out_of_range("Out of range of matrix!");
    return this->data[i][j]; // gets value at row i, column j
}

template<typename Data>
Data Matrix<Data>::get_size() const {
    return this->size; // return matrix size
}

template<typename Data>
Data Matrix<Data>::sum_diagonal_major() const {
    Data sum = 0;
    
    for (size_t i = 0; i < this->size; ++i) {
        sum += this->data[i][i]; // We move across the diagonal, so we only need to index by i in both the row and the column!
        // This is only correct because we're in a diagonal matrix.
    }
    
    return sum; // return sum
}

template<typename Data>
Data Matrix<Data>::sum_diagonal_minor() const {
    Data sum = 0;
    
    for (size_t i = 0; i < this->size; ++i) {
        sum += this->data[i][this->size - 1 - i]; // Minor is flipped across the vertical axis compared to major. We need to go from max column to min column, so we subtract from the size of the matrix! 
    }
    
    return sum; // return minor sum
}

template<typename Data>
void Matrix<Data>::swap_rows(std::size_t r1, std::size_t r2) {
    if (r1 < 0 || r2 < 0 || r1 >= this->get_size() || r2 >= this->get_size())
        throw std::out_of_range("Out of range of matrix!");
    // C++ allows us to do this with the standard library!
    // It's exactly what it looks like... we're swapping the memory from r1 and r2!
    std::swap(this->data[r1], this->data[r2]);

    // this->print_matrix(); // print resulting matrix
}

template<typename Data>
void Matrix<Data>::swap_cols(std::size_t c1, std::size_t c2) {
    if (c1 < 0 || c2 < 0 || c1 >= this->get_size() || c2 >= this->get_size())
        throw std::out_of_range("Out of range of matrix!");
    
    // Like the swap row function, we can similarly use the swap method here.
    // However, since columns span multiple different pointers, we have to iterate through each colum and swap the individual entries manually!
    for (size_t i = 0; i < this->size; ++i) {
        std::swap(this->data[i][c1], this->data[i][c2]); // Swap element from one column to the other
    }

    // this->print_matrix(); // Print resulting matrix
} 



