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
#include "cstdlib"
#include <map>
#include <string>
#include <iostream>
#include <sstream>

namespace kallaballa {
// International standard code take from: https://de.wikipedia.org/wiki/Morsezeichen#Standard-Codetabelle
std::map<const wchar_t, const std::wstring> morseMap = {
    {' ', L" "},
    {L'\n', L"\n"},
    {L'A', L".-"},
    {L'B', L"-..."},
    {L'C', L"-.-."},
    {L'D', L"-.."},
    {L'E', L"."},
    {L'F', L"..-."},
    {L'G', L"--."},
    {L'H', L"...."},
    {L'I', L".."},
    {L'J', L".---"},
    {L'K', L"-.-"},
    {L'L', L".-.."},
    {L'M', L"--"},
    {L'N', L"-."},
    {L'O', L"---"},
    {L'P', L".--."},
    {L'Q', L"--.-"},
    {L'R', L".-."},
    {L'S', L"..."},
    {L'T', L"-"},
    {L'U', L"..-"},
    {L'V', L"...-"},
    {L'W', L".--"},
    {L'X', L"-..-"},
    {L'Y', L"-.--"},
    {L'Z', L"--.."},
    {L'1', L".----"},
    {L'2', L"..---"},
    {L'3', L"...--"},
    {L'4', L"....-"},
    {L'5', L"....."},
    {L'6', L"-...."},
    {L'7', L"--..."},
    {L'8', L"---.."},
    {L'9', L"----."},
    {L'0', L"-----"},
    {L'.',L".-.-.-"},
    {L',',L"--..--"},
    {L':',L"---..."},
    {L';',L"-.-.-."},
    {L'?',L"..--.."},
    {L'-',L"-....-"},
    {L'_',L"..--.-"},
    {L'(',L"-.--."},
    {L')',L"-.--.-"},
    {L'\'',L".----."},
    {L'=',L"-...-"},
    {L'+',L".-.-."},
    {L'/',L"-..-."},
    {L'@',L".--.-."},
    {L'À', L".--.-"},
    {L'Å', L".--.-"},
    {L'Ä', L".-.-"},
    {L'È', L".-..-"},
    {L'É', L"..-.."},
    {L'Ö', L"---."},
    {L'Ü', L"..--"},
    {L'ß', L"...--.."},
    {L'Ñ', L"--.--"},
    {L'\x04', L"...-.-"}, //EOT = SK
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

  std::wstring line;
  std::wstring morse;
  size_t x = 0;
  size_t y = 0;
  RGBColor color = selector.next();
  setlocale(LC_ALL, "");
  std::locale loc("");
  std::wcin.imbue(loc);
  std::wcout.imbue(loc);

  while(std::getline(std::wcin, line))
  {
    for(const wchar_t& c : line) {
      morse = morseMap[(wchar_t)std::towupper(c)];
      std::wcerr << morse << L" ";

      for (const wchar_t& m : morse) {
        if(m == L'-') {
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
    std::wcerr << std::endl;
  }
}
