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
    void setAll(int color){
        red = color;
        green = color;
        blue = color;
    }
};

enum ImgType{
    P1, P2, P3, P4, P5, P6
};


class ImageEditor;

class Image {
private:
    ImgType type{};
    int width{};
    int height{};
    int maxValue = 0;
    
    //Pixel*** arr{};
    Matrix<Pixel>* arr;
    
    //void allocatePixels();
    //void releasePixels();
    
    ImgType strToType(const std::string& typeStr);
    std::string typeToStr(const ImgType& type);
    
    
    void readHeader(std::ifstream& ifstr);
    void readData(std::ifstream& ifstr);
    void writeHeader(std::ofstream& ofstr);
    void writeData(std::ofstream& ofstr);
public:
    Image() = delete;
    ~Image();
    //Image(const Image& img);
    Image(std::string& path);
    //Image(ImageHeader& h);
    
    
    void save(std::string& path);
    
    void printHeader();
    void printData();
    
    
    friend class ImageEditor;
};

#endif
