#include "CommandController/CommandController.hpp"

/** \mainpage General Information
 *
 * \section Usage
 *
 * The program can be started in two ways:
 *  - without arguments, in which case the user has to open a file using commands.
 *  - with a single parameter that is a path to an image.
 *
 *  After the program has been started the user can enter the following commands:
 *  - EXIT: exits the application.
 *  - OPEN [path]: tries to open image from given path.
 *  - CLOSE: closes currently open image if there is one.
 *  - SAVEAS [path]: save image at given path as long as it is valid.
 *  - SAVE: saves image at the path that it was last saved at or opened from.
 *  - DITHER [dither method]: dithers an image according to the given method code. Currently supported method codes are:
 *     * 1: Basic one dimensional dithering algorithm
 *     * 2: Floyd-Stanberg
 *     * 3: Fake Floyd-Stanberg
 *     * 4: Jarvis, Judice, and Ninke
 *     * 5: Stucki
 *     * 6: Atkinson
 *     * 7: Burkes
 *     * 8: Sierra
 *     * 9: Two-row Sierra
 *     * 10: Sierra Lite
 *     * 11: 4x4 Bayer matrix algorithm
 *     * 12: 8x8 Bayer matrix algorithm
 *  - RESIZE [newWidth] [newHeight]: resizes image to a new width/height by stretching it accordingly.
 *  - RESIZE [percentage]: resizes the image to a given percentage of its size.
 *  - CROP [point 1 x] [point 1 y] [point 2 x] [point 2 y]: crops the image by two given points.
 *  - GRAYSCALE: turns the image's pixels to grayscale, note that this does not change its type, only its colors.
 *
 *
 * \section sec_1 Overview of how the program works with Images
 * The program generally first reads the Image's header. After that it checks what the type that was read is and uses a different reading method depending on what the type was.\n
 * The image's data always gets stored in a template Matrix class filled with pixels that always have full 3 channel rgb data.\n
 * For bitmap and graymap images the rgb pixels just have the values of all channels set to the same color.\n
 * When saving the image to a file, the code does a similar thing to reading: it checks what the type is and depending on it, it uses a different method for writing.\n
 *
 * \section sec_2 More information
 * The program was developed using the CLang compiler on MacOS with Xcode as an IDE.\n
 * All of the code and tests compile and run without problem under those conditions.\n
 * Code has been also tested on windows and it should be compiling on CodeBlocks with g++ without problems too. \n
 * Please contact me if any technical problems arise while examining.\n
 *
 * \section sec_3 Currently known issues
 * The biggest known problem of the program right now is the fact that it cannot currently read a binary bitmap (P4 type).\n
 * This is currently handled by throwing an exception whenever the user tries to read a binary bitmap image.\n
 *
 *\section sec_4 Credits
 *Проектът е създаден от Ивайло Недялков Атанасов.\n
 *ФН: 45763\n
 *Специалност: Информатика\n
 *Група: 2\n
 *github repo: https://github.com/legobatkata/PROJECT
 *
 *
 */

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
