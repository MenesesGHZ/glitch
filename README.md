<h1 align="center" >Glitch Image Effect with OpenMP </h1>

<div align="center">
<img alt="dorohedoro's glitch" src="/../with_test_examples/examples/pixel_sorting_filter/14_vertical.png">
</div>
<div align="center">
<img alt="C++ version" src="https://img.shields.io/badge/C++-v11-blue?style=flat-square">
<img alt="OpenMP version" src="https://img.shields.io/badge/OpenMP-blue?style=flat-square">
<img alt="CMake version" src="https://img.shields.io/badge/CMake-3.5.1-success?style=flat-square">
</div>

This software has the intent to make glitch effects on an image from your command line.
This is the product of school project for implementing multiparallel support to an algorithm using OpenMP software.

### Prerequisites
* C++ >= 11
* CMake >= 3.5.1
* OpenMP (optional)

### Installation
Clone this repository and navigate under `glitch/`
```bash
git clone && cd glitch
```

Under `glitch/` follow the next steps in order to make fresh build, and generate a binary file called **Glitch**.

1. Remove all content inside `build/` folder using the next command.
    ```bash
    rm -rf build/*
    ```

2. Navigate under `build/` folder. Then build with *cmake* which is going to generate plenty of other files.
Finally run the *make* command to invoke the generated Makefile (one of the files generated by cmake).
    ```bash
    cd build/ && cmake ../ && make
    ```

3. (Optional for linux or WSL users). After generating `./Glitch` file, you can move or copy it under `/usr/local/bin/` to use it everywhere on your machine. Under `glitch/build` run:
    ```bash
    sudo cp Glitch /usr/local/bin/
    ```

4. (Optional for linux or WSL users). Test the installation: 
    ```bash
    Glitch --help
    ```

### Usage
Once the binary file called **Glitch** has been generated you are ready to go. To see more details about how to use this software you can type on your command line: ```./Glitch --help```
    
Which is going to display the following message:
```bash
Options:
    -i, --input <path>: Set relative path to the input image
    -o, --output <path>: Set relative path to save the output image. (default = './output.png')
    -f, --filters: Set filter(s) to be applied sequentally separeted by comma (e.g. psv,sv,psv,...). (default = psh)
            psv: pixel sort vertical
            psh: pixel sort horizontal
            sv:  swap vertical
            sh:  swap horiztonal
            s:   sort pixels

    -c, --criteria <int>: Set criteria integer for [psv, psh] filters. Recommended value between 0 - 255. (default = 35)
    -p, --parallel: A flag to enable parallel computing. (default disabled; default threads = 4)
    -t, --threads <int>: Set number of threads. (default = 4)
    -v, --verbose: A flag to enable verbose mode. (default disabled)
    -h, --help: Display this message
``` 

Here is a list of the filters you could apply with a brief description, and also a sample url-image:
| Filter | Name                    | Description                                                                 | Sample URL-image |
|:-:     |:-:                      |:-:                                                                          | :-: |
| psv    | pixel sort vertical     | sorts each column base on -c, --criteria variable and the pixel's intensity | [ctrl+click](https://github.com/MenesesGHZ/glitch/blob/with_test_examples/examples/pixel_sorting_filter/14_vertical.png)    |
| psh    | pixel sort horizontal   | sorts each row base on -c, --criteria variable and the pixel's intensity  | [ctrl+click](https://github.com/MenesesGHZ/glitch/blob/with_test_examples/examples/pixel_sorting_filter/14_horizontal.png)  |
| sv     | swap vertical           | swaps the position of two random pixels of random columns of an image |  [ctrl+click](https://github.com/MenesesGHZ/glitch/blob/with_test_examples/examples/swap_vertical_filter/2.png)         |
| sh     | swap horizontal         | swaps the position of two random pixels of random rows of an image  | [ctrl+click](https://github.com/MenesesGHZ/glitch/blob/with_test_examples/examples/swap_horizontal_filter/2.png)            |
|  s     | sort pixels             | sorts pixels incrementally base on the pixel's intensity  | [ctrl+click](https://github.com/MenesesGHZ/glitch/blob/with_test_examples/examples/sort_filter/10.png)                      |



# License
This project is under the MIT license.
