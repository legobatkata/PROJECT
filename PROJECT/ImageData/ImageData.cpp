#include "ImageData.hpp"


Pixel::Pixel(std::size_t r, std::size_t g, std::size_t b){
    red = r;
    green = g;
    blue = b;
}



void ImageData::allocate(){
    arr = new Pixel*[height];
    if(!arr) throw std::invalid_argument("asd");
        
    for(int i=0; i<height; i++){
        arr[i] = new Pixel[width];
        if(!arr[i]){
            release();
        }
    }
}
    
void ImageData::release(){
    for(int i=0; i<height;i++){
        delete[] arr[i];
    }
    delete[] arr;
}
    
    
ImageData::ImageData(std::string& path):ImageHeader(path){
    allocate();
    readData(fileIn, type);
    //rows = header.getHeight();
    //cols = header.getWidth();
}
  


ImageData::~ImageData(){
    release();
}
    

void ImageData::readData(std::ifstream &ifstr, ImgType type){
    std::string input;
    std::size_t value;
    for(std::size_t i=0; i<height; i++){
        for(std::size_t j=0; j<width; j++){
            
            
            switch (type){
                case ImgType::P1:
                case ImgType::P2: {
                    input = getNextParam(ifstr);
                    value = strToInt(input);
                    
                    Pixel p1(value, value, value);
                    arr[i][j] = p1;
                    
                    break;
                }
                case ImgType::P3:{
                    std::string pixRstr = getNextParam(ifstr);
                    std::string pixGstr = getNextParam(ifstr);
                    std::string pixBstr = getNextParam(ifstr);
                    
                    std::size_t pixRint = strToInt(pixRstr);
                    std::size_t pixGint = strToInt(pixGstr);
                    std::size_t pixBint = strToInt(pixBstr);
                    
                    Pixel p2(pixRint, pixGint, pixBint);
                    arr[i][j] = p2;
                    
                    break;
                }
                case ImgType::P4:
                    break;
                case ImgType::P5:
                    break;
                case ImgType::P6:
                    break;
                default:
                    break;
            }
            
            
        }
    }
    
}



void ImageData::writeData(std::ofstream& ofstr, ImgType type){
    for(std::size_t i=0; i<height; i++){
        for(std::size_t j=0; j<width; j++){
            
            switch (type) {
                case ImgType::P1:
                case ImgType::P2:{
                    ofstr<<arr[i][j].red<<" ";
                    break;
                }
                case ImgType::P3:{
                    ofstr<<arr[i][j].red<<" ";
                    ofstr<<arr[i][j].green<<" ";
                    ofstr<<arr[i][j].blue<<" ";
                    break;
                }
                case ImgType::P4:{
                    
                    break;
                }
                case ImgType::P5:{
                    
                    break;
                }
                case ImgType::P6:{
                    
                    break;
                }
                default:
                    break;
            }
            
        }
        ofstr<<"\n";
    }
}



void ImageData::printData(){
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            std::cout<<arr[i][j].red<<" "<<arr[i][j].green<<" "<<arr[i][j].blue<<"\n";
        }
    }
}
