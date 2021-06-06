#include "catch2.hpp"
#include "../PROJECT/Matrix/Matrix.hpp"

TEST_CASE("lksajd"){
    Matrix<int> a(3, 4);
    for(int i=0;i<3; i++){
        for(int j=0;j<4;j++){
            a.at(i, j) = i+j;
        }
    }
    
    Matrix<int> b = a;
    
    b.print();
}

