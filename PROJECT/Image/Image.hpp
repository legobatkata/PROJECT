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
    void setAll(int color);
    Pixel(std::string hexStr);
};

enum ImgType{
    P1, P2, P3, P4, P5, P6
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
    Image() = delete;
    ~Image();
    Image(const std::string& path);
    Image(int width, int height, const std::string& hexCode);
    
    void saveAs(const std::string& path);
    void save();
    
    ImgType getType()const;
    int getWidth()const;
    int getHeight()const;
    int getMaxValue()const;
    
    friend class ImageEditor;
};

#endif
