#ifndef Image_hpp
#define Image_hpp

#include <iostream>
#include <fstream>
#include "../ImageHeader/ImageHeader.hpp"
#include "../ImageData/ImageData.hpp"
//#include "../ImageEditor/ImageEditor.hpp"

class ImageEditor;

class Image: public ImageData{
protected:
    void copyHeaderData(ImageHeader& h);
public:
    Image() = delete;
    Image(std::string& path);
    Image(ImageHeader& h);
    void save(std::string& path);
    
    friend class ImageEditor;
};

#endif
