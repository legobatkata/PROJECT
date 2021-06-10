#include "CommandController.hpp"

CommandController::CommandController(){}

CommandController::CommandController(std::string path){
    img = new Image(path);
}

CommandController::~CommandController(){
    if(hasOpened) delete img;
}

void CommandController::startReading(){
    std::string input;
    bool keepReading = true;
    do{
        getline(std::cin, input);
        Command currentCmd(input);
        keepReading = executeCommand(currentCmd);
        
    } while(keepReading);
}


bool CommandController::executeCommand(const Command& cmd){
    std::string firstArg = toUpperCase(cmd[0]);
    
    if(strcmp(firstArg.c_str(), "EXIT")==0){
        try{
            if(hasOpened){
                delete img;
                hasOpened = false;
            }
            std::cout<<"exiting program\n";
            return false;
            
        } catch (const std::exception& e){
           std::cout<<e.what()<<"\n";
        }
    }
    
    if(strcmp(firstArg.c_str(), "CLOSE")==0){
        try{
            if(!hasOpened) throw std::invalid_argument(no_file_opened);
            
            std::cout<<"Are you sure you want to close the current file?\n";
            std::string response;
            getline(std::cin, response);
            Command responseCmd(response);
            
            if(strcmp(toUpperCase(responseCmd[0]).c_str(), "YES") == 0 || strcmp(toUpperCase(responseCmd[0]).c_str(), "Y") == 0){
                delete img;
                hasOpened = false;
            }
            
        } catch (const std::exception& e){
            std::cout<<e.what()<<"\n";
        }
    }
    
    else if(strcmp(firstArg.c_str(), "OPEN")==0){
        try{
            if(hasOpened){ //throw std::invalid_argument(file_already_opened);
                Command closeCmd("CLOSE");
                executeCommand(toUpperCase(cmd[0]));
            }
            if(cmd.getSize() != 2) throw std::invalid_argument("wrong use of command, please use as: open [path]");
            
            img = new Image(cmd[1]);
            hasOpened = true;
            
        } catch (const std::exception& e){
            std::cout<<e.what()<<"\n";
        }
    }
    
    else if(strcmp(firstArg.c_str(), "NEW")==0){
        try{
            if(hasOpened){ //throw std::invalid_argument(file_already_opened);
                Command closeCmd("CLOSE");
                executeCommand(toUpperCase(cmd[0]));
            }
            if(cmd.getSize() != 4) throw std::invalid_argument("Wrong use of command, please use as: new [width] [height] [fillColor]");
            
            img = new Image(strToInt(cmd[1]), strToInt(cmd[2]), cmd[3]);
            hasOpened = true;
            
        } catch (const std::exception& e){
            std::cout<<e.what()<<"\n";
        }
    }
    
    else if(strcmp(firstArg.c_str(), "SAVEAS")==0){
        try{
            if(!hasOpened) throw std::invalid_argument(no_file_opened);
            if(cmd.getSize() != 2)throw std::invalid_argument("Wrong use of command, please use as: saveas [save path]");
            // maybe check if path extention is correct here too
            img->saveAs(cmd[1]);
        } catch (const std::exception& e){
            std::cout<<e.what()<<"\n";
        }
    }
    
    else if(strcmp(firstArg.c_str(), "SAVE")==0){
        try{
            if(!hasOpened) throw std::invalid_argument(no_file_opened);
            if(cmd.getSize() != 1) throw std::invalid_argument("Too many arguments");
            img->save();
        } catch (const std::exception& e){
            std::cout<<e.what()<<"\n";
        }
    }
    
    else if(strcmp(firstArg.c_str(), "CROP")==0){
        try{
            if(!hasOpened) throw std::invalid_argument(no_file_opened);
            if(cmd.getSize() != 5)throw std::invalid_argument("Wrong use of command, please use as: crop [point 1 x] [point 1 y] [point 2 x] [point 2 y]");
            ImageEditor::getInstance().crop(*img, strToInt(cmd[1]), strToInt(cmd[2]), strToInt(cmd[3]), strToInt(cmd[4]));
            
        } catch (const std::exception& e){
            std::cout<<e.what()<<"\n";
        }
    }
    
    else if(strcmp(firstArg.c_str(), "RESIZE")==0){
        try{
            if(!hasOpened) throw std::invalid_argument(no_file_opened);
            if(cmd.getSize() == 3){
                ImageEditor::getInstance().resize(*img, strToInt(cmd[1]), strToInt(cmd[2]));
            }  else if(cmd.getSize() == 2) {
                ImageEditor::getInstance().resize(*img, strToInt(cmd[1]));
            }
            else throw std::invalid_argument("Wrong use of command, please use as: resize [new width] [new height]\nor as: resize [percentage]");
            
        } catch (const std::exception& e){
            std::cout<<e.what()<<"\n";
        }
    }
    
    else if(strcmp(firstArg.c_str(), "DITHER")==0){
        try{
            if(!hasOpened) throw std::invalid_argument(no_file_opened);
            if(cmd.getSize() != 2) throw std::invalid_argument("Wrong use of command, please enter again and specify which dithering algorithm to use:\n1: basic 1 dimensional dither\n2: Floyd-Steinberg\n3: Fake Floyd-Steinberg\n4: Jarvis, Judice, and Ninke\n5: Stucki\n6: Atkinson\n7: Burkes\n8: Sierra\n9: Two-Row Sierra\n10: Sierra Lite\n11: 4x4 Bayer matrix\n12: 8x8 Bayer matrix\n");
            int algo = strToInt(cmd[1]);
            //ImageEditor::getInstance().grayscale(*img);
            switch (algo){
                case 1:
                    ImageEditor::getInstance().dither1d(*img);
                    break;
                case 2:
                    ImageEditor::getInstance().ditherFloyd(*img);
                    break;
                case 3:
                    ImageEditor::getInstance().ditherFakeFloyd(*img);
                    break;
                case 4:
                    ImageEditor::getInstance().ditherJJN(*img);
                    break;
                case 5:
                    ImageEditor::getInstance().ditherStucki(*img);
                    break;
                case 6:
                    ImageEditor::getInstance().ditherAtkinson(*img);
                    break;
                case 7:
                    ImageEditor::getInstance().ditherBurkes(*img);
                    break;
                case 8:
                    ImageEditor::getInstance().ditherSierra(*img);
                    break;
                case 9:
                    ImageEditor::getInstance().ditherSierraTwoRow(*img);
                    break;
                case 10:
                    ImageEditor::getInstance().ditherSierraLite(*img);
                    break;
                case 11:
                    ImageEditor::getInstance().dither4x4(*img);
                    break;
                case 12:
                    ImageEditor::getInstance().dither8x8(*img);
                    break;
                default:
                    ImageEditor::getInstance().ditherFloyd(*img);
                break;
            }
        } catch (const std::exception& e){
            std::cout<<e.what()<<"\n";
        }
    }
    
    else {
        std::cout<<"Command not recognised\n";
    }
    
    
    return true;
}





