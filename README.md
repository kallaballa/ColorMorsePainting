ColorMorsePainting
============

Generate colorful morse code messages suitable to be printed on e.g. t-shirts.
I've written it for linux, but it should be easily portable to other platforms. 
I'm using the CIEDE2000 library taken from https://github.com/gfiumara/CIEDE2000 which is incorporated in this repository.
The only external dependency is the boost program options library.

## Build

First please install the boost program options library.

For Debian/Ubuntu:

    sudo apt-get install libboost-program-options-dev

For OpenSuse:

    sudo zypper in libboost_program_options1_54_0

To build it simply run 'make' in the base directory.

    git clone https://github.com/kallaballa/ColorMorsePainting.git
    cd ColorMorsePainting
    make

## Color Palette

The program by default uses a predefined color palette stored as line separated hex rgb values in the file "colors.txt".
You can specify a different palette file with the "-p" flag. Addionally the program can be configured to use random colors
from the whole RGB 24bit spectrum by using the "-r" flag.

## Usage

    Usage: colorMorsePainting [options] [text]
    
    Options:
      -h [ --help ]                         Produce help message
      -v [ --verbose ]                      Enable verbose output
      -d [ --dots-per-row ] arg (=18)       Width of the whole painting measured as
                                            morse dots per row
      -w [ --dot-width ] arg (=5)           Width of a dot in millimeters
      -m [ --dot-margin ] arg (=1)          Width of a dot margin in millimeters
      -c [ --canvas-margin ] arg (=5)       Width of the margin of the painting
      -a [ --alignment ] arg (=LEFT)        The alignment of morse dot lines which 
                                            are not using the full width. Either 
                                            LEFT, CENTER or RIGHT
      -f [ --output-file ] arg (=-)         The path of the output file. Default is
                                            stdout
      -p [ --palette-file ] arg (=colors.txt)
                                            A file containing the color palette to 
                                            be used for the painting.
      -b [ --background ] arg (=000000)     The background color in hex RGB (24 
                                            bit)
      -r [ --random-colors ]                Don't use a predefined palette. Instead
                                            use random colors
      -s [ --spacing ]                      Leave a blank dot between word 
                                            boundaries

## Example

The program takes the input text as argument and writes the generated svg by default to stdout

    ./colorMorsePainting "Man kann mit einem Computer Kunst und Schönheit schaffen" > painting.svg 

![Morse Painting: Kunst und Schönheit](https://github.com/kallaballa/ColorMorsePainting/raw/master/example/painting.png "Morse Painting: Kunst und Schönheit")


