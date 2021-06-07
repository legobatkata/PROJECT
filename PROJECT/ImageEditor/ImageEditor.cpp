#include "ImageEditor.hpp"



void ImageEditor::resize(Image& img, int newHeight, int newWidth){
    
    Matrix<Pixel>* newArr = new Matrix<Pixel>(newHeight, newWidth);
    
    for(int i=0;i<newHeight; i++){
        
        for(int j=0; j<newWidth; j++){
            
            int srcH = (int)round((double)i / (double)newHeight * (double)img.height);
            int srcW = (int)round((double)j / (double)newWidth * (double)img.width);
            
            if(srcH > img.height-1) srcH = img.height-1;
            if(srcW > img.width-1) srcW = img.width-1;
            
            newArr->at(i, j).red = img.arr->at(srcH, srcW).red;
            newArr->at(i, j).green = img.arr->at(srcH, srcW).green;
            newArr->at(i, j).blue = img.arr->at(srcH, srcW).blue;
            
        }
        
    }
    
    delete img.arr;
    img.arr = newArr;
    img.height = newHeight;
    img.width = newWidth;
    
}
void ImageEditor::resize(Image& img, double percentage){
    resize(img, (int)((double)img.height * percentage/100), (int)((double)img.width * percentage/100));
}


void ImageEditor::crop(Image& img, int lx, int ly, int rx, int ry){
    
    int trueLy = std::min(ly, ry);
    int trueLx = std::min(lx, rx);
    int trueRy = std::max(ly, ry);
    int trueRx = std::max(lx, rx);
    
    if(trueLx >= img.width || trueLy >= img.height){
        // maybe should throw exception here
        std::cout<<"invalid cropping coordinates\n";
        return;
    }
    
    int endX = std::min(trueRx, img.width);
    int endY = std::min(trueRy, img.height);
    
    int newHeight = endY - trueLy;
    int newWidth = endX - trueLx;
    
    Matrix<Pixel> *newArr = new Matrix<Pixel>(newHeight, newWidth);
    
    
    for(int i=0; i<newHeight; i++){
        for(int j=0; j<newWidth; j++){
            if(i+trueLy < img.height && i+trueLy>=0 && j+trueLx<img.width && j+trueLx>=0)
                newArr->at(i, j) = img.arr->at(i+trueLy, j+trueLx);
            else {
                // maybe should throw exception here
                std::cout<<"error while croppinng\n";
                delete newArr;
                return;
            }
        }
    }
    
    delete img.arr;
    img.arr = newArr;
    img.height = newHeight;
    img.width = newWidth;
}



void ImageEditor::greenCake(Image& img){
    for(int i=0;i<img.height;i++){
        for(int j=0; j<img.width; j++){
            int color = img.arr->at(i, j).red*0.21 + img.arr->at(i, j).green*0.72 + img.arr->at(i, j).blue*0.07;
            img.arr->at(i, j).red = color;
            img.arr->at(i, j).green = color;
            img.arr->at(i, j).blue = color;
        }
    }
}


void ImageEditor::dither1d(Image& img){
    int mat[1][2] = {
        0, 1
    };
    
    Matrix<Pixel>* newArr = new Matrix<Pixel>(*img.arr);
    
    
    try{
        for(int i=0; i<img.height; i++)
            for(int j=0; j<img.width; j++){
                diffusePixelsByMatrix<1, 2>(*newArr, i, j, (int)img.maxValue, mat, 0, 1);
                evaluatePixelAt(*newArr, i, j, (int)img.maxValue);
            }
    } catch(const std::exception& e){
        throw std::invalid_argument("error while editing image");
    }
    
    delete img.arr;
    img.arr = newArr;
    
}

void ImageEditor::ditherFloyd(Image& img){
     
    int mat[2][3] = {
        0, 0, 7,
        3, 5, 1
    };
    
    Matrix<Pixel>* newArr = new Matrix<Pixel>(*img.arr);
    
    try{
        for(int i=0; i<img.height; i++){
            
            for(int j=0; j<img.width; j++){
                
                diffusePixelsByMatrix<2, 3>(*newArr, i, j, (int)img.maxValue, mat, 1, 16);
                evaluatePixelAt(*newArr, i, j, (int)img.maxValue);
                
            }
        }
    } catch(const std::exception& e){
        throw std::invalid_argument("error while editing image");
    }

    delete img.arr;
    img.arr = newArr;
}


void ImageEditor::ditherFakeFloyd(Image& img){
    int mat[2][2] = {
        0, 3,
        3, 2,
    };
    
    Matrix<Pixel>* newArr = new Matrix<Pixel>(*img.arr);
    
    try{
        for(int i=0; i<img.height; i++){
            
            for(int j=0; j<img.width; j++){
                
                diffusePixelsByMatrix<2, 2>(*newArr, i, j, (int)img.maxValue, mat, 0, 8);
                evaluatePixelAt(*newArr, i, j, (int)img.maxValue);
                
            }
        }
    } catch(const std::exception& e){
        throw std::invalid_argument("error while editing image");
    }

    delete img.arr;
    img.arr = newArr;
}

void ImageEditor::ditherJJN(Image& img){
    int mat[3][5] = {
        0, 0, 0, 7, 5,
        3, 5, 7, 5, 3,
        1, 3, 5, 3, 1
    };
    
    
    Matrix<Pixel>* newArr = new Matrix<Pixel>(*img.arr);
    
    try{
        for(int i=0; i<img.height; i++){
            
            for(int j=0; j<img.width; j++){
                
                diffusePixelsByMatrix<3, 5>(*newArr, i, j, (int)img.maxValue, mat, 2, 48);
                evaluatePixelAt(*newArr, i, j, (int)img.maxValue);
                
            }
        }
    } catch(const std::exception& e){
        throw std::invalid_argument("error while editing image");
    }

    delete img.arr;
    img.arr = newArr;
}


void ImageEditor::ditherStucki(Image& img){
    int mat[3][5] = {
        0, 0, 0, 8, 4,
        2, 4, 8, 4, 2,
        1, 2, 4, 2, 1
    };
    
    Matrix<Pixel>* newArr = new Matrix<Pixel>(*img.arr);
    
    try{
        for(int i=0; i<img.height; i++){
            
            for(int j=0; j<img.width; j++){
                
                diffusePixelsByMatrix<3, 5>(*newArr, i, j, (int)img.maxValue, mat, 2, 42);
                evaluatePixelAt(*newArr, i, j, (int)img.maxValue);
                
            }
        }
    } catch(const std::exception& e){
        throw std::invalid_argument("error while editing image");
    }

    delete img.arr;
    img.arr = newArr;
}


void ImageEditor::ditherAtkinson(Image& img){
    int mat[3][4] = {
        0, 0, 1, 1,
        1, 1, 1, 0,
        0, 1, 0, 0
    };
    
    Matrix<Pixel>* newArr = new Matrix<Pixel>(*img.arr);
    
    try{
        for(int i=0; i<img.height; i++){
            
            for(int j=0; j<img.width; j++){
                
                diffusePixelsByMatrix<3, 4>(*newArr, i, j, (int)img.maxValue, mat, 1, 8);
                evaluatePixelAt(*newArr, i, j, (int)img.maxValue);
                
            }
        }
    } catch(const std::exception& e){
        throw std::invalid_argument("error while editing image");
    }

    delete img.arr;
    img.arr = newArr;
    
}


void ImageEditor::ditherBurkes(Image& img){
    int mat[2][5] = {
        0, 0, 0, 8, 4,
        2, 4, 8, 4, 2
    };
    
    Matrix<Pixel>* newArr = new Matrix<Pixel>(*img.arr);
    
    try{
        for(int i=0; i<img.height; i++){
            
            for(int j=0; j<img.width; j++){
                
                diffusePixelsByMatrix<2, 5>(*newArr, i, j, (int)img.maxValue, mat, 2, 32);
                evaluatePixelAt(*newArr, i, j, (int)img.maxValue);
                
            }
        }
    } catch(const std::exception& e){
        throw std::invalid_argument("error while editing image");
    }

    delete img.arr;
    img.arr = newArr;
}



void ImageEditor::ditherSierra(Image& img){
    int mat[3][5] = {
        0, 0, 0, 5, 3,
        2, 4, 5, 4, 2,
        0, 2, 3, 2, 0
    };
    
    Matrix<Pixel>* newArr = new Matrix<Pixel>(*img.arr);
    
    try{
        for(int i=0; i<img.height; i++){
            
            for(int j=0; j<img.width; j++){
                
                diffusePixelsByMatrix<3, 5>(*newArr, i, j, (int)img.maxValue, mat, 2, 32);
                evaluatePixelAt(*newArr, i, j, (int)img.maxValue);
                
            }
        }
    } catch(const std::exception& e){
        throw std::invalid_argument("error while editing image");
    }

    delete img.arr;
    img.arr = newArr;
}


void ImageEditor::ditherSierraTwoRow(Image& img){
    int mat[2][5] = {
        0, 0, 0, 4, 3,
        1, 2, 3, 2, 1,
    };
    
    Matrix<Pixel>* newArr = new Matrix<Pixel>(*img.arr);
    
    try{
        for(int i=0; i<img.height; i++){
            
            for(int j=0; j<img.width; j++){
                
                diffusePixelsByMatrix<2, 5>(*newArr, i, j, (int)img.maxValue, mat, 2, 16);
                evaluatePixelAt(*newArr, i, j, (int)img.maxValue);
                
            }
        }
    } catch(const std::exception& e){
        throw std::invalid_argument("error while editing image");
    }

    delete img.arr;
    img.arr = newArr;
}


void ImageEditor::ditherSierraLite(Image& img){
    int mat[2][3] = {
        0, 0, 2,
        1, 1, 0
    };
    
    Matrix<Pixel>* newArr = new Matrix<Pixel>(*img.arr);
    
    try{
        for(int i=0; i<img.height; i++){
            
            for(int j=0; j<img.width; j++){
                
                diffusePixelsByMatrix<2, 3>(*newArr, i, j, (int)img.maxValue, mat, 1, 4);
                evaluatePixelAt(*newArr, i, j, (int)img.maxValue);
                
            }
        }
    } catch(const std::exception& e){
        throw std::invalid_argument("error while editing image");
    }

    delete img.arr;
    img.arr = newArr;
}

void ImageEditor::dither4x4(Image& img){
    int mat[4][4] = {
        0, 8, 2, 10,
        12, 4, 14, 6,
        3, 11, 1, 9,
        15, 7, 13, 5
    };
    
    Matrix<Pixel>* newArr = new Matrix<Pixel>(*img.arr);
    
    try{
        for(int i=0; i<img.height; i++){
            
            for(int j=0; j<img.width; j++){
                
                if(i%4 == 0  && j%4 == 0){
                    diffuseInBlock<4, 4>(*newArr, i, j, (int)img.maxValue, mat, -1, 16);
                }
                
            }
        }
    } catch(const std::exception& e){
        throw std::invalid_argument("error while editing image");
    }

    delete img.arr;
    img.arr = newArr;
}

void ImageEditor::dither8x8(Image& img){
    int mat[8][8] = {
         0, 32,  8, 40,  2, 34, 10, 42,
        48, 16, 56, 24, 50, 18, 58, 26,
        12, 44,  4, 36, 14, 46,  6, 38,
        60, 28, 52, 20, 62, 30, 54, 22,
         3, 35, 11, 43,  1, 33,  9, 41,
        51, 19, 59, 27, 49, 17, 57, 25,
        15, 47,  7, 39, 13, 45,  5, 37,
        63, 31, 55, 23, 61, 29, 53, 21
    };
    
    Matrix<Pixel>* newArr = new Matrix<Pixel>(*img.arr);
    
    try{
        for(int i=0; i<img.height; i++){
            
            for(int j=0; j<img.width; j++){
                
                if(i%8 == 0  && j%8 == 0){
                    diffuseInBlock<8, 8>(*newArr, i, j, (int)img.maxValue, mat, -1, 64);
                }
                
            }
        }
    } catch(const std::exception& e){
        throw std::invalid_argument("error while editing image");
    }

    delete img.arr;
    img.arr = newArr;
}






template<int mRows, int mCols>
void ImageEditor::diffusePixelsByMatrix(Matrix<Pixel>& arr, int curRow, int curCol, int maxValue, int matrix[mRows][mCols], int offset, int diviser){
    
    for(int i=0; i<mRows; i++){
        for(int j=(i==0)?offset+1:0; j<mCols; j++){
        
            
            if(curRow+i < arr.getRows() && curRow+i >= 0 && curCol+j - offset < arr.getCols() && curCol+j - offset >= 0){
                if((int)arr.at(curRow, curCol).red <= maxValue/2){
                        arr.at(curRow+i, curCol+j-offset).red = arr.at(curRow+i, curCol+j-offset).red + (int)((double)arr.at(curRow, curCol).red / diviser * matrix[i][j]);
                }else{
                        arr.at(curRow+i, curCol+j-offset).red = arr.at(curRow+i, curCol+j-offset).red + (int)(((double)arr.at(curRow, curCol).red - (double)maxValue) / diviser * matrix[i][j]);
                }
                
                if((int)arr.at(curRow, curCol).green <= maxValue/2){
                        arr.at(curRow+i, curCol+j-offset).green = arr.at(curRow+i, curCol+j-offset).green + (int)((double)arr.at(curRow, curCol).green / diviser * matrix[i][j]);
                }else{
                        arr.at(curRow+i, curCol+j-offset).green = arr.at(curRow+i, curCol+j-offset).green + (int)(((double)arr.at(curRow, curCol).green - (double)maxValue) / diviser * matrix[i][j]);
                }
                
                if((int)arr.at(curRow, curCol).blue <= maxValue/2){
                        arr.at(curRow+i, curCol+j-offset).blue = arr.at(curRow+i, curCol+j-offset).blue + (int)((double)arr.at(curRow, curCol).blue / diviser * matrix[i][j]);
                }else{
                        arr.at(curRow+i, curCol+j-offset).blue = arr.at(curRow+i, curCol+j-offset).blue + (int)(((double)arr.at(curRow, curCol).blue - (double)maxValue) / diviser * matrix[i][j]);
                }
                /*
                if((int)img.arr->at(curRow, curCol).green <= (int)img.maxValue/2){
                        img.arr->at(curRow+i, curCol+j-offset).green = img.arr->at(curRow+i, curCol+j-offset).green + (int)((double)img.arr->at(curRow, curCol).green / diviser * matrix[i][j]);
                }else{
                        img.arr->at(curRow+i, curCol+j-offset).green = img.arr->at(curRow+i, curCol+j-offset).green + (int)(((double)img.arr->at(curRow, curCol).green - (double)img.maxValue) / diviser * matrix[i][j]);
                }
                
                if((int)img.arr->at(curRow, curCol).blue <= (int)img.maxValue/2){
                        img.arr->at(curRow+i, curCol+j-offset).blue = img.arr->at(curRow+i, curCol+j-offset).blue + (int)((double)img.arr->at(curRow, curCol).blue / diviser * matrix[i][j]);
                }else{
                        img.arr->at(curRow+i, curCol+j-offset).blue = img.arr->at(curRow+i, curCol+j-offset).blue + (int)(((double)img.arr->at(curRow, curCol).blue - (double)img.maxValue) / diviser * matrix[i][j]);
                }*/
            }
            
        }
    }
    
    
}



template<int mRows, int mCols>
void ImageEditor::diffuseInBlock(Matrix<Pixel>& arr, int curRow, int curCol, int maxValue, int matrix[mRows][mCols], int offset, int diviser){
    
    for(int i=0; i<mRows; i++){
        for(int j=(i==0)?offset+1:0; j<mCols; j++){
            if(curRow+i < arr.getRows() && curRow+i >= 0 && curCol+j - offset < arr.getCols() && curCol+j - offset >= 0){
                
                
                arr.at(curRow+i, curCol+j-offset).red = arr.at(curRow+i, curCol+j-offset).red + (int)((double)maxValue/1.2*((double)matrix[i][j]/(double)diviser - 0.5));
                arr.at(curRow+i, curCol+j-offset).green = arr.at(curRow+i, curCol+j-offset).green + (int)((double)maxValue/1.2*((double)matrix[i][j]/(double)diviser - 0.5));
                arr.at(curRow+i, curCol+j-offset).blue = arr.at(curRow+i, curCol+j-offset).blue + (int)((double)maxValue/1.2*((double)matrix[i][j]/(double)diviser - 0.5));
                
                evaluatePixelAt(arr, curRow+i, curCol+j-offset, maxValue);
            }
        }
    }
    
    
}


void ImageEditor::evaluatePixelAt(Matrix<Pixel>& arr, int curRow, int curCol, int maxValue){
    if((int)arr.at(curRow, curCol).red <= (int)maxValue/2){
        arr.at(curRow, curCol).red = 0;
    } else {
        arr.at(curRow, curCol).red = (int)maxValue;
    }
    
    if((int)arr.at(curRow, curCol).green <= (int)maxValue/2){
        arr.at(curRow, curCol).green = 0;
    } else {
        arr.at(curRow, curCol).green = (int)maxValue;
    }
    
    if((int)arr.at(curRow, curCol).blue <= (int)maxValue/2){
        arr.at(curRow, curCol).blue = 0;
    } else {
        arr.at(curRow, curCol).blue = (int)maxValue;
    }
}
