#include "CommandController/CommandController.hpp"


int main(int argc, char** args) {
    
    if(argc == 1){
        CommandController cCon;
        cCon.startReading();
    } else if(argc == 2){
        CommandController cCon(args[1]);
        cCon.startReading();
    } else {
        std::cout<<"too many arguments, please open either with only a path to a file or without arguments at all\n";
    }
    
    
    return 0;
}
