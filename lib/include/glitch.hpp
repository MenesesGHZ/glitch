#pragma once

#include <vector>
#include <omp.h>
#include <iostream>
#include <algorithm>
#include "lodepng.h"

namespace glitch{

    class Pixel{
      public:
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
        int get_intensity();
    };

    class Image{
      public:
        unsigned int width;
        unsigned int height;
        std::vector<Pixel> pixels;

        Pixel get_pixel(unsigned int, unsigned int);
        void set_pixel(unsigned int, unsigned int, std::vector<unsigned char>);
        
        std::vector<unsigned char> get_raw_pixels();
        void load_image(char *);
        void save_image(const char*);
    };

    // glitching algorithms
    void sort_distorsion(Image*, unsigned int);
}
