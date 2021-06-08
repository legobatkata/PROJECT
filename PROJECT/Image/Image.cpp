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
    if(type == P6) istr.seekg((int)istr.tellg()-2);
    readData(istr);
    
    currentPath = path;
    istr.close();
}


Image::Image(int& width, int& height, const std::string& hexCode){
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
    int value;
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            
            
            switch (type){
                case ImgType::P1:
                case ImgType::P2: {
                    input = getNextParam(ifstr);
                    value = strToInt(input);
                    
                    arr->at(i, j).red = value;
                    arr->at(i, j).green = value;
                    arr->at(i, j).blue = value;
                    
                    break;
                }
                case ImgType::P3:{
                    std::string pixRstr = getNextParam(ifstr);
                    std::string pixGstr = getNextParam(ifstr);
                    std::string pixBstr = getNextParam(ifstr);
                    
                    int pixRint = strToInt(pixRstr);
                    int pixGint = strToInt(pixGstr);
                    int pixBint = strToInt(pixBstr);
                    
                    arr->at(i, j).red = pixRint;
                    arr->at(i, j).green = pixGint;
                    arr->at(i, j).blue = pixBint;
                    
                    break;
                }
                case ImgType::P4:{
                    
                    
                    
                    break;
                }
                case ImgType::P5:{
                    int value = (int)getNextByte(ifstr);
                    
                    arr->at(i, j).red = value;
                    arr->at(i, j).green = value;
                    arr->at(i, j).blue = value;
                    
                    break;
                }
                case ImgType::P6:{
                    int red = (int)getNextByte(ifstr);
                    int green = (int)getNextByte(ifstr);
                    int blue = (int)getNextByte(ifstr);
                    
                    arr->at(i, j).red = red;
                    arr->at(i, j).green = green;
                    arr->at(i, j).blue = blue;
                    
                    break;
                }
                default:
                    break;
            }
            
            
        }
    }
    
}
void Image::writeData(std::ofstream& ofstr){
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            
            switch (type) {
                case ImgType::P1:
                case ImgType::P2:{
                    ofstr<<arr->at(i, j).red<<" ";
                    break;
                }
                case ImgType::P3:{
                    ofstr<<arr->at(i, j).red<<" ";
                    ofstr<<arr->at(i, j).green<<" ";
                    ofstr<<arr->at(i, j).blue<<" ";
                    break;
                }
                case ImgType::P4:{
                   
                    
                    break;
                }
                case ImgType::P5:{
                    uint8_t val = (uint8_t)arr->at(i, j).red;
                    ofstr.write((char*)&val, sizeof(val));
                    break;
                }
                case ImgType::P6:{
                    uint8_t redWrite = (uint8_t)arr->at(i, j).red;
                    uint8_t greenWrite = (uint8_t)arr->at(i, j).green;
                    uint8_t blueWrite = (uint8_t)arr->at(i, j).blue;
                    
                    ofstr.write((char*)&redWrite, sizeof(redWrite));
                    ofstr.write((char*)&greenWrite, sizeof(greenWrite));
                    ofstr.write((char*)&blueWrite, sizeof(blueWrite));
                    break;
                }
                default:
                    break;
            }
            
        }
        //ofstr<<"\n";
    }
}


void Image::printHeader(){
    std::cout<<"type: "<<typeToStr(type)<<"\n";
    std::cout<<"width: "<<width<<"\n";
    std::cout<<"height: "<<height<<"\n";
    std::cout<<"maxValue: "<<maxValue<<"\n";
}

void Image::printData(){
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            std::cout<<arr->at(i, j).red<<" "<<arr->at(i, j).green<<" "<<arr->at(i, j).blue<<"\n";
        }
    }
}
