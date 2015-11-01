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

#include "Util.hpp"
#include "Morse.hpp"
#include "Color.hpp"
#include "SVGMorseWriter.hpp"
#include "cstdlib"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace kallaballa {
  void paint(std::wistream& in, ColorSelector& selector, SVGMorseWriter& writer, MorseTranslator& morseTrans, bool verbose, bool spacing) {
    std::wstring line;
    std::wstring morse;
    RGBColor color = selector.next();

    setlocale(LC_ALL, "");
    std::locale loc("");
    std::wcin.imbue(loc);
    std::wcout.imbue(loc);

    while(std::getline(in, line)) {
     for(const wchar_t& c : line) {
       morse = morseTrans.translate((wchar_t)std::towupper(c));
       if(verbose)
         std::wcerr << morse << L" ";

       for (const wchar_t& m : morse) {
         if(m == L'-') {
           writer.writeDash(color);
         } else if(m == L'.'){
           writer.writeDot(color);
         } else if(spacing && m == L' '){
           writer.writeSpace();
         }
       }
       color = selector.next();
     }
     if(verbose)
       std::wcerr << std::endl;
    }
  }
}

int main(int argc, char** argv) {
  size_t dotsPerRow = 18;
  size_t dotWidthMM = 5;
  size_t dotMarginMM = 1;
  size_t canvasMarginMM = 5;
  size_t roundedRadiusX = 0;
  size_t roundedRadiusY = 0;
  size_t dashWidthFactor = 3;
  std::string paletteFile = "colors.txt";
  std::string outputFile = "-";
  std::string text;
  std::string backgroundHex = "000000";
  std::string strAlign = "LEFT";
  bool verbose = false;
  bool randomColors = false;
  bool spacing = false;
  bool stdin = false;

  po::options_description genericDesc("Options");
  genericDesc.add_options()
    ("help,h", "Produce help message")
    ("verbose,v", "Enable verbose output")
    ("dots-per-row,d", po::value<size_t>(&dotsPerRow)->default_value(dotsPerRow), "Width of the whole painting measured as morse dots per row")
    ("dot-width,w", po::value<size_t>(&dotWidthMM)->default_value(dotWidthMM), "Width of a dot in millimeters")
    ("dot-margin,m", po::value<size_t>(&dotMarginMM)->default_value(dotMarginMM), "Width of a dot margin in millimeters")
    ("canvas-margin,c", po::value<size_t>(&canvasMarginMM)->default_value(canvasMarginMM), "Width of the margin of the painting")
    ("rounded-radius-x,x", po::value<size_t>(&roundedRadiusX)->default_value(roundedRadiusX), "The rounded corner radius (x) of the dot rectangles")
    ("rounded-radius-y,y", po::value<size_t>(&roundedRadiusY)->default_value(roundedRadiusY), "The rounded corner radius (y) of the dot rectangles")
    ("dash-width-factor,k", po::value<size_t>(&dashWidthFactor)->default_value(dashWidthFactor), "The width of a dash described as a multiple of dots (min = 2, max = dots-per-row / 2)")
    ("alignment,a", po::value<std::string>(&strAlign)->default_value(strAlign), "The alignment of morse dot lines which are not using the full width. Either LEFT, CENTER or RIGHT")
    ("output-file,f", po::value<std::string>(&outputFile)->default_value(outputFile), "The path of the output file. Default is stdout")
    ("palette-file,p", po::value<std::string>(&paletteFile)->default_value(paletteFile), "A file containing the color palette to be used for the painting.")
    ("background,b", po::value<std::string>(&backgroundHex)->default_value(backgroundHex), "The background color in hex RGB (24 bit)")
    ("stdin,i", "Read input text from stdin")
    ("random-colors,r", "Don't use a predefined palette. Instead use random colors")
    ("spacing,s", "Leave a blank dot between word boundaries");

  po::options_description hidden("Hidden options");
  hidden.add_options()
    ("text", po::value< std::string >(&text), "The text to encode in the painting");

  po::positional_options_description p;
  p.add("text", -1);

  po::options_description cmdline_options;
  cmdline_options.add(genericDesc).add(hidden);

  po::options_description visible;
  visible.add(genericDesc);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv).options(cmdline_options).positional(p).run(), vm);
  po::notify(vm);

  if (vm.count("help") || (text.empty() && !vm.count("stdin"))) {
      std::cerr << "Usage: colorMorsePainting [OPTION]... TEXT\n";
      std::cerr << "       colorMorsePainting [OPTION]... -i\n";
      std::cerr << visible;
      return 0;
  }

  using namespace kallaballa;

  verbose = vm.count("verbose");
  randomColors = vm.count("random-colors");
  spacing = vm.count("spacing");
  RGBColor bgColor = strtol(backgroundHex.c_str(), NULL, 16);
  stdin = vm.count("stdin");

  bool deleteInStream = false;
  bool deleteOutStream = false;
  std::wistream* in;
  std::ostream* out;

  if(stdin) {
    in = &std::wcin;
  } else {
    in = new std::wistringstream(utf8_to_utf32(text));
    deleteInStream = true;
  }

  if(outputFile == "-") {
    out = &std::cout;
  } else {
    out = new std::ofstream(outputFile);
    deleteOutStream = true;
  }

  if(dashWidthFactor < 2 || dashWidthFactor > (dotsPerRow / 2)) {
    std::cerr << "Error: Illegal dash-width-factor = " << dashWidthFactor << std::endl;
    exit(1);
  }

  SVGMorseWriter::Alignment align = SVGMorseWriter::LEFT;
  to_upper_case(strAlign);

  if(strAlign == "LEFT") {
    //nothing to do
  } else if(strAlign == "CENTER") {
    align = SVGMorseWriter::CENTER;
  } else if(strAlign == "RIGHT") {
    align = SVGMorseWriter::RIGHT;
  } else {
    std::cerr << "Error: Unknown alignment = " << strAlign << std::endl;
    exit(1);
  }

  ColorSelector* selector;
  if(randomColors) {
    selector = new ColorSelector(bgColor);
  } else  {
    selector = new ColorSelector(bgColor, readColorsFromFile(paletteFile));
  }

  SVGMorseWriter writer(*out, align, bgColor, roundedRadiusX, roundedRadiusY, dashWidthFactor, dotsPerRow, dotWidthMM, dotMarginMM, canvasMarginMM);
  MorseTranslator morseTrans;

  paint(*in, *selector, writer, morseTrans, verbose, spacing);

  if(deleteInStream)
    delete in;

  if(deleteOutStream)
    delete out;

  delete selector;
}
