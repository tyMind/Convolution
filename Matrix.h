#ifndef CONVOLUTION_MATRIX_H
#define CONVOLUTION_MATRIX_H

#include <iostream>
#include <vector>

class Matrix{
private:
    int m_row;
    int m_col;
    std::vector<std::vector<int>>m_matx;

public:
    Matrix():m_row(0), m_col(0){}
    Matrix(int row, int col);
    std::vector<std::vector<int>> getSubMatrix(int startRow, int startCol, int endRow, int endCol) const; //seperate the submatrix from
                                                                                                    //the main matrix on which the
                                                                                                    //kernel must run(in each step
                                                                                                    //there are different submatrices)
    std::vector<std::vector<int>> getMatrix() const;  //get the matrix from matrix object
    int getRow() const;
    int getCol() const;

    void setMatrix(const std::vector<std::vector<int>>&outMatx);   //"copy" outMatx matrix into Matrix object's m_matx
    void setRowColVal(int row, int col);    //set the number of rows and columns in matrix object
    void printMatrix();

    void fillRandNums(); //push random numbers into m_matx, those numbers can be from the range 0 to 9

    static void writeNumOfMatrices(const std::string &fileName, int numOfMatrices);    //write how many matrices you want to insert into the file
    void writeToFile(const std::string &fileName); //write a matrix to a file
    static std::vector<Matrix> readFromFile(const std::string &fileName);    //read all matrices from file and push it to the vector

    Matrix applyFilter(const Matrix &b);   //apply filter on a Matrix object
    Matrix dotProduct(const std::vector<std::vector<int>>&subMatrix, const Matrix &b);

};

#endif //CONVOLUTION_MATRIX_H
