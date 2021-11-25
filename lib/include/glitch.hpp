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
    class PixelSorting{
      private:
        static void sort_column(Image*, unsigned int);
        static void sort_row(Image*, unsigned int);
        static int get_first_not_criteria_x(Image*, int, int);
        static int get_first_not_criteria_y(Image*, int, int);
        static int get_next_criteria_x(Image*, int, int);
        static int get_next_criteria_y(Image*, int, int);

      public:
        static void pixel_sort_horizontal_filter(Image*);
        static void pixel_sort_vertical_filter(Image*);
        static int criteria; // 0 - 255
    };
}
