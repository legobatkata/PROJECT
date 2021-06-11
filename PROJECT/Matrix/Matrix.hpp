#ifndef Matrix_hpp
#define Matrix_hpp

#include <iostream>

/**
 Template class that creates and manages an n by m matrix of whatever class is given to it as a template.
 Used mainly as a holder for the Image class's Pixels.
 */
template<class T>
class Matrix{
private:
    T** m;
    int rows = 0;
    int cols = 0;
    
    void releaseByRows(int m_rows);
    void allocate();
    void copy(const Matrix& newM);
public:
    Matrix() = delete;
    Matrix(int rows, int cols);
    ~Matrix();
    Matrix<T>& operator =(const Matrix<T>& newM);
    Matrix(const Matrix<T>& newM);
    
    T& at(int i, int j);
    const T& at(int i, int j) const;
    
    int getRows() const;
    int getCols() const;
};


template <class T>
void Matrix<T>::releaseByRows(int m_rows){
    for(int i=0; i<m_rows;i++){
        delete[] m[i];
    }
    delete[] m;
}

template <class T>
void Matrix<T>::allocate(){
    m = new T*[rows];
    if(!m) throw std::invalid_argument("could not allocate memory for members");
        
    for(int i=0; i<rows; i++){
        m[i] = new T[cols];
        if(!m[i]){
            releaseByRows(i);
        }
    }
}

template <class T>
void Matrix<T>::copy(const Matrix<T>& newM){
    if(!(rows == 0 || cols == 0))
        releaseByRows(rows);
    rows = newM.rows;
    cols = newM.cols;
    allocate();
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            m[i][j] = newM.at(i, j);
        }
    }
}

template <class T>
Matrix<T>& Matrix<T>::operator =(const Matrix<T>& newM){
    if(this != &newM) copy(newM);
    return *this;
}
template <class T>
Matrix<T>::Matrix(const Matrix<T>& newM){
    copy(newM);
}


template <class T>
Matrix<T>::Matrix(int rows, int cols){
    if(rows <= 0 || cols <= 0) throw std::invalid_argument("cannot allocate a matrix with given parameters");
    this->rows = rows;
    this->cols = cols;
    allocate();
}

template <class T>
Matrix<T>::~Matrix(){
    releaseByRows(rows);
}

template <class T>
T& Matrix<T>::at(int i, int j){
    return m[i][j];
}

template <class T>
const T& Matrix<T>::at(int i, int j) const{
    return m[i][j];
}

template <class T>
int Matrix<T>::getRows() const {
    return rows;
}

template <class T>
int Matrix<T>::getCols() const {
    return cols;
}

/*
template <class T>
void Matrix<T>::print() const{
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            std::cout<<m[i][j]<<" ";
        }
        std::cout<<"\n";
    }
}
 */

#endif
