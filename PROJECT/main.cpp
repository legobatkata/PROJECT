#include <iostream>
#include <fstream>

#include "ImageClasses/Image/Image.hpp"

//enum picTypes{
//    P1, P2, P3
//};


/*bool strContains(std::string str, char c){
    for(int i=0; i<str.size(); i++){
        if(str[i] == c) return true;
    }
    return false;
}

void trimCommentFromStr(std::string& str, char c){
    while(str[str.size()-1] == c){
        str.pop_back();
    }
}

void gotoNextLine(std::ifstream& fstr){
    std::string blah;
    getline(fstr,blah);
}

void getNextHeaderParam(std::ifstream& fstr){
    std::string bufferStr;
    fstr>>bufferStr;
    
    if(strContains(bufferStr, '#')){
        trimCommentFromStr(bufferStr, '#');
        gotoNextLine(fstr);
    }
    
    
    std::cout<<bufferStr<<"\n";
}
*/
void readHeader(std::string path){
    //std::ifstream file;
    //file.open(path);
    
    /*
    getNextHeaderParam(file);
    getNextHeaderParam(file);
    getNextHeaderParam(file);
    getNextHeaderParam(file);
     */
    
    /*std::string bufferStr;
    for(int i=0; i<4; i++){
        char c;
        file>>c;
        if(c=='#'){
            while(c=='\n'){
                file.ignore();
            }
        } else bufferStr.push_back(c);
        */
        /*if(bufferStr[0] == '#'){
            std::getline(file, bufferStr);
            //file.ignore();
            i--;
        } else std::cout<<bufferStr<<"\n";
        */
    //}
    
    
    //file.close();
}



int main() {
    
    //readHeader("testpics/marbles.pbm");
    
    Image img("testPics/marbles.pbm");
    
    return 0;
}
