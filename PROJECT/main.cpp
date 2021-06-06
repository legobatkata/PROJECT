#include <iostream>
#include <fstream>

#include "Image/Image.hpp"
#include "ImageEditor/ImageEditor.hpp"

int main() {
    std::string asd = "testPics/cake.ppm";
    Image img(asd);
    
    ImageEditor::getInstance().greenCake(img);
    //ImageEditor::getInstance().dither1d(img);
    //ImageEditor::getInstance().ditherJJN(img);
    //ImageEditor::getInstance().ditherFloyd(img);
    //ImageEditor::getInstance().ditherFakeFloyd(img);
    //ImageEditor::getInstance().ditherStucki(img);
    //ImageEditor::getInstance().ditherAtkinson(img);
    //ImageEditor::getInstance().ditherBurkes(img);
    //ImageEditor::getInstance().ditherSierra(img);
    //ImageEditor::getInstance().ditherSierraTwoRow(img);
    //ImageEditor::getInstance().ditherSierraLite(img);
    //ImageEditor::getInstance().dither4x4(img);
    //ImageEditor::getInstance().dither8x8(img);
    
    
    std::string qwe = "testPics/testdir.pbm";
    img.save(qwe);
    
    std::cout<<"done\n";
    return 0;
}
