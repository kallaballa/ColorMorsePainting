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

#include "ColorMorsePainting.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <random>

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

std::vector<Color> readColorsFromFile(const std::string& filename) {
  std::ifstream ifs(filename);
  std::vector<Color> colors;
  std::string line;
  Color c;
  while (std::getline(ifs, line)) {
    c = strtol(line.substr(1).c_str(), NULL, 16);
    colors.push_back(c);
  }

  return colors;
}

class ColorSelector {
  static std::random_device randDev_;
  Color lastColor_ = 0;
  std::vector<Color> palette_;

  std::mt19937 rng_;
  std::uniform_int_distribution<int> uni_;
public:
  ColorSelector(std::vector<Color> palette) : palette_(palette), rng_(randDev_()), uni_(0,palette.size() - 1) {
  }

  Color next() {
    if(lastColor_ == 0) {
      return lastColor_ = palette_[uni_(rng_)];
    } else {
      Color selected;
      // quick and dirty color "contrast" ensurance
      while(euclideanDistance(lastColor_, selected = palette_[uni_(rng_)] ) < 100) {}
      return lastColor_ = selected;;
    }
  }
};

std::random_device ColorSelector::randDev_;

SVGMorseWriter::SVGMorseWriter(const char* filename, size_t dotsPerRow, size_t dotWidthMM, size_t dotMarginMM, size_t canvasMarginMM) :
	ofs(filename),
	dotWidthPix(dotWidthMM * PIXEL_TO_MM),
	dotMarginPix(dotMarginMM * PIXEL_TO_MM),
	canvasMarginPix(canvasMarginMM * PIXEL_TO_MM),
	realWidthPix(dotsPerRow * dotWidthPix + dotsPerRow * dotMarginPix + canvasMarginPix * 2 - dotMarginPix),
	realHeightPix(0) {
  writeHeader();
}

SVGMorseWriter::~SVGMorseWriter() {
	writeFooter();
	this->ofs.close();
}

void SVGMorseWriter::writeHeader() {
	this->ofs << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>"<< std::endl;
	this->ofs << "<svg " << std::endl;
	this->ofs << "xmlns:dc=\"http://purl.org/dc/elements/1.1/\"" << std::endl;
	this->ofs << "xmlns:cc=\"http://creativecommons.org/ns#\"" << std::endl;
	this->ofs << "xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"" << std::endl;
	this->ofs << "xmlns:svg=\"http://www.w3.org/2000/svg\"" << std::endl;
	this->ofs << "xmlns:xlink=\"http://www.w3.org/1999/xlink\"" << std::endl;
	this->ofs << "xmlns=\"http://www.w3.org/2000/svg\"" << std::endl;
	this->ofs << "version=\"1.1\"" << std::endl;
	this->ofs << "id=\"svg2\">" << std::endl;
	this->ofs << "<g id=\"foreground\">" << std::endl;
}

void SVGMorseWriter::writeFooter() {
  this->ofs << "</g><g id=\"background\">" << std::endl;
  this->ofs << "<rect" << std::endl;
  this->ofs << "width=\"" << realWidthPix << "\"" << std::endl;
  this->ofs << "height=\"" << realHeightPix << "\"" << std::endl;
  this->ofs << "x=\"0\"" << std::endl;
  this->ofs << "y=\"0\"" << std::endl;
  this->ofs << "id=\"-1\"" << std::endl;
  this->ofs << "style=\"stroke-width: 0px; fill: #000000;\"/>" << std::endl;
	this->ofs << "</g>" << std::endl;
	this->ofs << "<use xlink:href=\"#foreground\" />" << std::endl;
	this->ofs << "</svg>" << std::endl;
}

void SVGMorseWriter::writeDot(size_t x, size_t y, Color c) {
  std::stringstream sstream;
  sstream << std::setfill('0') << std::setw(6) << std::hex << c;
  std::string strColor = sstream.str();

	this->ofs << "<rect" << std::endl;
	this->ofs << "width=\"" << dotWidthPix << "\"" << std::endl;
	this->ofs << "height=\"" << dotWidthPix << "\"" << std::endl;
	this->ofs << "x=\"" << canvasMarginPix + dotWidthPix * x + dotMarginPix * x << "\"" << std::endl;
	this->ofs << "y=\"" << canvasMarginPix + dotWidthPix * y + dotMarginPix * y << "\"" << std::endl;
	this->ofs << "id=\"" << pixelID++ << "\"" << std::endl;
	this->ofs << "style=\"fill:#" + strColor + ";stroke:none;\" />" << std::endl;
	this->realHeightPix = canvasMarginPix + dotWidthPix * y + dotMarginPix * y + dotWidthPix + canvasMarginPix;
}

void SVGMorseWriter::writeDash(size_t x, size_t y, Color c) {
  std::stringstream sstream;
  sstream << std::setfill('0') << std::setw(6) << std::hex << c;
  std::string strColor = sstream.str();

  this->ofs << "<rect" << std::endl;
  this->ofs << "width=\"" << dotWidthPix * 3 + dotMarginPix * 2 << "\"" << std::endl;
  this->ofs << "height=\"" << dotWidthPix << "\"" << std::endl;
  this->ofs << "x=\"" << canvasMarginPix + dotWidthPix * x + dotMarginPix * x << "\"" << std::endl;
  this->ofs << "y=\"" << canvasMarginPix + dotWidthPix * y + dotMarginPix * y << "\"" << std::endl;
  this->ofs << "id=\"" << pixelID++ << "\"" << std::endl;
  this->ofs << "style=\"fill:#" + strColor + ";stroke:none;\" />" << std::endl;
  this->realHeightPix = canvasMarginPix + dotWidthPix * y + dotMarginPix * y + dotWidthPix + canvasMarginPix;
}
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
  ColorSelector selector(readColorsFromFile("colors.txt"));
  SVGMorseWriter stencil("out.svg", dotsPerRow, dotWidthMM, dotMarginMM, canvasMarginMM);

  std::string text = argv[5];
  std::stringstream morse;

  for(const char& c : text) {
    morse << morseMap[std::toupper(c)] << " ";
  }

  size_t x = 0;
  size_t y = 0;
  std::cerr << morse.str() << std::endl;
  Color color = selector.next();
  for (const char& c : morse.str()) {
    if(c == '-') {
      if(x + 3 > dotsPerRow) {
        x = 0;
        ++y;
      }

      stencil.writeDash(x, y, color);
      x+=3;
    } else if(c == '.'){
      if(x + 1 > dotsPerRow) {
        x = 0;
        ++y;
      }

      stencil.writeDot(x, y, color);
      x++;
    } else if(c == ' '){
      color = selector.next();
    }
  }
}
