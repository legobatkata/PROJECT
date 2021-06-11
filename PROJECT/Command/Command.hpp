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
    /**
     Splits the raw string into substrings using spaces as a divider and then puts each substring into a vector.
     */
    Command(std::string raw);
    /**
     Return the string that is at position pos of the string vecor.
     */
    std::string& operator[](const std::size_t pos);
    /**
     Return the string that is at position pos of the string vecor.
     */
    const std::string& operator[](const std::size_t pos) const;
    /**
     Returns the raw value of the command, that was initially passed in the constructor.
     */
    const std::string& getRaw() const;
    /**
     Return the count of arguments in the command.
     */
    int getSize() const;
    
    /**
     Prints the command.
     */
    void print() const;
};

#endif

