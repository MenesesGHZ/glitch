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
    void swap_vertical_filter(Image*);
    void shift_vertical_filter(Image*);
    void shift_horizontal_filter(Image*);

    class PixelSorting{
      private:
        static const int blackness_criteria = 0;
      public:
        static void sort_column(glitch::Image* image, unsigned int x, unsigned int mode);
        static void sort_row(glitch::Image* image, unsigned int y, unsigned int mode);
        static int get_first_not_black_x(Image*, int, int);
        static int get_first_not_black_y(Image*, int, int);
        static int get_next_black_x(Image*, int, int);
        static int get_next_black_y(Image*, int, int);
        static int get_first_bright_y();
        static int get_next_dark_y();
        static int get_first_not_white_y();
        static int get_next_white_y();
        static void real_pixel_sort_filter(glitch::Image* image, unsigned int mode);
    };
}
