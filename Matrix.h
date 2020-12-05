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
    Matrix(){}
    Matrix(int row, int col);
    std::vector<std::vector<int>> getSubMatrix(int startRow, int startCol, int endRow, int endCol);
    std::vector<std::vector<int>> getMatrix();
    int getRow(){
        return m_row;
    }
    int getCol(){
        return m_col;
    }
    void setMatrix(std::vector<std::vector<int>>outMatx);
    void setRowColVal(int row, int col);
    void printMatrix();

    void fillRandNums(); //push random numbers into m_matx

    static void writeNumOfMatrices(std::string fileName, int numOfMatrices);    //write how many matrices you want to insert into the file
    void writeToFile(std::string fileName);
    static std::vector<Matrix> readFromFile(std::string fileNam);    //read all matrixes from file and push it to the vector
//    void updateMatrix();

    Matrix applyFilter(Matrix b);
    Matrix dotProduct(std::vector<std::vector<int>>subMatrix, Matrix b);

};

#endif //CONVOLUTION_MATRIX_H
