#ifndef ImageEditor_hpp
#define ImageEditor_hpp

#include <iostream>
#include "../Image/Image.hpp"

class ImageEditor{
private:
    ImageEditor(){};
public:
    ImageEditor(const ImageEditor&) = delete;
    ImageEditor& operator =(const ImageEditor&) = delete;

    static ImageEditor& getInstance(){
        static ImageEditor instance;
        return instance;
    }
    
    void greenCake(Image& img){
        
        for(int i=0;i<img.height;i++)
            for(int j=0; j<img.width; j++){
                std::size_t color = img.arr[i][j].red*0.21 + img.arr[i][j].green*0.72 + img.arr[i][j].blue*0.07;
                img.arr[i][j].red = color;
                img.arr[i][j].green = color;
                img.arr[i][j].blue = color;
                
                
                //img.arr[i][j].red /= 100;
                //img.arr[i][j].green /= 100;
                //img.arr[i][j].blue /= 100;
            }
        
        img.maxValue /= 4;
        for(int i=0;i<img.height;i++)
            for(int j=0; j<img.width; j++){
                img.arr[i][j].red /= 4;
                img.arr[i][j].green /= 4;
                img.arr[i][j].blue /= 4;
            }
        
        img.maxValue /= 4;
        for(int i=0;i<img.height;i++)
            for(int j=0; j<img.width; j++){
                img.arr[i][j].red /= 4;
                img.arr[i][j].green /= 4;
                img.arr[i][j].blue /= 4;
            }
        
        img.maxValue /= 2;
        for(int i=0;i<img.height;i++)
            for(int j=0; j<img.width; j++){
                img.arr[i][j].red /= 2;
                img.arr[i][j].green /= 2;
                img.arr[i][j].blue /= 2;
            }
        
        img.maxValue *= 2;
        for(int i=0;i<img.height;i++)
            for(int j=0; j<img.width; j++){
                img.arr[i][j].red *= 2;
                img.arr[i][j].green *= 2;
                img.arr[i][j].blue *= 2;
            }
        
    }
    
    
    void dither1(Image& img){
        for(int i=0;i<img.height;i++){
            int errorR = 0;
            int errorG = 0;
            int errorB = 0;
            for(int j=0; j<img.width; j++){
                //std::cout<<"("<<img.arr[i][j].red<<", "<<img.arr[i][j].red<<", "<<img.arr[i][j].red<<") "<<error;
                
                // red
                if((int)img.arr[i][j].red + errorR <= (int)img.maxValue/2){
                    errorR += (int)img.arr[i][j].red;
                    img.arr[i][j].red = 0;
                }else{
                    errorR += (int)img.arr[i][j].red - (int)img.maxValue;
                    img.arr[i][j].red = img.maxValue;
                }
                
                // green
                if((int)img.arr[i][j].green + errorG <= (int)img.maxValue/2){
                    errorG += (int)img.arr[i][j].green;
                    img.arr[i][j].green = 0;
                }else{
                    errorG += (int)img.arr[i][j].green - (int)img.maxValue;
                    img.arr[i][j].green = img.maxValue;
                }
                
                // blue
                if((int)img.arr[i][j].blue + errorB <= (int)img.maxValue/2){
                    errorB += (int)img.arr[i][j].blue;
                    img.arr[i][j].blue = 0;
                }else{
                    errorB += (int)img.arr[i][j].blue - (int)img.maxValue;
                    img.arr[i][j].blue = img.maxValue;
                }
                //std::cout<<"    -----    ("<<img.arr[i][j].red<<", "<<img.arr[i][j].red<<", "<<img.arr[i][j].red<<") "<<error<<"\n";
            }
            //std::cout<<"-----------\n";
        }
    }
    
};


#endif
