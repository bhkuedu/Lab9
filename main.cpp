#include "matrix.hpp"
#include <iostream>
#include <fstream>



int main(int argc, char *argv[]) {
    std::ifstream file;
    std::string filename;
    
    std::cout << "Enter the filename: "; // ask user for file name
    std::cin >> filename;

    file.open(filename); // try to open file, may not be open
    
    if (!file.is_open()) { // couldnt open file for some reason? is it the right file? does it exist? who cares let the user find out!
        std::cerr << "Failed to open file." << std::endl; // tell our user we couldnt do jack
        return 1;
    }

    
    int N;
    int type;
    file >> N; // get matrix size
    file >> type; // Gets type. 0 for integer, 1 for double-precision matrices.

    
    if (N < 0)
        throw std::invalid_argument("Matrix size cannot be invalid!");

    file.ignore(); // make sure to blank this newline
    
    if (type == 0)  { // Integer type
        Matrix<int> matrix1(N);
        Matrix<int> matrix2(N);


        // shove in values from file into matrix 1
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int num;
                file >> num;

                matrix1.set_value(i, j, num);
            }
        }

        file.ignore(); // dont mind newline

        // shove in values from file into matrix 2 this time
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int num;
                file >> num;

                matrix2.set_value(i, j, num);
            }
        }

        std::cout << std::endl << "Matrix 1:" << std::endl << std::endl;
        matrix1.print_matrix();

        std::cout << std::endl << "Matrix 2:" << std::endl << std::endl;
        matrix2.print_matrix();


        // matrix info

        // Aditional testing stuff
        // // sum
        // Matrix matrix_sum = matrix1 + matrix2;
        // std::cout << "sum of both:" << std::endl;
        // matrix_sum.print_matrix();

        // // product
        // Matrix matrix_product = matrix1 * matrix2;
        // std::cout << "product of both (matrix 1 first):" << std::endl;
        // matrix_product.print_matrix();

        // // diagonal major/minor
        // std::cout << "matrix 1 diagonal major:" << matrix1.sum_diagonal_major() << std::endl;
        // std::cout << "matrix 2 diagnonal minor:" << matrix1.sum_diagonal_minor() << std::endl;

        // // swap row
        // matrix1.swap_rows(1, 2);
        // std::cout << "matrix 1, swapping row 1 and 2" << std::endl;
        // matrix1.print_matrix();

        // // swap columb
        // matrix1.swap_cols(0, 1);
        // std::cout << "matrix 1 after swapping columns 0 and 1:" << std::endl;
        // matrix1.print_matrix();

        // // update rows
        // matrix1.update_rows(0, 1, 100);
        // std::cout << "matrix 1 after updating rows with row 0 column 1, and the value of 100: " << std::endl;
        // matrix1.print_matrix();
        
    } else { // Double type
        Matrix<double> matrix1(N);
        Matrix<double> matrix2(N);


        // shove in values from file into matrix 1
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                double num;
                file >> num;

                matrix1.set_value(i, j, num);
            }
        }

        file.ignore(); // dont mind newline

        // shove in values from file into matrix 2 this time
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                double num;
                file >> num;

                matrix2.set_value(i, j, num);
            }
        }
        
        std::cout << std::endl << "Matrix 1:" << std::endl << std::endl;
        matrix1.print_matrix();

        std::cout << std::endl << "Matrix 2:" << std::endl << std::endl;
        matrix2.print_matrix();


        // matrix info

        // Aditional testing stuff
        // // sum
        // Matrix matrix_sum = matrix1 + matrix2;
        // std::cout << "sum of both:" << std::endl;
        // matrix_sum.print_matrix();

        // // product
        // Matrix matrix_product = matrix1 * matrix2;
        // std::cout << "product of both (matrix 1 first):" << std::endl;
        // matrix_product.print_matrix();

        // // diagonal major/minor
        // std::cout << "matrix 1 diagonal major:" << matrix1.sum_diagonal_major() << std::endl;
        // std::cout << "matrix 2 diagnonal minor:" << matrix1.sum_diagonal_minor() << std::endl;

        // // swap row
        // matrix1.swap_rows(1, 2);
        // std::cout << "matrix 1, swapping row 1 and 2" << std::endl;
        // matrix1.print_matrix();

        // // swap columb
        // matrix1.swap_cols(0, 1);
        // std::cout << "matrix 1 after swapping columns 0 and 1:" << std::endl;
        // matrix1.print_matrix();

        // // update rows
        // matrix1.update_rows(0, 1, 100.10);
        // std::cout << "matrix 1 after updating rows with row 0 column 1, and the value of 100.10:" << std::endl;
        // matrix1.print_matrix();
        
    }
    
    file.close(); // gotta close the file since we're done with it

    // matrix info - defined aboved in each if conditional branch
    

    return 0;
}
