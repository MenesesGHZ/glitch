#include <vector>
#include "glitch.hpp"
#include "config.h"


int main(){

    // defining filename
    char filename[100];
    strcpy(filename , PROJECT_SOURCE_DIR);
    strcat(filename, "/test/1.png");

    // defining an image object
    glitch::Image image;
    image.load(filename);

    // mock print
    std::cout << "Filename: " << filename << std::endl;
    std::cout << "Width: " << image.width << "  Height: " << image.height << std::endl << std::endl;
    
    // applying glitch algorithm
    glitch::PixelSorting::criteria = 0;
    glitch::PixelSorting::pixel_sort_vertical_filter(&image);

    // saving image 
    char filename2[100];
    strcpy(filename2 , "/home/meneses/Documents/PROYECTOS/glitch");
    strcat(filename2, "/examples/pixel_sorting_filter/1.png");
    image.save(filename2);

    return 0;
}