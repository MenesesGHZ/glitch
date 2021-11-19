#include <vector>
#include "glitch.hpp"
#include "lodepng.h"
#include "config.h"


int main(){

    // defining filename
    char filename[100];
    strcpy(filename , PROJECT_SOURCE_DIR);
    strcat(filename, "/test/1.png");

    // defining image vector and its width and height
    std::vector<unsigned char> image; 
    unsigned width, height;

    // loading image
    unsigned error = lodepng::decode(image, width, height, filename);
    if(error){
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    } 

    // mock print
    std::cout << "Filename: " << filename << std::endl;
    std::cout << "Width: " << width << "  Height: " << height << std::endl << std::endl;
    std::cout << "First Pixel: " 
              << "\nR:" << static_cast<unsigned>(image[0]) 
              << "\nG:" << static_cast<unsigned>(image[1]) 
              << "\nB:" << static_cast<unsigned>(image[2]) 
              << "\nA:" << static_cast<unsigned>(image[3]) << std::endl << std::endl;

    // trash testing
    glitch::pixel_slice();

    return 0;
}