#include "Image.hpp"


Image::Image(std::string& path):ImageData(path){
    /*std::ifstream ifstr;
    ifstr.open(path);
    if(!ifstr)std::cout<<"file couldnt load"<<"\n";
    readHeader(ifstr);
    readData(ifstr, type);*/
    fileIn.close();
    
    //printData();
}


void Image::copyHeaderData(ImageHeader& h){
    this->ImageHeader::height = h.getHeight();
    this->Image::width = h.getWidth();
    this->Image::type = h.getType();
    this->ImageHeader::maxValue = h.getMaxValue();
}


void Image::save(std::string& path){
    fileOut.open(path);
    writeHeader(fileOut);
    writeData(fileOut, type);
    fileOut.close();
}
