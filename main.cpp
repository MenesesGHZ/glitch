#include <vector>
#include "glitch.hpp"
#include "config.h"


int main(){

    // defining filename
    char filename[100];
    strcpy(filename , PROJECT_SOURCE_DIR);
    strcat(filename, "/test/input/3.png");

    // defining an image object
    glitch::Image image;
    image.load_image(filename);

    // mock print
    std::cout << "Filename: " << filename << std::endl;
    std::cout << "Width: " << image.width << "  Height: " << image.height << std::endl << std::endl;
    std::cout << "First Pixel: " 
              << "\nR:" << static_cast<unsigned>(image.pixels[0].r) 
              << "\nG:" << static_cast<unsigned>(image.pixels[0].g) 
              << "\nB:" << static_cast<unsigned>(image.pixels[0].b) 
              << "\nA:" << static_cast<unsigned>(image.pixels[0].a) << std::endl << std::endl;


    // applying glitch algorithm
    glitch::sort_distorsion(&image, 4);

    // saving image 
    char filename2[100];
    strcpy(filename2 , PROJECT_SOURCE_DIR);
    strcat(filename2, "/test/output/3.png");
    image.save_image(filename2);

    return 0;
}