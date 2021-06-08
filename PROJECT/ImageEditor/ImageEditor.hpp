#ifndef ImageEditor_hpp
#define ImageEditor_hpp

#include <iostream>
#include <cmath>
#include "../Image/Image.hpp"

class ImageEditor{
private:
    ImageEditor(){};
    
    void evaluatePixelAt(Matrix<Pixel>& arr, int curRow, int curCol, int maxValue);
    
    template<int mRows, int mCols>
    void diffusePixelsByMatrix(Matrix<Pixel>& arr, int curRow, int curCol, int maxValue, int matrix[mRows][mCols], int offset, int diviser);
    
    template<int mRows, int mCols>
    void diffuseInBlock(Matrix<Pixel>& arr, int curRow, int curCol, int maxValue, int matrix[mRows][mCols], int offset, int diviser);
    
public:
    ImageEditor(const ImageEditor&) = delete;
    ImageEditor& operator =(const ImageEditor&) = delete;

    static ImageEditor& getInstance(){
        static ImageEditor instance;
        return instance;
    }
    
    void grayscale(Image& img);
    void resize(Image& img, int newHeight, int newWidth);
    void resize(Image& img, double percentage);
    void crop(Image& img, int lx, int ly, int rx, int ry);
    
    void dither1d(Image& img);
    void ditherFloyd(Image& img);
    void ditherFakeFloyd(Image& img);
    void ditherJJN(Image& img);
    void ditherStucki(Image& img);
    void ditherAtkinson(Image& img);
    void ditherBurkes(Image& img);
    void ditherSierra(Image& img);
    void ditherSierraTwoRow(Image& img);
    void ditherSierraLite(Image& img);
    void dither4x4(Image& img);
    void dither8x8(Image& img);
    
    
    
};


#endif
