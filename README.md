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

To build it, simply run 'make' in the base directory.

    git clone https://github.com/kallaballa/ColorMorsePainting.git
    cd ColorMorsePainting
    make

## Color Palette

The program by default uses a predefined color palette stored as line separated hex rgb values in the file "colors.txt".
You can specify a different palette file with the "-p" flag. 
Using the [CIEDE20000](https://en.wikipedia.org/wiki/Color_difference#CIEDE2000) color difference metric the program make
sure that adjancend morse letters have a sufficent color contrast (making them easily distinguishable) to each other as well
as to the background color.
Please note that the program can be configured to use random colors from the whole 24bit RGB spectrum by using the "-r" flag.

## Usage

    Usage: colorMorsePainting [OPTION]... TEXT
           colorMorsePainting [OPTION]... -i
    
    Options:
      -h [ --help ]                         Produce help message
      -v [ --verbose ]                      Enable verbose output
      -d [ --dots-per-row ] arg (=18)       Width of the whole painting measured as
                                            morse dots per row
      -w [ --dot-width ] arg (=5)           Width of a dot in millimeters
      -m [ --dot-margin ] arg (=1)          Width of a dot margin in millimeters
      -c [ --canvas-margin ] arg (=5)       Width of the margin of the painting
      -x [ --rounded-radius-x ] arg (=0)    The rounded corner radius (x) of the 
                                            dot rectangles
      -y [ --rounded-radius-y ] arg (=0)    The rounded corner radius (y) of the 
                                            dot rectangles
      -k [ --dash-width-factor ] arg (=3)   The width of a dash described as a 
                                            multiple of dots (min = 2, max = 
                                            dots-per-row / 2)
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
      -i [ --stdin ]                        Read input text from stdin
      -r [ --random-colors ]                Don't use a predefined palette. Instead
                                            use random colors
      -s [ --spacing ]                      Leave a blank dot between word 
                                            boundaries

## Example

The program takes the input text as argument and writes the generated svg by default to stdout. The following example uses the default settings.

    ./colorMorsePainting "Man kann mit einem Computer Kunst und Schönheit schaffen" > default.svg 

![Morse Painting: Kunst und Schönheit (default options)](https://github.com/kallaballa/ColorMorsePainting/raw/master/example/default.png "Morse Painting: Kunst und Schönheit (default options)")

The second example defines several custom options (random colors instead of a color palette, rounded corner radius x = 5px / y = 5px, alignment = center, verbose output) and reads the text from stdin (-i):

    echo "Man kann mit einem Computer Kunst und Schönheit schaffen" | ./colorMorsePainting -b 222222 -r -y 5 -x 5 -a center -v -i > custom.svg

![Morse Painting: Kunst und Schönheit (custom options)](https://github.com/kallaballa/ColorMorsePainting/raw/master/example/custom.png "Morse Painting: Kunst und Schönheit (custom options)")

