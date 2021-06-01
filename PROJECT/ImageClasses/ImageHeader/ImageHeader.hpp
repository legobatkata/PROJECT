#ifndef ImageHeader_hpp
#define ImageHeader_hpp

#include <iostream>
#include "../../Utils/Utils.hpp"

using std::size_t;

enum ImgType{
    P1, P2, P3, P4, P5, P6
};

class ImageHeader {
protected:
    ImgType type{};
    size_t width{};
    size_t height{};
    size_t maxValue = 0;
    
    ImgType translateType(const std::string& typeStr);
    
public:
    //ImageHeader() = delete;
    ImageHeader();
    ImageHeader(ImgType t, size_t w, size_t h);
    ImageHeader(ImgType t, size_t w, size_t h, size_t v);
    
    void readHeader(std::ifstream& istr);
    
    
    ImgType getType() const;
    size_t getWidth() const;
    size_t getHeight() const;
    size_t getMaxValue() const;
};


#endif
