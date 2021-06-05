#include <iostream>
#include "../Utils/Utils.hpp"
#include "../ImageHeader/ImageHeader.hpp"

struct Pixel{
    int red{};
    int green{};
    int blue{};
    Pixel() = default;
    Pixel(std::size_t r, std::size_t g, std::size_t b);
    void setAll(int color){
        red = color;
        green = color;
        blue = color;
    }
};

class ImageData : public ImageHeader{
protected:
    Pixel** arr{};
    
    void allocate();
    void release();
    
public:
    ImageData() = delete;
    ~ImageData();
    ImageData(std::string& path);
    
    void readData(std::ifstream& ifstr, ImgType type);
    void writeData(std::ofstream& ofstr, ImgType type);
    void printData();
    
};
