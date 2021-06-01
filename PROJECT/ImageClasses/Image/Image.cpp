#include "Image.hpp"


Image::Image(std::string path){
    std::ifstream ifstr;
    ifstr.open(path);
    if(!ifstr)std::cout<<"file couldnt load"<<"\n";
    readHeader(ifstr);
    readData(ifstr, type);
    ifstr.close();
    
    printData();
}


void Image::copyHeaderData(ImageHeader& h){
    this->ImageHeader::height = h.getHeight();
    this->Image::width = h.getWidth();
    this->Image::type = h.getType();
    this->ImageHeader::maxValue = h.getMaxValue();
}


Image::Image(ImageHeader& h){
    copyHeaderData(h);
}


