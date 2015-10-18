/*
 * ColorMorsePainting
 * Copyright (C) 2015 Amir Hassan <amir@viel-zu.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "Color.hpp"
#include "SVGMorseWriter.hpp"
#include <map>
#include <string>
#include <iostream>
#include <sstream>

namespace kallaballa {

using std::string;

std::map<const char, const std::string> morseMap = {
    {' ', " "},
    {'\n', "\n"},
    {'A', ".-"},
    {'B', "-..."},
    {'C', "-.-."},
    {'D', "-.."},
    {'E', "."},
    {'F', "..-."},
    {'G', "--."},
    {'H', "...."},
    {'I', ".."},
    {'J', ".---"},
    {'K', "-.-"},
    {'L', ".-.."},
    {'M', "--"},
    {'N', "-."},
    {'O', "---"},
    {'P', ".--."},
    {'Q', "--.-"},
    {'R', ".-."},
    {'S', "..."},
    {'T', "-"},
    {'U', "..-"},
    {'V', "...-"},
    {'W', ".--"},
    {'X', "-..-"},
    {'Y', "-.--"},
    {'Z', "--.."},
    {'1', ".----"},
    {'2', "..---"},
    {'3', "...--"},
    {'4', "....-"},
    {'5', "....."},
    {'6', "-...."},
    {'7', "--..."},
    {'8', "---.."},
    {'9', "----."},
    {'0', "-----"},
    {'.', ".-.-.-"},
    {',', "--..--"},
    {'?', "..--.."},
    {'-', "-...-"},
    {'/', "-..-."},
    {'@', ".--.-."},
    {'+', ".-.-."},
    {'=', "-..."},
    {'\'', ".----"},
    {'(', "-.--"},
    {')', "-.--."},
    {'\"', ".-..-"},
    {'\x04', "...-.-"}, //EOT = SK
};



} /* namespace kallaballa */

int main(int argc, char** argv) {
  using namespace kallaballa;

  if (argc != 6) {
    std::cerr << "Usage: PixelMorse <pixels per row> <pixel width mm> <pixel margin mm> <board margin mm> <text>" << std::endl;
    return 1;
  }

  size_t dotsPerRow = atoi(argv[1]);
  size_t dotWidthMM = atoi(argv[2]);
  size_t dotMarginMM = atoi(argv[3]);
  size_t canvasMarginMM = atoi(argv[4]);
  ColorSelector selector(readColorsFromFile("pastelColors.txt"));
  SVGMorseWriter writer("out.svg", dotsPerRow, dotWidthMM, dotMarginMM, canvasMarginMM);

  std::string text = argv[5];
  std::stringstream morse;

  for(const char& c : text) {
    morse << morseMap[std::toupper(c)] << " ";
  }

  size_t x = 0;
  size_t y = 0;
  RGBColor color = selector.next();

  for (const char& c : morse.str()) {
    if(c == '-') {
      if(x + 3 > dotsPerRow) {
        x = 0;
        ++y;
      }

      writer.writeDash(x, y, color);
      x+=3;
    } else if(c == '.'){
      if(x + 1 > dotsPerRow) {
        x = 0;
        ++y;
      }

      writer.writeDot(x, y, color);
      ++x;
    } else if(c == ' '){
      color = selector.next();
    }
  }
}
