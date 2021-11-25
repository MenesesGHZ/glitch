#include "glitch.hpp"

glitch::Pixel glitch::Image::get_pixel(unsigned int x, unsigned int y){
    if(x > this->width || y > this->height){
        std::cout<< x <<"get" << y<< std::endl; 
        throw std::invalid_argument("invalid coordinate"); 
    }
    const int pixel_i = x + y * width;    
    return this->pixels[pixel_i];
}

void glitch::Image::set_pixel(unsigned int x, unsigned int y, std::vector<unsigned char> pixel){
    if(x > this->width || y > this->height){
        std::cout<< x <<"set" << y<< std::endl; 
        throw std::invalid_argument("invalid coordinate"); 
    }

    const int pixel_i = x + y * width;
    this->pixels[pixel_i].r = pixel[0];
    this->pixels[pixel_i].g = pixel[1];
    this->pixels[pixel_i].b = pixel[2];
    this->pixels[pixel_i].a = pixel[3];
}

void glitch::Image::set_pixel(unsigned int x, unsigned int y, glitch::Pixel pixel){
    if(x > this->width || y > this->height){
        std::cout<< x <<"set" << y<< std::endl; 
        throw std::invalid_argument("invalid coordinate"); 
    }
    const int pixel_i = x + y * width;
    this->pixels[pixel_i] = pixel;
}


int glitch::Pixel::get_intensity(){
    return (this->r + this->g + this->b) / 3;
}

void glitch::Image::load(char *filename){
    std::vector<unsigned char> raw_pixels;

    unsigned error = lodepng::decode(raw_pixels, this->width, this->height, filename);
    if(error){
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    } 

    for(int i = 0; i < raw_pixels.size(); i+=4){
        this->pixels.push_back(
            glitch::Pixel{raw_pixels[i], raw_pixels[i+1], raw_pixels[i+2], raw_pixels[i+3]}
        );
    }
}

void glitch::Image::save(const char* filename) {
  std::vector<unsigned char> raw_pixels = this->get_raw_pixels();
  unsigned error = lodepng::encode(filename, raw_pixels, this->width, this->height);
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}



std::vector<unsigned char> glitch::Image::get_raw_pixels(){
    std::vector<unsigned char> pixels_out;

    for(int i = 0; i < this->pixels.size(); i++){
        pixels_out.push_back(this->pixels[i].r);
        pixels_out.push_back(this->pixels[i].g);
        pixels_out.push_back(this->pixels[i].b);
        pixels_out.push_back(this->pixels[i].a);
    }

    return pixels_out;
}


// glitch algorithms
void glitch::sort_filter(glitch::Image* image, unsigned int sections){   
    omp_set_num_threads(sections);
    #pragma omp parallel for
    for (int i = 0; i < sections; i++){
        std::vector<glitch::Pixel>::iterator begin_i = image->pixels.begin() + (i * (image->pixels.size() / sections));
        std::vector<glitch::Pixel>::iterator end_i = image->pixels.begin() + ((i + 1) * (image->pixels.size() / sections));
        std::sort(begin_i, end_i, [](Pixel p1, Pixel p2) {
                return p1.get_intensity() < p2.get_intensity();
        });
    }
}

void glitch::swap_horizontal_filter(glitch::Image* image){
    const int swaps_limit = image->width / 2;
    for (int i = 0; i < image->height; i+=rand() % 10){
        for (int j = 0; j < swaps_limit; j++){
            int p1_x = rand() % image->width;
            int p2_x = rand() % image->width;

            Pixel p1 = image->get_pixel(p1_x, i);
            Pixel p2 = image->get_pixel(p2_x, i);
            
            image->set_pixel(p1_x, i, p2);
            image->set_pixel(p2_x, i, p1);
        }
    }
}

void glitch::swap_vertical_filter(glitch::Image* image){
    const int swaps_limit = image->height / 2;
    for (int i = 0; i < image->width; i+=rand() % 10){
        for (int j = 0; j < swaps_limit; j++){
            int p1_y = rand() % image->height;
            int p2_y = rand() % image->height;

            Pixel p1 = image->get_pixel(i, p1_y);
            Pixel p2 = image->get_pixel(i, p2_y);
            
            image->set_pixel(i, p1_y, p2);
            image->set_pixel(i, p2_y, p1);
        }
    }
}


// Pixel Sorting 
int glitch::PixelSorting::get_first_not_criteria_y(glitch::Image* image, int x, int y){
    if(y >= image->height) {
        return - 1;
    }

    while(image->get_pixel(x, y).get_intensity() < glitch::PixelSorting::criteria) {
        y++;
        if(y >= image->height) {
            return - 1;
        }
    }
    return y;
}

int glitch::PixelSorting::get_next_criteria_y(glitch::Image* image, int x, int y){
    y++;
    if(y < image->height){
        while(image->get_pixel(x, y).get_intensity() > glitch::PixelSorting::criteria) { // need a fix
            y++;
            if(y >= image->width) {
                return image->height - 1;
            }
        }
    }
    return y - 1; 
}

int glitch::PixelSorting::get_first_not_criteria_x(glitch::Image* image, int x, int y){
    while(image->get_pixel(x, y).get_intensity() < glitch::PixelSorting::criteria) { // need a fix
        x++;
        if(x >= image->width) {
            return -1;
        }
    }
    return x;
}

int glitch::PixelSorting::get_next_criteria_x(glitch::Image* image, int x, int y){
    x++;
    while(image->get_pixel(x, y).get_intensity() > glitch::PixelSorting::criteria) { // need a fix
        x++;
        if(x >= image->width) {
            return image->width-1;
        }
    }
    return x - 1;
}

void glitch::PixelSorting::sort_row(glitch::Image* image, unsigned int y){
    unsigned int x = 0, x_end = 0;
    while(x_end < image->width-1){
        x = glitch::PixelSorting::get_first_not_criteria_x(image, x,y);
        x_end = glitch::PixelSorting::get_next_criteria_x(image, x,y);
        
        if(x < 0 || x >= image->width) break;
        
        int sort_length = x_end-x;
        
        std::vector<glitch::Pixel> sorted;
        for(int i=0; i<sort_length; i++) {
            sorted.push_back(image->get_pixel(x+i, y));
        }
        std::sort(sorted.begin(), sorted.end(), [](Pixel p1, Pixel p2) {
            return p1.get_intensity() < p2.get_intensity();
        });
        for(int i=0; i<sort_length; i++) {
            image->set_pixel(x+i, y, sorted[i]);
        }
        x = x_end+1;
    }
}

void glitch::PixelSorting::sort_column(glitch::Image* image, unsigned int x){
    unsigned int y = 0, y_end = 0;
    while(y_end < image->height-1){
        y = glitch::PixelSorting::get_first_not_criteria_y(image, x,y);
        y_end = glitch::PixelSorting::get_next_criteria_y(image, x,y);
    
        if(y < 0 || y >= image->height) break;
        
        int sort_length = y_end-y;
        
        std::vector<glitch::Pixel> sorted;
        for(int i=0; i<sort_length; i++) {
            if (y + i >= image->height){
                std::cout<<"ENTRE: "<<y+1<<std::endl;
                break;
            }
            sorted.push_back(image->get_pixel(x, y+i));
        }
        std::sort(sorted.begin(), sorted.end(), [](Pixel p1, Pixel p2) {
            return p1.get_intensity() < p2.get_intensity();
        });
        for(int i=0; i<sort_length; i++) {
            if (y + i >= image->height){
                std::cout<< image->height <<" <= "<<y<<std::endl;
                break;
            }
            image->set_pixel(x, y+i, sorted[i]);
        }
        y = y_end+1;
    }
}

void glitch::PixelSorting::pixel_sort_horizontal_filter(glitch::Image* image){
    for (int y = 0; y < image->height - 1; y++){
        glitch::PixelSorting::sort_row(image, y);
    }
}

void glitch::PixelSorting::pixel_sort_vertical_filter(glitch::Image* image){
    for (int x = 0; x < image->width - 1; x++){
        glitch::PixelSorting::sort_column(image, x);
    }    
}

int glitch::PixelSorting::criteria = 30;

