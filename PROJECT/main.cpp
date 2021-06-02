#include <iostream>
#include <fstream>

#include "Image/Image.hpp"
#include "ImageEditor/ImageEditor.hpp"

int main() {
    std::string asd = "testPics/cake.ppm";
    Image img(asd);
    
    ImageEditor::getInstance().greenCake(img);
    ImageEditor::getInstance().dither1(img);
    
    std::string qwe = "testPics/writeTest2.pbm";
    img.save(qwe);
    
    std::cout<<"done\n";
    return 0;
}
