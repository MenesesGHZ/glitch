#include "glitch.hpp"

void glitch::offset_pixel_sort(){
    std::cout << "testing offset pixel" << std::endl;
}

void glitch::pixel_slice(){
    std::cout << "testing pixel slice" << std::endl;
}

std::vector<unsigned char> glitch::Image::get_pixel(unsigned int x, unsigned int y){
    if(x > this->width || y > this->height){
        throw std::invalid_argument("invalid coordinate"); 
    }

    const int pixel_i = (x + y * width) * 4;
    std::vector<unsigned char> pixel = {
        this->pixels[pixel_i],
        this->pixels[pixel_i + 1],
        this->pixels[pixel_i + 2],
        this->pixels[pixel_i + 3]
    }; 

    return pixel;
}

void glitch::Image::set_pixel(unsigned int x, unsigned int y, std::vector<unsigned char> pixel){
    if(x > this->width || y > this->height){
        throw std::invalid_argument("invalid coordinate"); 
    }

    const int pixel_i = (x + y * width) * 4;
    this->pixels[pixel_i] = pixel[0];
    this->pixels[pixel_i + 1] = pixel[1];
    this->pixels[pixel_i + 2] = pixel[2];
    this->pixels[pixel_i + 3] = pixel[3];
}