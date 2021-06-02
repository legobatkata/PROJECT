#include <iostream>
#include <fstream>

#include "Image/Image.hpp"
#include "ImageEditor/ImageEditor.hpp"

int main() {
    std::string asd = "testPics/pic.pbm";
    Image img(asd);
    
    std::string qwe = "testPics/writeTest.pbm";
    ImageEditor::getInstance().createBorder(img);
    img.save(qwe);
    std::cout<<"done\n";
    return 0;
}
