ColorMorsePainting
============

Generate colorful morse code messages suitable to be printed on e.g. t-shirts.
I've written it for linux, but it should be easily portable to other platforms. 
The only third party code is the CIEDE2000 library taken from https://github.com/gfiumara/CIEDE2000 which is incorporated in this repository.

## Build

To build it simply run 'make' in the base directory.

    git clone https://github.com/kallaballa/ColorMorsePainting.git
    cd ColorMorsePainting
    make

## Color Palette

The program uses a predefined color palette stored as line separated hex rgb values in the file "colors.txt". 

## Usage

    Usage: colorMorsePainting [options] [text]

    Options:
      -h [ --help ]                         Produce help message
      -v [ --verbose ]                      Enable verbose output
      -d [ --dots-per-row ] arg (=18)       Width of the whole painting measured as
                                            (morse) dots per row
      -w [ --dot-width ] arg (=5)           Width of a dot in millimeters
      -m [ --dot-margin ] arg (=1)          Width of a dot margin in millimeters
      -c [ --canvas-margin ] arg (=5)       Width of the margin of the painting
      -f [ --output-file ] arg (=-)         The path of the output file. Default is
                                            stdout
      -p [ --palette-file ] arg (=colors.txt)
                                            A file containing the color palette to 
                                            be used for the painting.
      -r [ --random-colors ]                Don't use a predefined palette. Instead
                                            use random colors
      -s [ --spacing ]                      Leave a blank dot between word 
                                            boundaries

## Example

The program takes the input text as argument and writes the generated svg by default to stdout

    ./colorMorsePainting "Man kann mit einem Computer Kunst und Schönheit schaffen" > painting.svg 

![Morse Painting: Kunst und Schönheit](https://github.com/kallaballa/ColorMorsePainting/raw/master/example/painting.png "Morse Painting: Kunst und Schönheit")


