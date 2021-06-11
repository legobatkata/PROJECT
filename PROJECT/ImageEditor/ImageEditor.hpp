#ifndef ImageEditor_hpp
#define ImageEditor_hpp

#include <iostream>
#include <cmath>
#include "../Image/Image.hpp"

/**
 Singleton class that takes care of editing images it is given.
 All of its functions have a strong exception guarantee by first creating a copy of the given Image's Pixel Matrix and then all changes are made to this new Matrix.
 If any problems come up, an exception is thrown and the new Matrix is deleted, while also preserving the original Image.
 If there are no problems, the new Matrix replaces the Image's old Pixel Matrix.
 */
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
    
    /**
     Resizes the Image using the formula from the article, given in the Project's task document.
     */
    void resize(Image& img, int newHeight, int newWidth);
    /**
     Calls resize(Image& img, int newHeight, int newWidth) with newHeight and newWidth modified properly according the given percentage;
     */
    void resize(Image& img, double percentage);
    /**
     Crops a rectangle from the passed Image according to given coordinates.
     If the described rectangle goes out of bounds of the Image, it the rectangle is properly resized so that it fits in the Image.
     throws an exception if the described rectangle has no intersection with the given Image.
     */
    void crop(Image& img, int lx, int ly, int rx, int ry);
    /**
     Convert a given Image's pixels to grayscale.
     Note that this function only converts the pixels, but does not change the Image's type.
     That means that if i have a pixelmap Image, using grayscale on it does not change its typet to a graymap, but only its Pixels.
     */
    void grayscale(Image& img);
    
    
    
    /**
     Error diffusion dithering methods have their own little error matrix, declared in the function itself.
     The function then goes through every pixel of the given image and overlays the error matrix over the original Image's Pixel Matrix.
     The currently observed pixel is given a value of either 0 or the Image's maxValue, depending on which it is closer to.
     Then, nearby Pixels increase or decrease in value, that is determined by the error made during the current Pixel's conversion and the coefficent given in the error matrix.
     This happens to all 3 color channels so that it works on both grayscale and colored images.
     */
    /**@{*/
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
    /**@}*/
    
    /**
     The Bayer matrix dithering methods have an n by m coefficent matrix that is declared in their function.
     They then go through the Image's Pixel Matrix by every n-th row and m-th column and overlay the coefficent matrix using the current Pixel as its top left corner.
     Then every pixel in the Image's Pixel Matrix is individually evaluated to either 0 or the Image's maxValue using the formula from this wikipedia article: https://en.wikipedia.org/wiki/Ordered_dithering.
     This happens to all 3 color channes so that the dither works on both grayscale and colored images.
     */
    /**@{*/
    void dither4x4(Image& img);
    void dither8x8(Image& img);
    /**@}*/
    
    
    
    
    
};


#endif
