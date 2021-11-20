#include "glitch.hpp"

void glitch::sort_distorsion(glitch::Image* image, unsigned int sections){   
    omp_set_num_threads(4);
    #pragma omp parallel for
    for (int i = 0; i < sections; i++){
        std::vector<glitch::Pixel>::iterator begin_i = image->pixels.begin() + (i * (image->pixels.size() / sections));
        std::vector<glitch::Pixel>::iterator end_i = image->pixels.begin() + ((i + 1) * (image->pixels.size() / sections));
        std::sort(begin_i, end_i, [](Pixel p1, Pixel p2) {
                return p1.get_intensity() < p2.get_intensity();
        });
    }
}

glitch::Pixel glitch::Image::get_pixel(unsigned int x, unsigned int y){
    if(x > this->width || y > this->height){
        throw std::invalid_argument("invalid coordinate"); 
    }

    const int pixel_i = (x + y * width) * 4;
    return this->pixels[pixel_i];
}

void glitch::Image::set_pixel(unsigned int x, unsigned int y, std::vector<unsigned char> pixel){
    if(x > this->width || y > this->height){
        throw std::invalid_argument("invalid coordinate"); 
    }

    const int pixel_i = (x + y * width) * 4;
    this->pixels[pixel_i].r = pixel[0];
    this->pixels[pixel_i].g = pixel[1];
    this->pixels[pixel_i].b = pixel[2];
    this->pixels[pixel_i].a = pixel[3];
}


int glitch::Pixel::get_intensity(){
    return (this->r + this->g + this->b) / 3;
}

void glitch::Image::load_image(char *filename){
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

void glitch::Image::save_image(const char* filename) {
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