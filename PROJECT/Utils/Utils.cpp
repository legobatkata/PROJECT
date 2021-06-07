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


unsigned int hexToDec(std::string hexStr){
    unsigned int res = 0;
    for (int i = 0; i < hexStr.length(); ++i){
        if (hexStr[i] >= 48 && hexStr[i] <= 57)
            res += (hexStr[i] - 48) * pow(16, hexStr.length() - i - 1);
        else if (hexStr[i] >= 65 && hexStr[i] <= 70)
            res += (hexStr[i] - 55) * pow(16, hexStr.length() - i - 1);
        else if (hexStr[i] >= 97 && hexStr[i] <= 102)
            res += (hexStr[i] - 87) * pow(16, hexStr.length() - i - 1);
    }
    return res;
}

// TODO: move these to their own file later


bool strContains(std::string str, char c){
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
    getline(fstr,blah);
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
