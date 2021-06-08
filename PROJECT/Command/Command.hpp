#ifndef Command_hpp
#define Command_hpp

#include <iostream>
#include <vector>
#include <string>

class Command{
private:
    std::string rawString;
    std::vector<std::string> arrString;
public:
    Command(std::string raw);
    
    std::string& operator[](const std::size_t& pos);
    const std::string& operator[](const std::size_t& pos) const;
    const std::string& getRaw() const;
    int getSize() const;
    
    void print() const;
};

#endif

