#include "Matrix.h"
#include <time.h>
#include <fstream>
#include <sstream>

Matrix::Matrix(int row, int col):m_row(row), m_col(col){
    m_matx=std::vector<std::vector<int>>(m_row, std::vector<int>(m_col));
    fillRandNums();    //initializes main matrix
}

std::vector<std::vector<int>> Matrix::getMatrix() {
    return m_matx;
}

std::vector<std::vector<int>> Matrix::getSubMatrix(int startRow, int startCol, int endRow, int endCol){
    std::vector<std::vector<int>>subMatrix;
    for(int i=startRow; i<endRow; i++){
        std::vector<int>rowLine;
        for(int j=startCol; j<endCol; j++){
            rowLine.push_back(m_matx[i][j]);
        }
        subMatrix.push_back(rowLine);
    }
    return subMatrix;
}

void Matrix::setMatrix(std::vector<std::vector<int>> outMatx) {
    int rowSize=outMatx.size();
    int colSize=outMatx[0].size();

    for(int i=0; i<rowSize; i++){
        m_matx.push_back(std::vector<int>());
        for(int j=0; j<colSize; j++){
            m_matx[i].push_back(outMatx[i][j]);
        }
    }
}

void Matrix::setRowColVal(int row, int col) {
    m_row=row;
    m_col=col;
}

void Matrix::printMatrix() {
    for(int i=0; i<m_row; i++){
        for(int j=0; j<m_col; j++){
            std::cout<<m_matx[i][j]<<" ";
        }
        std::cout<<'\n';
    }
    std::cout<<'\n';
}

void Matrix::fillRandNums() {
    srand(time(NULL));
    int num;
    for(int i=0; i<m_row; i++){
        m_matx.push_back(std::vector<int>(m_col));
        for(int j=0; j<m_col; j++){
            num=rand()%2;
            m_matx[i][j]=num;
        }
    }
}

void Matrix::writeNumOfMatrices(std::string fileName, int numOfMatrices) {
//    int prevNumOfMatrices=0;
//    std::ifstream inFile(fileName);
//    if(!inFile.is_open()){
//        std::cout<<"Couldn't open the file: "<<fileName<<'\n';
//    }
//    else{
//        inFile>>prevNumOfMatrices;
//    }

    std::fstream outFile;
    outFile.open(fileName, std::fstream::out);
    outFile<<numOfMatrices;
    outFile<<std::endl;
    outFile.close();
//    inFile.close();
}

void Matrix::writeToFile(std::string fileName) {
    std::fstream outFile;
    outFile.open(fileName, std::fstream::out | std::fstream::app);
    outFile<<m_row<<" "<<m_col<<" ";
    outFile<<std::endl;

    for (int i = 0; i < m_row; i++) {
        for (int j = 0; j < m_col; j++) {
            outFile << m_matx[i][j] << " ";
        }
        outFile<<std::endl;
    }
    outFile<<std::endl;
    outFile.close();
}

std::vector<Matrix> Matrix::readFromFile(std::string fileName) {
    std::ifstream inFile;
    inFile.open(fileName, std::fstream::in);
    std::string line;

    int rowSize=0, colSize=0;


    int rowInFile=1;
    int nextMatrixRow=2;    //next matrix row in file
    int value=0;
    int getMatSize=0;

    std::getline(inFile, line);
    std::stringstream lineStream(line);
    if(rowInFile==1){
        rowInFile++;
        while(lineStream>>value){
            getMatSize=value;
        }
    }

    std::vector<Matrix>matrices(getMatSize);
//    std::vector<std::vector<std::vector<int>>>matrices(getMatSize);
    int matrixIt=-1;
    while(std::getline(inFile, line) && matrixIt<getMatSize){
        std::vector<int>lineData;
        std::stringstream lineStream(line);
        static int colIt=0;
        if(line!=""){
            if(rowInFile==nextMatrixRow){
                int i=0;
                while(lineStream>>value){
                    if(i==0){
                        rowSize=value;
                        matrices[matrixIt+1].m_row=rowSize;
                        rowInFile++;
                    }
                    else{
                        colSize=value;
                        matrices[matrixIt+1].m_col=colSize;
                    }
                    i++;
                }
                nextMatrixRow=rowInFile+rowSize+1;
                matrixIt+=1;
            }

            else{
                //push matrix elements into the vector
                while(lineStream>>value) {
                    lineData.push_back(value);
                }
                matrices[matrixIt].m_matx.push_back(lineData);
            }
            rowInFile++;
        }

    }
    return matrices;
}

Matrix Matrix::applyFilter(Matrix b) {
    Matrix retMatrix;
    int retMatRowSize=(this->m_row)-(b.m_row)+1;
    int retMatColSize=(this->m_col)-(b.m_col)+1;
    retMatrix.setRowColVal(retMatRowSize, retMatColSize);
    retMatrix.m_matx=std::vector<std::vector<int>>(retMatRowSize);    //maybe resizing would be better
    auto filterMatrix=b.getMatrix();
    for(int i=0; i<retMatRowSize; i++){
        for(int j=0; j<retMatColSize; j++){
            int count=0;
            auto subMatrix=getSubMatrix(i, j, i+b.m_row, j+b.m_col);
            for(int row=0; row<b.m_row; row++){
                for(int col=0; col<b.m_col; col++){
                    if(subMatrix[row][col]==1 && subMatrix[row][col]==filterMatrix[row][col]){
                        count++;
                    }
                }
            }
        retMatrix.m_matx[i].push_back(count);
        }
    }
    return retMatrix;
}

Matrix Matrix::dotProduct(std::vector<std::vector<int>>subMatrix, Matrix b){
    auto filterMatrix=b.getMatrix();
//    Matrix returnMatx(filterMatrix.size(), filterMatrix[0].size());
    Matrix returnMatx;
    returnMatx.setRowColVal(filterMatrix.size(), filterMatrix[0].size());
    int sum=0;
    std::vector<std::vector<int>>outMatx(subMatrix.size());
    for(int i=0; i<subMatrix[0].size(); i++){
        for(int j=0; j<filterMatrix.size(); j++){
            outMatx[i].push_back(subMatrix[i][j]*filterMatrix[j][i]);
        }
    }
    returnMatx.setMatrix(outMatx);
    return returnMatx;

}