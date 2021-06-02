#include "ImageHeader.hpp"




ImageHeader::ImageHeader(std::string& path): fileIn(path, std::ios::in){
    readHeader(fileIn);
}

ImageHeader::ImageHeader(ImgType t, size_t w, size_t h)
    :type(t), width(w), height(h){}

ImageHeader::ImageHeader(ImgType t, size_t w, size_t h, size_t v)
    :type(t), width(w), height(h), maxValue(v){}



void ImageHeader::readHeader(std::ifstream& istr){
    type = strToType(getNextParam(istr));
    width = strToInt(getNextParam(istr));
    height = strToInt(getNextParam(istr));
    if(type != P1)
        maxValue = strToInt(getNextParam(istr));
}

void ImageHeader::writeHeader(std::ofstream& ostr){
    ostr<<typeToStr(type)<<"\n";
    ostr<<width<<"\n";
    ostr<<height<<"\n";
    if(type!=P1 && type!=P4)
        ostr<<maxValue<<"\n";
}


void ImageHeader::printHeader(){
    std::cout<<"type: "<<typeToStr(type)<<"\n";
    std::cout<<"width: "<<width<<"\n";
    std::cout<<"height: "<<height<<"\n";
    std::cout<<"maxValue: "<<maxValue<<"\n";
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



ImgType ImageHeader::strToType(const std::string& typeStr){
    if(typeStr == "P1") return P1;
    else if(typeStr == "P2") return P2;
    else if(typeStr == "P3") return P3;
    else if(typeStr == "P4") return P4;
    else if(typeStr == "P5") return P5;
    else if(typeStr == "P6") return P6;
    else throw std::invalid_argument("invalid type in header");
}

std::string ImageHeader::typeToStr(const ImgType& typeStr){
    if(type == P1) return "P1";
    else if(type == P2) return "P2";
    else if(type == P3) return "P3";
    else if(type == P4) return "P4";
    else if(type == P5) return "P5";
    else if(type == P6) return "P6";
    else throw std::invalid_argument("invalid argument");
}
