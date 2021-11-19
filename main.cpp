#include <vector>
#include "glitch.hpp"
#include "lodepng.h"
#include "config.h"


int main(){

    // defining filename
    char filename[100];
    strcpy(filename , PROJECT_SOURCE_DIR);
    strcat(filename, "/test/1.png");

    // defining an image object
    glitch::Image image = glitch::Image();

    // loading image
    unsigned error = lodepng::decode(image.pixels, image.width, image.height, filename);
    if(error){
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    } 

    // mock print
    std::cout << "Filename: " << filename << std::endl;
    std::cout << "Width: " << image.width << "  Height: " << image.height << std::endl << std::endl;
    std::cout << "First Pixel: " 
              << "\nR:" << static_cast<unsigned>(image.pixels[0]) 
              << "\nG:" << static_cast<unsigned>(image.pixels[1]) 
              << "\nB:" << static_cast<unsigned>(image.pixels[2]) 
              << "\nA:" << static_cast<unsigned>(image.pixels[3]) << std::endl << std::endl;

    // testing get pixel
    std::vector<unsigned char> pixel = image.get_pixel(90,230);
    std::cout << "Selected Pixel: (must be black or almost black) " 
              << "\nR:" << static_cast<unsigned>(pixel[0]) 
              << "\nG:" << static_cast<unsigned>(pixel[1]) 
              << "\nB:" << static_cast<unsigned>(pixel[2]) 
              << "\nA:" << static_cast<unsigned>(pixel[3]) << std::endl;

    return 0;
}