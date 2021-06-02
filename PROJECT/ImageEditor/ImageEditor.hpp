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
    
    void createBorder(Image& img){
        
        
        for(int i=0; i<img.width; i++){
            img.arr[0][i].red = 1;
            img.arr[0][i].green = 1;
            img.arr[0][i].blue = 1;
        }
        for(int i=0; i<img.width; i++){
            img.arr[img.height-1][i].red = 1;
            img.arr[img.height-1][i].green = 1;
            img.arr[img.height-1][i].blue = 1;
        }
        for(int i=0; i<img.height; i++){
            img.arr[i][0].red = 1;
            img.arr[i][0].green = 1;
            img.arr[i][0].blue = 1;
        }
        for(int i=0; i<img.height; i++){
            img.arr[i][img.width-1].red = 1;
            img.arr[i][img.width-1].green = 1;
            img.arr[i][img.width-1].blue = 1;
        }
        
    }
    
};


#endif
