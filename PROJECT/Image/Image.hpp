#ifndef Image_hpp
#define Image_hpp

#include <iostream>
#include <fstream>
#include "../Utils/Utils.hpp"
#include "../Matrix/Matrix.hpp"

struct Pixel{
    int red{};
    int green{};
    int blue{};
    Pixel() = default;
    Pixel(int r, int g, int b);
    /**
     Creates a pixel and fills all of its values with the same int.
     This is mainly used in bitmap and graymap images (P1, P2, P4, P5) because even though these formats need only one color channel, the program still saves them in an RGB pixel.
     */
    void setAll(int color);
    /**
     Creates a pixel from a given hex string,
     if the given string is not valid (aka doesn's start with a '#', has more than 6 characters, contains non hex values, etc ... ) throws an exception.
     */
    Pixel(std::string hexStr);
};

enum ImgType{
    /**
     ascii bitmap
     */
    P1,
    /**
     ascii graymap
     */
    P2,
    /**
     ascii pixelmap
     */
    P3,
    /**
     binary bitmap
     */
    P4,
    /**
     binary graymap
     */
    P5,
    /**
     binary pixelmap
     */
    P6
};


class ImageEditor;

class Image {
private:
    std::string currentPath = "\0";
    ImgType type{};
    int width{};
    int height{};
    int maxValue = 1;
    Matrix<Pixel>* arr;
    
    ImgType strToType(const std::string& typeStr);
    std::string typeToStr(const ImgType& type);
    
    void readHeader(std::ifstream& ifstr);
    void readData(std::ifstream& ifstr);
    void writeHeader(std::ofstream& ofstr);
    void writeData(std::ofstream& ofstr);
public:
    /**
     deleted
     */
    Image() = delete;
    /**
     First reads the header of the file.
     If the file does not exist or the header of the file is not correct, throws an exception.
     The function then creates a new Pixel Matrix and fills it by reading the raster from the file according to its type.
     */
    Image(const std::string& path);
    /**
     Creates a new Pixel Matrix for the Image according to given width and height.
     It then fills the new Matrix with Pixels with the given color.
     An exception is thrown if width or height are <= 0 and if the given hex string is not a valid hex rgb string.
     */
    Image(int width, int height, const std::string& hexCode);
    /**
     Calls delete on the pixel matrix, thus freeing the allocated in heap memory
     */
    ~Image();
    
    /**
     Writes the header params to file at given path.
     After that, writes the Pixel Matrix to the file according to the Image's type.
     If no problems arise, sets the given path as the Image's currentPath.
     If the extention at the end of the given path does not match the Image's type or doesn't exist at all, throws an exception.
     */
    void saveAs(const std::string& path);
    /**
     Calls the saveAs function with currentPath.
     If there is no currentPath, throws an exception.
     */
    void save();
    
    ImgType getType()const;
    int getWidth()const;
    int getHeight()const;
    int getMaxValue()const;
    
    
    /**
     Due to the nature of image editing algorithms, the ImageEditor class has to have access to almost all of Image's private parameters, so it is declared as a friend class.
     */
    friend class ImageEditor;
};

#endif
