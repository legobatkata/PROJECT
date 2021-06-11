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
    CommandController() = default;
    
    /**
     Tries to load an Image from path, called when opening the program with a path as an argument
     */
    CommandController(std::string path);
    
    /**
     Starts the reading cycle of the class.
     The cycle reads a line from the console and puts it in a Command class, which splits its arguments.
     Then executeCommand is called with the newly created Command.
     The cycle continues until the user inputs an "exit" Command.
     */
    void startReading();
    
};

#endif
