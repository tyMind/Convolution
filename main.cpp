#include <iostream>
#include <vector>

#include "Matrix.h"
#include "Test.h"

void deleteFiles(const std::string &matrixFileName, const std::string &filterFileName){
    std::cout<<"Delete input files after the operations on them\n";
    if(std::remove(matrixFileName.c_str())==0){
        std::cout<<matrixFileName<<" was deleted successfully\n";
    }
    else{
        std::cout<<"there was an error during the deletion of file "<<matrixFileName<<'\n';
    }
    if(std::remove(filterFileName.c_str())==0){
        std::cout<<filterFileName<<" was deleted successfully\n";
    }
    else{
        std::cout<<"there was an error during the deletion of file "<<filterFileName<<'\n';
    }
}

std::vector<std::vector<int>> userMatrix(int rowNum, int colNum){
    std::vector<std::vector<int>>retUserMatrix(rowNum);
    int num;
    std::cout<<"Input the matrix on the next steps\n";
    for(int i=0; i<rowNum; i++){
        std::cout<<"Input the elements of row: "<<i<<'\n';
        for(int j=0; j<colNum; j++){
            std::cin>>num;
            retUserMatrix[i].push_back(num);
        }
    }
    return retUserMatrix;
}

int main(){
    int numOfMatrices, numOfFilters;
    std::cout<<"Write the number of input matrices that you want to create: ";
    std::cin>>numOfMatrices;

    std::cout<<"Write the number of input filters that you want to create: ";
    std::cin>>numOfFilters;

    std::string matrixFileName;
    std::cout<<"Specify the filename that you want to write the matrices in: ";
    std::cin>>matrixFileName;
    Matrix::writeNumOfMatrices(matrixFileName, numOfMatrices);

    std::string filterFileName;
    std::cout<<"Specify the filename that you want to write the filters in: ";
    std::cin>>filterFileName;
    Matrix::writeNumOfMatrices(filterFileName, numOfFilters);

    std::vector<Matrix>writeMatrices(numOfMatrices);
    std::vector<Matrix>writeFilters(numOfFilters);

    //fill in matrices vector and write it to the file
    int numOfRows, numOfCols;


    for(int i=0; i<numOfMatrices; i++){
        std::cout<<"Write the dimensions of the matrix, number of rows and columns respectively: ";
        std::cin>>numOfRows>>numOfCols;
        writeMatrices[i].setRowColVal(numOfRows, numOfCols);

        int randomFill=0;
        std::cout<<"Please specify 1 if you want to input the matrices yourself, or 0 if you want the application to create "
                   "randomized matrices with the given sizes: ";
        std::cin>>randomFill;
        if(!randomFill){
            writeMatrices[i].fillRandNums();
        }
        else{
            writeMatrices[i].setMatrix(userMatrix(numOfRows, numOfCols));
        }
        writeMatrices[i].writeToFile(matrixFileName);
    }

    for(int i=0; i<numOfFilters; i++){
        std::cout<<"Write the dimensions of the filter matrix, number of rows and columns respectively: ";
        std::cin>>numOfRows>>numOfCols;
        writeFilters[i].setRowColVal(numOfRows, numOfCols);
        int randomFill=0;
        std::cout<<"Please specify 1 if you want to input the matrix yourself, or 0 if you want the application to create "
                   "it using random elements: ";
        std::cin>>randomFill;
        if(!randomFill){
            writeFilters[i].fillRandNums();
        }
        else{
            writeFilters[i].setMatrix(userMatrix(numOfRows, numOfCols));
        }
        writeFilters[i].writeToFile(filterFileName);
    }

    //reading both main and filter matrices from files and printing them out
    std::cout<<"Read matrices from: "<<matrixFileName<<'\n';
    std::vector<Matrix>readMatrices=Matrix::readFromFile(matrixFileName);
    for(int i=0; i<readMatrices.size(); i++){
        readMatrices[i].printMatrix();
    }

    std::cout<<"Read filters from: "<<filterFileName<<'\n';
    Matrix m;
    std::vector<Matrix>readFilters=Matrix::readFromFile(filterFileName);

    for(int i=0; i<readFilters.size(); i++){
        readFilters[i].printMatrix();
    }

    //convolution part
    Matrix originalMatrix;
    int filterMatIndex, mainMatIndex;
    std::cout<<"Input the main matrix index that you would like to apply the filter on: ";
    std::cin>>mainMatIndex;
    std::cout<<"Input the filter matrix index that you would like to apply on the main matrix: ";
    std::cin>>filterMatIndex;

    if(mainMatIndex>numOfMatrices){
        std::cout<<"There is no matrix with "<<mainMatIndex<<" index\n";
        return -1;
    }
    else if(filterMatIndex>numOfFilters){
        std::cout<<"There is no filter with "<<filterMatIndex<<" index\n";
        return -1;
    }
    else{
        originalMatrix=readMatrices[mainMatIndex];
        std::cout<<"Original matrix\n";
        originalMatrix.printMatrix();
        Matrix firstFilteredMatrix=originalMatrix.applyFilter(readFilters[filterMatIndex]);
        std::cout<<"Matrix after the first filter\n";
        firstFilteredMatrix.printMatrix();

        std::string outFileName;
        std::cout<<"Write the file name that you want to write the matrix: ";
        std::cin>>outFileName;
        firstFilteredMatrix.writeToFile(outFileName);
    }

    //Test several operation results
    Test::test(matrixFileName, numOfMatrices, writeMatrices);

    deleteFiles(matrixFileName, filterFileName);

}