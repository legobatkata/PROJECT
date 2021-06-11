#ifndef Utils_hpp
#define Utils_hpp

#include <iostream>
#include <string>
#include <cmath>
#include <exception>
#include <fstream>

/**
 The Utils class contains a collection of functions used to help with tasks that could be needed in multiple parts of the project.
 */

/**
 Recieves a string and returns a version of it that is only in upper case.
 Used mainly in CommandController because first command argument must be case insensitive.
 */
std::string toUpperCase(const std::string& str);
/**
 Converts given string to int.
 */
const unsigned int strToInt(const std::string& str);

/**
 Check if a string contains a certain character, used for filtering commands while reading ascii files.
 */
bool strContains(std::string& str, char c);
/**
 Returns the part of a string that is before a certain character. Used for filtering commands while reading ascii files.
 */
void trimCommentFromStr(std::string& str, char c);
/**
 Converts a hex string to an int.
 Throws exception if given string has characters that are not in hex.
 */
int hexStrToDecInt(const std::string& hexStr);
/**
 Recieves a string path and returns the extention of the file specified in the path.
 Throws exception if path has no extention or a wrong one.
 */
std::string getExtFromPath(const std::string& path);

/**
 Recieves an std::ifstream& and uses getline to go to the file's next line.
 */
void gotoNextLine(std::ifstream& fstr);
/**
 Recieves an std::ifstream& and returns the next parameter as a string.
 If the next parameter contains a comment declaring character, it trims and returns only the parameter.
 If the next parameter starts with a comment declaring character, the function goes to the next line and recursively calls itself again.
 */
std::string getNextParam(std::ifstream& fstr);
/**
 Recieves an std::ifstream& that is opened in binary and returns the next byte as a uint8_t.
 */
uint8_t getNextByte(std::ifstream& fstr);

#endif
