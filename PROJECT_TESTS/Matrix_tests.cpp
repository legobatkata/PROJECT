#include "catch2.hpp"
#include "../PROJECT/Matrix/Matrix.hpp"

TEST_CASE("constructors / rule of 3"){
    SECTION("rows and cols constructor"){
        Matrix<int> m(3, 4);
        REQUIRE(m.getRows() == 3);
        REQUIRE(m.getCols() == 4);
    }
    SECTION("rows and cols constructor, incorrect data"){
        bool didThrow = false;
        try{
            Matrix<int> m(0, 4);
        } catch(const std::exception& e){
            didThrow = true;
        }
        REQUIRE(didThrow);
    }
    SECTION("rows and cols constructor, incorrect data 2"){
        bool didThrow = false;
        try{
            Matrix<int> m(4, -4);
        } catch(const std::exception& e){
            didThrow = true;
        }
        REQUIRE(didThrow);
    }
    SECTION("copy constructor"){
        Matrix<int> m(6, 5);
        Matrix<int> m2(m);
        REQUIRE(m2.getRows() == 6);
        REQUIRE(m2.getCols() == 5);
    }
    SECTION("copy assignment"){
        Matrix<int> m(6, 5);
        Matrix<int> m2 = m;
        REQUIRE(m2.getRows() == 6);
        REQUIRE(m2.getCols() == 5);
    }
}

TEST_CASE("content filling / at()"){
    Matrix<int> t(3, 3);
    
    for(int i=0;i<3; i++){
        for(int j=0;j<3;j++){
            t.at(i, j) = i+j;
        }
    }
    
    bool isOk = true;
    for(int i=0;i<3; i++){
        for(int j=0;j<3;j++){
            if(t.at(i, j) != i+j) isOk = false;
        }
    }
    
    REQUIRE(isOk);
}

