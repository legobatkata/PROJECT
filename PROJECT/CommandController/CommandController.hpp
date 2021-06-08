#ifndef CommandController_hpp
#define CommandController_hpp

#include "../Command/Command.hpp"
#include "../Utils/Utils.hpp"
#include "../Image/Image.hpp"
#include "../ImageEditor/ImageEditor.hpp"

#include <fstream>

class CommandController{
private:
    Image* img;
    bool hasOpened = false;
    bool executeCommand(const Command& cmd, std::istream& istr);
public:
    ~CommandController();
    CommandController();
    CommandController(std::string path);
    
    void startReading();
    
};

#endif
