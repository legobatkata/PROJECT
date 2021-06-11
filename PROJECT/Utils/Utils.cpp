#include "Utils.hpp"

std::string toUpperCase(const std::string& str){
    std::string newStr(str);
    for(size_t i=0; i<newStr.size(); i++){
        if(newStr[i]>='a' && newStr[i]<='z'){
            newStr[i] += ('A' - 'a');
        }
    }
    return newStr;
}

const unsigned int strToInt(const std::string& str){
    unsigned int res=0;
    for(std::size_t i=0; i<str.size(); i++){
        if(str[i]<'0' || str[i]>'9') throw std::invalid_argument("could not convert to int");
        else res += (str[i]-'0')*(pow(10, str.size()-i-1));
    }
    return res;
}


int hexStrToDecInt(const std::string& hexStr){
    int res = 0;
    for (int i = 0; i < hexStr.size(); ++i){
        if(!isxdigit(hexStr[i])) throw std::invalid_argument("hex string contains an non hex digit");
        if (hexStr[i] >= '0' && hexStr[i] <= '9')
            res += (hexStr[i] - '0') * pow(16, hexStr.length() - i - 1);
        else if (hexStr[i] >= 'A' && hexStr[i] <= 'F')
            res += (hexStr[i] - 'A' + 10) * pow(16, hexStr.length() - i - 1);
        else if (hexStr[i] >= 'a' && hexStr[i] <= 'f')
            res += (hexStr[i] - 'a' + 10) * pow(16, hexStr.length() - i - 1);
    }
    return res;
}

std::string getExtFromPath(const std::string& path){
    if(path.size() < 5) throw std::invalid_argument("path too short");
    if(path[path.size()-4] != '.') throw std::invalid_argument("no extention found");
    return path.substr(path.size()-3, path.size());
}


// file functions

bool strContains(std::string& str, char c){
    for(int i=0; i<str.size(); i++){
        if(str[i] == c) return true;
    }
    return false;
}

void trimCommentFromStr(std::string& str, char c){
    while(str[str.size()-1] != c){
        str.pop_back();
    }
    str.pop_back();
}

void gotoNextLine(std::ifstream& fstr){
    std::string blah;
    getline(fstr, blah);
}


std::string getNextParam(std::ifstream& fstr){
    std::string bufferStr;
    fstr>>bufferStr;
    
    if(!fstr) return "\0";
    
    if(strContains(bufferStr, '#')){
        if(bufferStr[0] != '#'){
            trimCommentFromStr(bufferStr, '#');
            gotoNextLine(fstr);
            //std::cout<<bufferStr<<"\n";
            return bufferStr;
        } else {
            gotoNextLine(fstr);
            return getNextParam(fstr);
        }
        
    } else {
        //std::cout<<bufferStr<<"\n";
        return bufferStr;
    }
    return "\0";
    
}

uint8_t getNextByte(std::ifstream& fstr){
    
    if(!fstr) return 0;
    
    try{
        uint8_t buf = 0;
        fstr.read((char*)&buf, sizeof(buf));
        return buf;
    } catch(const std::exception& e){
        std::cout<<e.what()<<"\n";
    }
    return 0;
    
    
}
