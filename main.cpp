#include <vector>
#include "glitch.hpp"
#include "config.h"


int main(){

    // defining filename
    char filename[100];
    strcpy(filename , PROJECT_SOURCE_DIR);
    strcat(filename, "/test/input/1.png");

    // defining an image object
    glitch::Image image;
    image.load(filename);

    // mock print
    std::cout << "Filename: " << filename << std::endl;
    std::cout << "Width: " << image.width << "  Height: " << image.height << std::endl << std::endl;
    std::cout << "First Pixel: " 
              << "\nR:" << static_cast<unsigned>(image.pixels[0].r) 
              << "\nG:" << static_cast<unsigned>(image.pixels[0].g) 
              << "\nB:" << static_cast<unsigned>(image.pixels[0].b) 
              << "\nA:" << static_cast<unsigned>(image.pixels[0].a) << std::endl << std::endl;


    // applying glitch algorithm
    glitch::swap_horizontal_filter(&image);

    // saving image 
    char filename2[100];
    strcpy(filename2 , PROJECT_SOURCE_DIR);
    strcat(filename2, "/test/output/1.png");
    image.save(filename2);

    return 0;
}