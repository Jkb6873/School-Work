#ifndef MATMULTIORDERING_H_INCLUDED
#define MATMULTIORDERING_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

class MatMultiOrdering {
public:
    explicit MatMultiOrdering(std::vector<int>&lengths);
    ~MatMultiOrdering();
    void print();
private:
    int bestCost_;
    int** m_;
    int** s_;
    size_t numMatrices_;
    std::vector<int>lengths_;
    void matrixChainOrder();
    void print(int i, int j, bool inAResult[], std::string& result);

};

std::string ToString(int x);

MatMultiOrdering::MatMultiOrdering(std::vector<int>&lengths){
    //get number of matrices from lengths
    numMatrices_ = lengths.size() - 1;
    //init m_ and s_
    m_ = new int*[numMatrices_];
    s_ = new int*[numMatrices_];
    for(unsigned int i = 0; i < numMatrices_; ++i){
        m_[i] = new int[numMatrices_];
        s_[i] = new int[numMatrices_];
        for(unsigned int j = 0; j < numMatrices_; ++j){
            m_[i][j] = 0;
            s_[i][j] = 0;
        }
    }
    //move lengths into Matrix Multiplication Ordering Class
    this->lengths_ = move(lengths);
    //calculate best order
    matrixChainOrder();
}

MatMultiOrdering:: ~MatMultiOrdering(){
    for(int i = 0; i < numMatrices_; i++){
        delete[] m_[i];
        delete[] s_[i];
    }
    delete[] m_;
    delete[] s_;
}


void MatMultiOrdering:: matrixChainOrder(){
    for (unsigned int i = 1; i < numMatrices_; i++) {
        //for i = 1 to i = n
        for (unsigned int j = 0; j < numMatrices_ - i; j++) {
            //for j = 0 to j = n - i
            int k = j + i;
            m_[j][k] = 9999999;
            //mutiplying matrix j * matrix k = 999999
            for (int l = j; l < k; l++) {
                int cost = m_[j][l] + m_[l+1][k] + lengths_[j]*lengths_[l+1]*lengths_[k+1];
                if (cost < m_[j][k]) {
                    m_[j][k] = cost;
                    s_[j][k] = l;
                }
            }
        }
    }
}

void MatMultiOrdering::print(){
    bool inAResult[numMatrices_];
    for (unsigned int i = 0; i < numMatrices_; i++)
        inAResult[i] = false;
    std::string result = "";
    print(0, numMatrices_ - 1, inAResult, result);
    std::cout << result << " = " << m_[0][numMatrices_-1] << " multiplications" << std::endl;
}

void MatMultiOrdering::print(int i, int j, bool inResult[], std::string& result){
    if (i != j) {
        print(i, s_[i][j], inResult, result);
        print(s_[i][j] + 1, j, inResult, result);
        if(!inResult[i] && !inResult[j])
            result = result + "( m" + ToString(i) + " * m" + ToString(j) + " )";
        else if (inResult[i] && !inResult[j]){
            result.insert(result.find("m" + ToString((i)) + " "), "( ");
            result = result + " * m" + ToString(j) + " )";
        }
        else if (inResult[j] && !inResult[i]){
            result.insert(result.find("m" + ToString((j)) + " ")+4, " )");
            result = "( m" + ToString(i) + " * " + result;
        }

        inResult[i] = true;
        inResult[j] = true;
    }
}
std::string ToString(int x){
    std::stringstream output;
    output << x;
    return output.str();
}
#endif // MATMULTIORDERING_H_INCLUDED
