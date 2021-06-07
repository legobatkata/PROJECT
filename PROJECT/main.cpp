#include <iostream>
#include <fstream>

#include "Image/Image.hpp"
#include "ImageEditor/ImageEditor.hpp"

int main() {
    //std::string asd = "testPics/marbles.pbm";
    //Image img(asd);
    std::string hexCode = "#00FF00";
    Image img(200, 300, hexCode);
    
    //ImageEditor::getInstance().greenCake(img);
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
    
    ImageEditor::getInstance().resize(img, 50);
    //ImageEditor::getInstance().crop(img, 200, 2000, 0, 0);
    
    std::string qwe = "testPics/testdir.pbm";
    img.save(qwe);
    
    std::cout<<"done\n";
    return 0;
}
