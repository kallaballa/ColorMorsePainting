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

#include "SVGMorseWriter.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>

namespace kallaballa {

  SVGMorseWriter::SVGMorseWriter(std::ostream& os, size_t dotsPerRow, size_t dotWidthMM, size_t dotMarginMM, size_t canvasMarginMM) :
    os(os),
    dotsPerRow_(dotsPerRow),
    dotWidthPix_(dotWidthMM * PIXEL_TO_MM),
    dotMarginPix_(dotMarginMM * PIXEL_TO_MM),
    canvasMarginPix_(canvasMarginMM * PIXEL_TO_MM),
    backgroundWidthPix_(dotsPerRow * dotWidthPix_ + dotsPerRow * dotMarginPix_ + canvasMarginPix_ * 2 - dotMarginPix_),
    backgroundHeightPix_(0) {
    writeHeader();
  }

  SVGMorseWriter::~SVGMorseWriter() {
    writeFooter();
  }

  void SVGMorseWriter::writeHeader() {
    this->os << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>"<< std::endl;
    this->os << "<svg " << std::endl;
    this->os << "xmlns:dc=\"http://purl.org/dc/elements/1.1/\"" << std::endl;
    this->os << "xmlns:cc=\"http://creativecommons.org/ns#\"" << std::endl;
    this->os << "xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"" << std::endl;
    this->os << "xmlns:svg=\"http://www.w3.org/2000/svg\"" << std::endl;
    this->os << "xmlns:xlink=\"http://www.w3.org/1999/xlink\"" << std::endl;
    this->os << "xmlns=\"http://www.w3.org/2000/svg\"" << std::endl;
    this->os << "version=\"1.1\"" << std::endl;
    this->os << "id=\"svg2\">" << std::endl;
    this->os << "<defs><g id=\"foreground\">" << std::endl;
  }

  void SVGMorseWriter::writeFooter() {
    this->os << "</g><g id=\"background\">" << std::endl;
    this->os << "<rect" << std::endl;
    this->os << "width=\"" << backgroundWidthPix_ << "\"" << std::endl;
    this->os << "height=\"" << backgroundHeightPix_ << "\"" << std::endl;
    this->os << "x=\"0\"" << std::endl;
    this->os << "y=\"0\"" << std::endl;
    this->os << "id=\"-1\"" << std::endl;
    this->os << "style=\"stroke-width: 0px; fill: #000000;\"/>" << std::endl;
    this->os << "</g></defs>" << std::endl;
    //do the drawing in the right order
    this->os << "<use xlink:href=\"#background\" />" << std::endl;
    this->os << "<use xlink:href=\"#foreground\" />" << std::endl;
    this->os << "</svg>" << std::endl;
  }

  void SVGMorseWriter::writeDot(size_t x, size_t y, RGBColor c) {
    std::stringstream sstream;
    sstream << std::setfill('0') << std::setw(6) << std::hex << c;
    std::string strColor = sstream.str();

    this->os << "<rect" << std::endl;
    this->os << "width=\"" << dotWidthPix_ << "\"" << std::endl;
    this->os << "height=\"" << dotWidthPix_ << "\"" << std::endl;
    this->os << "x=\"" << canvasMarginPix_ + dotWidthPix_ * x + dotMarginPix_ * x << "\"" << std::endl;
    this->os << "y=\"" << canvasMarginPix_ + dotWidthPix_ * y + dotMarginPix_ * y << "\"" << std::endl;
    this->os << "id=\"" << glyphID++ << "\"" << std::endl;
    this->os << "style=\"fill:#" + strColor + ";stroke:none;\" />" << std::endl;
    this->backgroundHeightPix_ = canvasMarginPix_ + dotWidthPix_ * y + dotMarginPix_ * y + dotWidthPix_ + canvasMarginPix_;
  }

  void SVGMorseWriter::writeDash(size_t x, size_t y, RGBColor c) {
    std::stringstream sstream;
    sstream << std::setfill('0') << std::setw(6) << std::hex << c;
    std::string strColor = sstream.str();

    this->os << "<rect" << std::endl;
    this->os << "width=\"" << dotWidthPix_ * 3 + dotMarginPix_ * 2 << "\"" << std::endl;
    this->os << "height=\"" << dotWidthPix_ << "\"" << std::endl;
    this->os << "x=\"" << canvasMarginPix_ + dotWidthPix_ * x + dotMarginPix_ * x << "\"" << std::endl;
    this->os << "y=\"" << canvasMarginPix_ + dotWidthPix_ * y + dotMarginPix_ * y << "\"" << std::endl;
    this->os << "id=\"" << glyphID++ << "\"" << std::endl;
    this->os << "style=\"fill:#" + strColor + ";stroke:none;\" />" << std::endl;
    this->backgroundHeightPix_ = canvasMarginPix_ + dotWidthPix_ * y + dotMarginPix_ * y + dotWidthPix_ + canvasMarginPix_;
  }
}
