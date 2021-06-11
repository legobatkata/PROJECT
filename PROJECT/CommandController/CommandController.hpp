#ifndef CommandController_hpp
#define CommandController_hpp

#include "../Command/Command.hpp"
#include "../ImageEditor/ImageEditor.hpp"


const std::string no_file_opened = "No file is currently open\n";
const std::string file_already_opened = "There is already an opened file\n";

class CommandController{
private:
    Image* img;
    bool hasOpened = false;
    bool executeCommand(const Command& cmd);
public:
    ~CommandController();
    CommandController();
    CommandController(std::string path);
    
    void startReading();
    
};

#endif
