#pragma once

#include <vector>
#include <iostream>

namespace glitch{

    // glitching algorithms
    void offset_pixel_sort();
    void pixel_slice();


    // base image class
    class Image{
      public:
        unsigned int width;
        unsigned int height;
        std::vector<unsigned char> pixels;

        std::vector<unsigned char> get_pixel(unsigned int, unsigned int);
        void set_pixel(unsigned int, unsigned int, std::vector<unsigned char>);
    };
}
