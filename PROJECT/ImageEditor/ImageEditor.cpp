#include "ImageEditor.hpp"


void ImageEditor::greenCake(Image& img){
    for(int i=0;i<img.height;i++){
        for(int j=0; j<img.width; j++){
            int color = img.arr[i][j].red*0.21 + img.arr[i][j].green*0.72 + img.arr[i][j].blue*0.07;
            img.arr[i][j].red = color;
            img.arr[i][j].green = color;
            img.arr[i][j].blue = color;
        }
    }
}



void ImageEditor::dither1(Image& img){
    for(int i=0;i<img.height;i++){
        int errorR = 0;
        int errorG = 0;
        int errorB = 0;
        for(int j=0; j<img.width; j++){
            
            // red
            if((int)img.arr[i][j].red + errorR <= (int)img.maxValue/2){
                errorR += (int)img.arr[i][j].red;
                img.arr[i][j].red = 0;
            }else{
                errorR += (int)img.arr[i][j].red - (int)img.maxValue;
                img.arr[i][j].red = (int)img.maxValue;
            }
            
            // green
            if((int)img.arr[i][j].green + errorG <= (int)img.maxValue/2){
                errorG += (int)img.arr[i][j].green;
                img.arr[i][j].green = 0;
            }else{
                errorG += (int)img.arr[i][j].green - (int)img.maxValue;
                img.arr[i][j].green = (int)img.maxValue;
            }
            
            // blue
            if((int)img.arr[i][j].blue + errorB <= (int)img.maxValue/2){
                errorB += (int)img.arr[i][j].blue;
                img.arr[i][j].blue = 0;
            }else{
                errorB += (int)img.arr[i][j].blue - (int)img.maxValue;
                img.arr[i][j].blue = (int)img.maxValue;
            }
        }
    }
}



void ImageEditor::ditherFloydStanberg(Image& img){
    for(int i=0;i<img.height;i++){
        for(int j=0; j<img.width; j++){
            
            // red
            if((int)img.arr[i][j].red <= (int)img.maxValue/2){
                if(j+1<img.width){
                    img.arr[i][j+1].red = (img.arr[i][j+1].red + (img.arr[i][j].red / 16 * 7));
                }
                if(i+1<img.height){
                    img.arr[i+1][j].red = (img.arr[i+1][j].red + (img.arr[i][j].red / 16 * 5));
                }
                if(i+1<img.height && j+1<img.width){
                    img.arr[i+1][j+1].red = (img.arr[i+1][j+1].red + (img.arr[i][j].red / 16));
                }
                if(j-1>0 && i+1<img.height) {
                    img.arr[i+1][j-1].red = (img.arr[i+1][j-1].red + (img.arr[i][j].red / 16 * 3));
                }
                img.arr[i][j].red = 0;
            }else{
                if(j+1<img.width) {
                    img.arr[i][j+1].red = (img.arr[i][j+1].red + (img.arr[i][j].red - (int)img.maxValue ) / 16 * 7);
                }
                if(i+1<img.height) {
                    img.arr[i+1][j].red = (img.arr[i+1][j].red + (img.arr[i][j].red - (int)img.maxValue ) / 16 * 5);
                }
                if(i+1<img.height && j+1<img.width) {
                    img.arr[i+1][j+1].red = (img.arr[i+1][j+1].red + (img.arr[i][j].red - (int)img.maxValue ) / 16);
                }
                if(j-1>0 && i+1<img.height) {
                    img.arr[i+1][j-1].red = (img.arr[i+1][j-1].red + (img.arr[i][j].red - (int)img.maxValue ) / 16 * 3);
                }
                img.arr[i][j].red = (int)img.maxValue;
            }
            
            
            // green
            if((int)img.arr[i][j].green <= (int)img.maxValue/2){
                if(j+1<img.width){
                    img.arr[i][j+1].green = (img.arr[i][j+1].green + (img.arr[i][j].green / 16 * 7));
                }
                if(i+1<img.height){
                    img.arr[i+1][j].green = (img.arr[i+1][j].green + (img.arr[i][j].green / 16 * 5));
                }
                if(i+1<img.height && j+1<img.width){
                    img.arr[i+1][j+1].green = (img.arr[i+1][j+1].green + (img.arr[i][j].green / 16));
                }
                if(j-1>0 && i+1<img.height) {
                    img.arr[i+1][j-1].green = (img.arr[i+1][j-1].green + (img.arr[i][j].green / 16 * 3));
                }
                img.arr[i][j].green = 0;
            }else{
                if(j+1<img.width) {
                    img.arr[i][j+1].green = (img.arr[i][j+1].green + (img.arr[i][j].green - (int)img.maxValue ) / 16 * 7);
                }
                if(i+1<img.height) {
                    img.arr[i+1][j].green = (img.arr[i+1][j].green + (img.arr[i][j].green - (int)img.maxValue ) / 16 * 5);
                }
                if(i+1<img.height && j+1<img.width) {
                    img.arr[i+1][j+1].green = (img.arr[i+1][j+1].green + (img.arr[i][j].green - (int)img.maxValue ) / 16);
                }
                if(j-1>0 && i+1<img.height) {
                    img.arr[i+1][j-1].green = (img.arr[i+1][j-1].green + (img.arr[i][j].green - (int)img.maxValue ) / 16 * 3);
                }
                img.arr[i][j].green = (int)img.maxValue;
            }
            
            
            // blue
            if((int)img.arr[i][j].blue <= (int)img.maxValue/2){
                if(j+1<img.width){
                    img.arr[i][j+1].blue = (img.arr[i][j+1].blue + (img.arr[i][j].blue / 16 * 7));
                }
                if(i+1<img.height){
                    img.arr[i+1][j].blue = (img.arr[i+1][j].blue + (img.arr[i][j].blue / 16 * 5));
                }
                if(i+1<img.height && j+1<img.width){
                    img.arr[i+1][j+1].blue = (img.arr[i+1][j+1].blue + (img.arr[i][j].blue / 16));
                }
                if(j-1>0 && i+1<img.height) {
                    img.arr[i+1][j-1].blue = (img.arr[i+1][j-1].blue + (img.arr[i][j].blue / 16 * 3));
                }
                img.arr[i][j].blue = 0;
            }else{
                if(j+1<img.width) {
                    img.arr[i][j+1].blue = (img.arr[i][j+1].blue + (img.arr[i][j].blue - (int)img.maxValue ) / 16 * 7);
                }
                if(i+1<img.height) {
                    img.arr[i+1][j].blue = (img.arr[i+1][j].blue + (img.arr[i][j].blue - (int)img.maxValue ) / 16 * 5);
                }
                if(i+1<img.height && j+1<img.width) {
                    img.arr[i+1][j+1].blue = (img.arr[i+1][j+1].blue + (img.arr[i][j].blue - (int)img.maxValue ) / 16);
                }
                if(j-1>0 && i+1<img.height) {
                    img.arr[i+1][j-1].blue = (img.arr[i+1][j-1].blue + (img.arr[i][j].blue - (int)img.maxValue ) / 16 * 3);
                }
                img.arr[i][j].blue = (int)img.maxValue;
            }
         
        }
    }
}

void ImageEditor::betterFloyd(Image& img){
     
    int mat[2][3] = {
        0, 0, 7,
        3, 5, 1
    };
    
    for(int i=0; i<img.height; i++){
        
        for(int j=0; j<img.width; j++){
            
            penis<2, 3>(img, i, j, mat, 1, 16);
            
        }
    }
}

void ImageEditor::ditherJJN(Image& img){
    int mat[3][5] = {
        0, 0, 0, 7, 5,
        3, 5, 7, 5, 3,
        1, 3, 5, 3, 1
    };
    
    for(int i=0; i<img.height; i++){
        
        for(int j=0; j<img.width; j++){
            
            penis<3, 5>(img, i, j, mat, 2, 48);
            
        }
    }
}










template<int mRows, int mCols>
void ImageEditor::penis(Image& img, int curRow, int curCol, int matrix[mRows][mCols], int offset, int diviser){
    
    /*for(int i=0; i<mRows; i++){
        for(int j=(i==0)?offset+1:0; j<mCols; j++){
        
            if((int)img.arr[curRow][curCol].red <= (int)img.maxValue/2){
                if(curRow+i < img.height && curRow+i >= 0 && curCol+j - offset < img.width && curCol+j - offset >= 0){
                    img.arr[curRow+i][curCol+j-offset].red = img.arr[curRow+i][curCol+j-offset].red + (img.arr[curRow][curCol].red / diviser * matrix[i][j]);
                    img.arr[curRow+i][curCol+j-offset].green = img.arr[curRow+i][curCol+j-offset].green + (img.arr[curRow][curCol].green / diviser * matrix[i][j]);
                    img.arr[curRow+i][curCol+j-offset].blue = img.arr[curRow+i][curCol+j-offset].blue + (img.arr[curRow][curCol].blue / diviser * matrix[i][j]);
                }
            }else{
                if(curRow+i < img.height && curRow+i >= 0 && curCol+j - offset < img.width && curCol+j - offset >= 0){
                    img.arr[curRow+i][curCol+j-offset].red = img.arr[curRow+i][curCol+j-offset].red + (img.arr[curRow][curCol].red - (int)img.maxValue) / diviser * matrix[i][j];
                    img.arr[curRow+i][curCol+j-offset].green = img.arr[curRow+i][curCol+j-offset].green + (img.arr[curRow][curCol].green - (int)img.maxValue) / diviser * matrix[i][j];
                    img.arr[curRow+i][curCol+j-offset].blue = img.arr[curRow+i][curCol+j-offset].blue + (img.arr[curRow][curCol].blue - (int)img.maxValue) / diviser * matrix[i][j];
                }
            }
        }
        
    }
    
    if((int)img.arr[curRow][curCol].red <= (int)img.maxValue/2){
        img.arr[curRow][curCol].red = 0;
        img.arr[curRow][curCol].green = 0;
        img.arr[curRow][curCol].blue = 0;
    } else {
        img.arr[curRow][curCol].red = (int)img.maxValue;
        img.arr[curRow][curCol].green = (int)img.maxValue;
        img.arr[curRow][curCol].blue = (int)img.maxValue;
    }
    */
    
    for(int i=0; i<mRows; i++){
        for(int j=(i==0)?offset+1:0; j<mCols; j++){
        
            if((int)img.arr[curRow][curCol].red <= (int)img.maxValue/2){
                if(curRow+i < img.height && curRow+i >= 0 && curCol+j - offset < img.width && curCol+j - offset >= 0){
                    img.arr[curRow+i][curCol+j-offset].red = img.arr[curRow+i][curCol+j-offset].red + (img.arr[curRow][curCol].red / diviser * matrix[i][j]);
                }
            }else{
                if(curRow+i < img.height && curRow+i >= 0 && curCol+j - offset < img.width && curCol+j - offset >= 0){
                    img.arr[curRow+i][curCol+j-offset].red = img.arr[curRow+i][curCol+j-offset].red + (img.arr[curRow][curCol].red - (int)img.maxValue) / diviser * matrix[i][j];
                }
            }
            
            if((int)img.arr[curRow][curCol].green <= (int)img.maxValue/2){
                if(curRow+i < img.height && curRow+i >= 0 && curCol+j - offset < img.width && curCol+j - offset >= 0){
                    img.arr[curRow+i][curCol+j-offset].green = img.arr[curRow+i][curCol+j-offset].green + (img.arr[curRow][curCol].green / diviser * matrix[i][j]);
                }
            }else{
                if(curRow+i < img.height && curRow+i >= 0 && curCol+j - offset < img.width && curCol+j - offset >= 0){
                    img.arr[curRow+i][curCol+j-offset].green = img.arr[curRow+i][curCol+j-offset].green + (img.arr[curRow][curCol].green - (int)img.maxValue) / diviser * matrix[i][j];
                }
            }
            
            if((int)img.arr[curRow][curCol].blue <= (int)img.maxValue/2){
                if(curRow+i < img.height && curRow+i >= 0 && curCol+j - offset < img.width && curCol+j - offset >= 0){
                    img.arr[curRow+i][curCol+j-offset].blue = img.arr[curRow+i][curCol+j-offset].blue + (img.arr[curRow][curCol].blue / diviser * matrix[i][j]);
                }
            }else{
                if(curRow+i < img.height && curRow+i >= 0 && curCol+j - offset < img.width && curCol+j - offset >= 0){
                    img.arr[curRow+i][curCol+j-offset].blue = img.arr[curRow+i][curCol+j-offset].blue + (img.arr[curRow][curCol].blue - (int)img.maxValue) / diviser * matrix[i][j];
                }
            }
        }
    }
    
    if((int)img.arr[curRow][curCol].red <= (int)img.maxValue/2){
        img.arr[curRow][curCol].red = 0;
    } else {
        img.arr[curRow][curCol].red = (int)img.maxValue;
    }
    
    if((int)img.arr[curRow][curCol].green <= (int)img.maxValue/2){
        img.arr[curRow][curCol].green = 0;
    } else {
        img.arr[curRow][curCol].green = (int)img.maxValue;
    }
    
    if((int)img.arr[curRow][curCol].blue <= (int)img.maxValue/2){
        img.arr[curRow][curCol].blue = 0;
    } else {
        img.arr[curRow][curCol].blue = (int)img.maxValue;
    }
    
    
}
