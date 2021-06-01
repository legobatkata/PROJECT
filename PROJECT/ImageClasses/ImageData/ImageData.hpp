#include <iostream>
#include "../../Utils/Utils.hpp"
#include "../ImageHeader/ImageHeader.hpp"

struct Pixel{
    std::size_t red{};
    std::size_t green{};
    std::size_t blue{};
    Pixel() = default;
    Pixel(std::size_t r, std::size_t g, std::size_t b);
};



class ImageData{
protected:
    Pixel** arr{};
    std::size_t rows{};
    std::size_t cols{};
    
    void allocate();
    void release();
    
public:
    ImageData() = default;
    ImageData(ImageHeader& header);
    
    void readData(std::ifstream& ifstr, ImgType type);
    void printData();
    
    
    
};
