#include <getopt.h>
#include "glitch.hpp"
#include "config.h"

void read_cli_parameters(int, char**);
std::string input_file, output_file = "output.png";
std::vector<std::string> filter_sequence = {"psh"}; 
bool verbose = false;

int main(int argc, char** argv){
    read_cli_parameters(argc, argv);

    // loading image
    glitch::Image image;
    image.load(&input_file[0]);

    // verbose printing
    if(verbose){
        printf("Input: %s | Output: %s\n", input_file.c_str(), output_file.c_str());
        printf("width: %d  height: %d  total pixels: %d\n", image.width, image.height, image.width * image.height);
        std::string flow_string;
        for(int i = 0; i < filter_sequence.size(); i++){
            flow_string += filter_sequence[i];
            if(i < filter_sequence.size() - 1){
                flow_string += " -> ";
            }
        } 
        printf("flow: [image input] -> { %s } -> [image output]\n", flow_string.c_str());
        if(glitch::parallel_enabled){
            printf("parallel enabled with [%d] threads\n", glitch::threads);
        }
    }

    // applying glitch algorithm(s) sequentially, and saving image
    for(std::string filter : filter_sequence){
        glitch::filters.at(filter)(&image);
    }
    image.save(&output_file[0]);

    exit(EXIT_SUCCESS);
}


void read_cli_parameters(int argc, char** argv){
    const char* const short_opts = "i:o:f:cpvh";
    const option long_options[] = {
       {"input",   required_argument, nullptr, 'i'},
       {"output",  required_argument, nullptr, 'o'},
       {"filters",  required_argument, nullptr, 'f'},
       {"criteria",required_argument, nullptr, 'c'},
       {"parallel",no_argument,       nullptr, 'p'},
       {"threads", required_argument, nullptr, 't'},
       {"verbose", no_argument,       nullptr, 'v'},
       {"help",    no_argument,       nullptr, 'h'},
       {0,         no_argument,       nullptr,  0 }
    };
    bool failure = false;

    auto print_help = [](){
        printf( 
            "\nOptions:\n"
            "   -i, --input <path>: Set relative path to the input image\n"
            "   -o, --output <path>: Set relative path to save the output image\n"
            "   -f, --filters: Set filter(s) to be applied sequentally separeted by comma (e.g. psv,psh,sv,...)\n"
            "          psv: pixel sort vertical\n"
            "          psh: pixel sort horizontal\n"
            "          sv:  swap vertical\n"
            "          sh:  swap horiztonal\n"
            "          s:   sort pixels\n\n"
            "   -c, --criteria <int>: Set criteria integer for [psv, psh] filters. Recommended value between (0 - 255)\n"
            "   -p, --parallel: A flag to enable parallel computing. (default threads = 4)\n"
            "   -t, --threads <int>: Set number of threads. default = 4\n"
            "   -v, --verbose: A flag to enable verbose mode\n"
            "   -h, --help: Display this message\n\n"            
        );
    };

    while (true) {
        const int opt = getopt_long(argc, argv, short_opts, long_options, nullptr);
        std::string filter, filter_arg;

        if (opt == -1)
            break;

        switch (opt) {
            case 'i':
                input_file = std::string(optarg);
                break;

            case 'o':
                output_file = std::string(optarg);
                break;

            case 'f':
                filter_sequence.clear();
                filter_arg = std::string(optarg);
                for(int i=0; i < filter_arg.size(); i++){
                    if (filter_arg[i] == ','){
                        filter_sequence.push_back(filter);
                        filter = "";
                        continue;
                    }
                    filter += filter_arg[i];
                    if (i == filter_arg.size()-1) filter_sequence.push_back(filter);   
                }
                break;

            case 'c':
                glitch::PixelSorting::criteria = std::stoi(optarg);
                break;

            case 'p':
                glitch::parallel_enabled = true;
                break;

            case 't':
                glitch::threads = std::stoi(optarg);
                break;

            case 'v':
                verbose = true;
                break;

            case 'h':
                print_help();
                exit(EXIT_SUCCESS);

            case '?':
                print_help();
                failure = true;
                break;

            default:
                print_help();
                break;
        }
    }
    if (input_file.empty()){
        printf("--input/-i must be specified\n"); failure = true;
    }
    if (output_file.empty()){ 
        printf("--output/-o must be specified\n"); failure = true;
    }
    for(const std::string filter : filter_sequence){
        if(!glitch::filters.count(filter)){
            printf("filter { %s } does not exist\n", filter.c_str()); failure = true;
            break;
        }
    }

    if (failure) exit(EXIT_FAILURE);  
}