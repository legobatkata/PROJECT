#ifndef Utils_hpp
#define Utils_hpp

#include <iostream>
#include <string>
#include <cmath>
#include <exception>
#include <fstream>


std::string toUpperCase(const std::string& str);
const unsigned int strToInt(const std::string& str);

bool strContains(std::string& str, char c);
void trimCommentFromStr(std::string& str, char c);
unsigned int hexStrToDecInt(const std::string& hexStr);

void gotoNextLine(std::ifstream& fstr);
std::string getNextParam(std::ifstream& fstr);
uint8_t getNextByte(std::ifstream& fstr);

#endif
