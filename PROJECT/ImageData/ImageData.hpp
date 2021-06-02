#include <iostream>
#include "../Utils/Utils.hpp"
#include "../ImageHeader/ImageHeader.hpp"

struct Pixel{
    std::size_t red{};
    std::size_t green{};
    std::size_t blue{};
    Pixel() = default;
    Pixel(std::size_t r, std::size_t g, std::size_t b);
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
