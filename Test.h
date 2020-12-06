#ifndef CONVOLUTION_TEST_H
#define CONVOLUTION_TEST_H

#include <iostream>
#include "Matrix.h"

struct Test {
    //check if the numOfMatrices has been read correctly
    static int getMatricesNum(const std::string &fileName);

    static std::vector<Matrix> getMatrices(const std::string &fileName);

    //check if the matrix has been read correctly
    static bool compareMatricesNum(int writeNum, const std::string &fileName);
    static bool compareMatrices(const std::vector<Matrix>&writtenMatrices, const std::string &fileName);

    static void test(const std::string &fileName, int writeNum, std::vector<Matrix>&writtenMatrices);
};


#endif //CONVOLUTION_TEST_H
