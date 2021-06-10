#include "Image.hpp"


Pixel::Pixel(int r, int g, int b){
    red = r;
    green = g;
    blue = b;
}

void Pixel::setAll(int color){
    red = color;
    green = color;
    blue = color;
}

Pixel::Pixel(std::string hexStr){
    if(hexStr.size() != 7 || hexStr[0] != '#') throw std::invalid_argument("invalid hex color");
    red =  hexStrToDecInt(hexStr.substr(1, 2));
    green = hexStrToDecInt(hexStr.substr(3, 2));
    blue = hexStrToDecInt(hexStr.substr(5, 2));
}


Image::~Image(){
    // this should call the Matrix's constructor and release the heap memory
    delete arr;
}

Image::Image(const std::string& path){
    std::ifstream istr(path, std::ios::binary);
    if(!istr) throw std::invalid_argument("could not open file");
        
    readHeader(istr);
    arr = new Matrix<Pixel>(height, width);
    readData(istr);
    
    currentPath = path;
    istr.close();
}


Image::Image(int width, int height, const std::string& hexCode){
    if(width <= 0 || height <= 0) throw std::invalid_argument("invalid width or height");
    Pixel p(hexCode);
    
    this->type = P3;
    this->height = height;
    this->width = width;
    this->maxValue = 255;
    arr = new Matrix<Pixel>(height, width);
    
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            arr->at(i, j).red = p.red;
            arr->at(i, j).green = p.green;
            arr->at(i, j).blue = p.blue;
        }
    }
}


void Image::saveAs(const std::string& path){
    std::ofstream ofstr(path);
    if(!ofstr) throw std::invalid_argument("error while saving at this path");
    
    writeHeader(ofstr);
    writeData(ofstr);
    
    currentPath = path;
    ofstr.close();
}


void Image::save(){
    if(currentPath[0] != '\0')
        saveAs(currentPath);
    else throw std::invalid_argument("no path found, please first use SaveAs /path/");
}


ImgType Image::strToType(const std::string& typeStr){
    if(typeStr == "P1") return P1;
    else if(typeStr == "P2") return P2;
    else if(typeStr == "P3") return P3;
    else if(typeStr == "P4") return P4;
    else if(typeStr == "P5") return P5;
    else if(typeStr == "P6") return P6;
    else throw std::invalid_argument("invalid type in header");
}

std::string Image::typeToStr(const ImgType& typeStr){
    if(type == P1) return "P1";
    else if(type == P2) return "P2";
    else if(type == P3) return "P3";
    else if(type == P4) return "P4";
    else if(type == P5) return "P5";
    else if(type == P6) return "P6";
    else throw std::invalid_argument("invalid argument");
}



void Image::readHeader(std::ifstream& ifstr){
    type = strToType(getNextParam(ifstr));
    width = strToInt(getNextParam(ifstr));
    height = strToInt(getNextParam(ifstr));
    if(type != P1 && type!=P4)
        maxValue = strToInt(getNextParam(ifstr));
}


void Image::writeHeader(std::ofstream& ofstr){
    ofstr<<typeToStr(type)<<"\n";
    ofstr<<width<<"\n";
    ofstr<<height<<"\n";
    if(type!=P1 && type!=P4)
        ofstr<<maxValue<<"\n";
}

void Image::readData(std::ifstream &ifstr){
    std::string input;
    
    switch (type){
            
        case ImgType::P1:
        case ImgType::P2: {
            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    std::string input = getNextParam(ifstr);
                    arr->at(i, j).red = strToInt(input);
                    arr->at(i, j).green = strToInt(input);
                    arr->at(i, j).blue = strToInt(input);
                }
            }
            break;
        }
            
        case ImgType::P3:{
            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    arr->at(i, j).red = strToInt(getNextParam(ifstr));;
                    arr->at(i, j).green = strToInt(getNextParam(ifstr));;
                    arr->at(i, j).blue = strToInt(getNextParam(ifstr));;
                }
            }
            break;
        }
        case ImgType::P4:{
            throw std::invalid_argument("sorry, binary bitmap is not currently supported by this software");
            break;
        }
            
        case ImgType::P5:{
            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    int binValue = (int)getNextByte(ifstr);
                    arr->at(i, j).red = binValue;
                    arr->at(i, j).green = binValue;
                    arr->at(i, j).blue = binValue;
                }
            }
            
            break;
        }
            
        case ImgType::P6:{
            ifstr.seekg((int)ifstr.tellg()-2);
            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    arr->at(i, j).red = (int)getNextByte(ifstr);
                    arr->at(i, j).green = (int)getNextByte(ifstr);
                    arr->at(i, j).blue = (int)getNextByte(ifstr);
                }
            }
            
            break;
        }
        default:
            break;
    }
            
            
    
}
void Image::writeData(std::ofstream& ofstr){
    switch (type) {
        case ImgType::P1:
        case ImgType::P2:{
            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    ofstr<<arr->at(i, j).red<<" ";
                }
                ofstr<<"\n";
            }
            break;
        }
            
        case ImgType::P3:{
            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    ofstr<<arr->at(i, j).red<<" ";
                    ofstr<<arr->at(i, j).green<<" ";
                    ofstr<<arr->at(i, j).blue<<" ";
                }
                ofstr<<"\n";
            }
            break;
        }
            
        case ImgType::P4:{
            throw std::invalid_argument("sorry, binary bitmap is not currently supported by this software");
            break;
        }
            
        case ImgType::P5:{
            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    uint8_t val = (uint8_t)arr->at(i, j).red;
                    ofstr.write((char*)&val, sizeof(val));
                }
            }
            break;
        }
            
        case ImgType::P6:{
            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    uint8_t redWrite = (uint8_t)arr->at(i, j).red;
                    uint8_t greenWrite = (uint8_t)arr->at(i, j).green;
                    uint8_t blueWrite = (uint8_t)arr->at(i, j).blue;
            
                    ofstr.write((char*)&redWrite, sizeof(redWrite));
                    ofstr.write((char*)&greenWrite, sizeof(greenWrite));
                    ofstr.write((char*)&blueWrite, sizeof(blueWrite));
                }
            }
            break;
        }
        default:
            break;
    }
}


ImgType Image::getType()const{
    return type;
}
int Image::getWidth()const{
    return width;
}
int Image::getHeight()const{
    return height;
}
int Image::getMaxValue()const{
    return maxValue;
}
