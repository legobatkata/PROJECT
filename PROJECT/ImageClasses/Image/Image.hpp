#ifndef Image_hpp
#define Image_hpp

#include <iostream>
#include "../ImageHeader/ImageHeader.hpp"
#include "../ImageData/ImageData.hpp"
#include <fstream>

class Image: public ImageHeader, public ImageData{
protected:
    void copyHeaderData(ImageHeader& h);
public:
    Image() = delete;
    Image(std::string path);
    Image(ImageHeader& h);
};

#endif
