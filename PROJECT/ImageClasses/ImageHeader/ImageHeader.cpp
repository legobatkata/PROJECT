#include "ImageHeader.hpp"




// --------------------------------------
#include <string>
#include <fstream>



ImageHeader::ImageHeader(){
    type = P1;
    width = 0;
    height = 0;
    maxValue = 0;
}

ImageHeader::ImageHeader(ImgType t, size_t w, size_t h)
    :type(t), width(w), height(h){}

ImageHeader::ImageHeader(ImgType t, size_t w, size_t h, size_t v)
    :type(t), width(w), height(h), maxValue(v){}

void ImageHeader::readHeader(std::ifstream& istr){
    //std::cout<<getNextParam(istr)<<'\n';
    //std::cout<<getNextParam(istr)<<'\n';
    //std::cout<<getNextParam(istr)<<'\n';
    //std::cout<<getNextParam(istr)<<"\n\n";
    
    type = translateType(getNextParam(istr));
    width = strToInt(getNextParam(istr));
    height = strToInt(getNextParam(istr));
    if(type != P1)
        maxValue = strToInt(getNextParam(istr));
    
    std::cout<<type<<'\n';
    std::cout<<width<<'\n';
    std::cout<<height<<'\n';
    std::cout<<maxValue<<"\n\n";
    
    
    
    for(int i=0;i<height;i++){
        for(int k=0; k<width; k++){
            std::string asd = getNextParam(istr);
            std::cout<<asd<<" ";
        }
        std::cout<<std::endl;
    }
}



ImgType ImageHeader::translateType(const std::string& typeStr){
    if(typeStr == "P1") return P1;
    else if(typeStr == "P2") return P2;
    else if(typeStr == "P3") return P3;
    else if(typeStr == "P4") return P4;
    else if(typeStr == "P5") return P5;
    else if(typeStr == "P6") return P6;
    else throw std::invalid_argument("invalid type in header");
}


ImgType ImageHeader::getType() const{
    return type;
}
size_t ImageHeader::getWidth() const{
    return width;
}
size_t ImageHeader::getHeight() const{
    return height;
}
size_t ImageHeader::getMaxValue() const{
    return maxValue;
}
