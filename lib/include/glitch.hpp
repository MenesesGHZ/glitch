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
        void set_pixel(unsigned int, unsigned int, Pixel);

        std::vector<unsigned char> get_raw_pixels();
        void load(char *);
        void save(const char*);
    };

    // glitching algorithms
    void sort_filter(Image*, unsigned int);
    void swap_horizontal_filter(Image*);
}
