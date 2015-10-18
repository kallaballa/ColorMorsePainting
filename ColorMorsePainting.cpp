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

  if (argc != 5) {
    std::cerr << "Usage: colorMorsePainting <dots per row> <dot width mm> <dot margin mm> <canvas margin mm>" << std::endl;
    return 1;
  }

  size_t dotsPerRow = atoi(argv[1]);
  size_t dotWidthMM = atoi(argv[2]);
  size_t dotMarginMM = atoi(argv[3]);
  size_t canvasMarginMM = atoi(argv[4]);
  ColorSelector selector(readColorsFromFile("colors.txt"));
  SVGMorseWriter writer(std::cout, dotsPerRow, dotWidthMM, dotMarginMM, canvasMarginMM);

  std::string line;
  std::string morse;
  size_t x = 0;
  size_t y = 0;
  RGBColor color = selector.next();

  while(std::getline(std::cin, line))
  {
    for(const char& c : line) {
      morse = morseMap[std::toupper(c)];

      for (const char& m : morse) {
        if(m == '-') {
          if(x + 3 > dotsPerRow) {
            x = 0;
            ++y;
          }

          writer.writeDash(x, y, color);
          x+=3;
        } else if(m == '.'){
          if(x + 1 > dotsPerRow) {
            x = 0;
            ++y;
          }

          writer.writeDot(x, y, color);
          ++x;
        }
      }
      color = selector.next();
    }
  }
}
