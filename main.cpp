#include <iostream>
#include <vector>

#include "Matrix.h"

int main(){
    int numOfMatrices, numOfFilters;
    std::cout<<"Write the number of input matrices that you want to create: ";
    std::cin>>numOfMatrices;

    std::cout<<"Write the number of input filters that you want to create: ";
    std::cin>>numOfFilters;

    std::string matFileName;
    std::cout<<"Specify the filename that you want to write the matrices in: ";
    std::cin>>matFileName;
    Matrix::writeNumOfMatrices(matFileName, numOfMatrices);


    std::string filtersFileName;
    std::cout<<"Specify the filename that you want to write the filters in: ";
    std::cin>>filtersFileName;
    Matrix::writeNumOfMatrices(filtersFileName, numOfFilters);

    std::vector<Matrix>writeMatrices(numOfMatrices);
    std::vector<Matrix>writeFilters(numOfFilters);

    //fill in matrices vector and write it to the file
    int numOfRows, numOfCols;

    for(int i=0; i<numOfMatrices; i++){
        std::cout<<"Write the dimensions of the matrix, number of rows and columns respectively: ";

        std::cin>>numOfRows>>numOfCols;
        writeMatrices[i].setRowColVal(numOfRows, numOfCols);
        writeMatrices[i].fillRandNums();
        writeMatrices[i].writeToFile(matFileName);
    }

    for(int i=0; i<numOfFilters; i++){
        std::cout<<"Write the dimensions of the filter matrix, number of rows and columns respectively: ";
        std::cin>>numOfRows>>numOfCols;
        writeFilters[i].setRowColVal(numOfRows, numOfCols);
        writeFilters[i].fillRandNums();
        writeFilters[i].writeToFile(filtersFileName);
    }

    //reading from file
    std::cout<<"Read matrices from: "<<matFileName<<'\n';
    std::vector<Matrix>readMatrices=Matrix::readFromFile(matFileName);
    for(int matIt=0; matIt<readMatrices.size(); matIt++){
        for(int i=0; i<readMatrices[matIt].getMatrix().size(); i++){
            for(int j=0; j<readMatrices[matIt].getMatrix()[0].size(); j++){
                std::cout<<readMatrices[matIt].getMatrix()[i][j]<<" ";
            }
            std::cout<<'\n';
        }
    }

    std::cout<<"Read filters from: "<<filtersFileName<<'\n';
    Matrix m;
    std::vector<Matrix>readFilters=Matrix::readFromFile(filtersFileName);

    for(int filterIt=0; filterIt<readFilters.size(); filterIt++){
        for(int i=0; i<readFilters[filterIt].getMatrix().size(); i++){
            for(int j=0; j<readFilters[filterIt].getMatrix()[0].size(); j++){
                std::cout<<readFilters[filterIt].getMatrix()[i][j]<<" ";
            }
            std::cout<<'\n';
        }
    }

    //convolution part
    Matrix out;
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
        out.setRowColVal(readMatrices[mainMatIndex].getRow()-(readFilters[filterMatIndex].getRow())+1,
                         readMatrices[mainMatIndex].getCol()-(readFilters[filterMatIndex].getCol())+1);
        out=readMatrices[mainMatIndex].applyFilter(readFilters[filterMatIndex]);
    }
    out.printMatrix();

    std::string outFileName;
    std::cout<<"Write the file name that you want to write the matrix: ";
    std::cin>>outFileName;
    out.writeToFile(outFileName);

//    int toDeleteFile=0;
//    std::cout<<"Please input true if you want to delete the files that you have created, else false: ";
//    std::cin>>toDeleteFile;
//
//    if(toDeleteFile==1){
//        if(std::remove(matFileName.c_str())){
//            std::cout<<matFileName<<" was deleted successfully\n";
//        }
//        else{
//            std::cout<<"there was an error during the deletion of file "<<matFileName<<'\n';
//        }
//        if(std::remove(filtersFileName.c_str())){
//            std::cout<<filtersFileName<<" was deleted successfully\n";
//        }
//        else{
//            std::cout<<"there was an error during the deletion of file "<<filtersFileName<<'\n';
//        }
//    }
//    else{
//        std::cout<<"There was no file deletion specified\n";
//    }
}