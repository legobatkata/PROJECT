#ifndef ImageEditor_hpp
#define ImageEditor_hpp

#include <iostream>
#include "../Image/Image.hpp"

class ImageEditor{
private:
    ImageEditor(){};
    
    template<int mRows, int mCols>
    void penis(Image& img, int curRow, int curCol, int matrix[mRows][mCols], int offset, int diviser);
    
public:
    ImageEditor(const ImageEditor&) = delete;
    ImageEditor& operator =(const ImageEditor&) = delete;

    static ImageEditor& getInstance(){
        static ImageEditor instance;
        return instance;
    }
    
    void greenCake(Image& img);
    
    void dither1(Image& img);
    void ditherFloydStanberg(Image& img);
    void betterFloyd(Image& img);
    void ditherJJN(Image& img);
    
    
};


#endif
