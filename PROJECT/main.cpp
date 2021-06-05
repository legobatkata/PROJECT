#include <iostream>
#include <fstream>

#include "Image/Image.hpp"
#include "ImageEditor/ImageEditor.hpp"

int main() {
    std::string asd = "testPics/cake.ppm";
    Image img(asd);
    
    //ImageEditor::getInstance().greenCake(img);
    //ImageEditor::getInstance().ditherFloydStanberg(img);
    //ImageEditor::getInstance().test(img);
    ImageEditor::getInstance().betterFloyd(img);
    
    std::string qwe = "testPics/testdir.pbm";
    img.save(qwe);
    
    std::cout<<"done\n";
    return 0;
}
