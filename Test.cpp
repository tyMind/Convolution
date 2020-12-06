#include "Test.h"
#include "Matrix.h"

int Test::getMatricesNum(const std::string &fileName){
    return Matrix::readFromFile(fileName).size();
}

std::vector<Matrix> Test::getMatrices(const std::string &fileName) {
    return Matrix::readFromFile(fileName);
}

bool Test::compareMatricesNum(int writeMatricesNum, const std::string &fileName) {
    int readMatricesNum=getMatricesNum(fileName);
    if(readMatricesNum==writeMatricesNum){
        return true;
    }
    return false;
}

bool Test::compareMatrices(const std::vector<Matrix> &writtenMatrices, const std::string &fileName) {
    auto readMatrices=Test::getMatrices(fileName);
    if(writtenMatrices.size()!=readMatrices.size()){
        return false;
    }
    for(int i=0; i<writtenMatrices.size(); i++){
        auto getWrittenMatrix=writtenMatrices[i].getMatrix();
        auto getReadMatrix=readMatrices[i].getMatrix();
        if((getWrittenMatrix.size()!=getReadMatrix.size()) || (getWrittenMatrix[i].size()!=getReadMatrix[i].size())){
            return false;
        }

        for(int j=0; j<getWrittenMatrix.size(); j++){
            for(int k=0; k<getWrittenMatrix[j].size(); k++){
                if(getWrittenMatrix[j][k]!=getReadMatrix[j][k]){
                    return false;
                }
            }
        }
    }
    return true;
}

void Test::test(const std::string &fileName, int writeNum, std::vector<Matrix> &writtenMatrices) {
    bool compMatricesNum=compareMatricesNum(writeNum, fileName);
    if(compMatricesNum){
        std::cout<<"Test 1 passed\n";
    }
    else{
        std::cout<<"Test 1 failed\n";
    }
    bool compareMatrices=Test::compareMatrices(writtenMatrices, fileName);
    if(compareMatrices==1){
        std::cout<<"Test 2 passed\n";
    }
    else{
        std::cout<<"Test 2 failed\n";
    }
}