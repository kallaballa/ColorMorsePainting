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

## Example

There are four parameters you need to supply:
* Width of the whole painting measured as (morse) dots per row
* Width of a dot in millimeters
* Width of a dot margin in millimeters
* Width of the margin of the painting

The program takes the input text from stdin and writes the generated svg to stdout

    echo "Man kann mit einem Computer Kunst und Schönheit schaffen" | ./colorMorsePainting 18 5 1 5 > painting.svg 

![Morse Painting: Kunst und Schönheit](https://github.com/kallaballa/ColorMorsePainting/raw/master/example/painting.png "Morse Painting: Kunst und Schönheit")


