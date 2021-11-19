#include <vector>
#include "glitch.hpp"
#include "lodepng.h"


int main(){
    
    char filename[] = "/home/meneses/Documents/PROYECTOS/glitch/test/1.png";
    std::vector<unsigned char> image; 
    unsigned width, height;
    unsigned error = lodepng::decode(image, width, height, filename);

    if(error){
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    } 

    std::cout << width << height << std::endl;
    
    glitch::pixel_slice();

    return 0;
}