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

  SVGMorseWriter::SVGMorseWriter(std::ostream& os, Alignment align, RGBColor background, size_t roundedRadiusX, size_t roundedRadiusY, size_t dashWidthFactor, size_t dotsPerRow, size_t dotWidthMM, size_t dotMarginMM, size_t canvasMarginMM) :
    os(os),
    align_(align),
    background_(background),
    roundedRadiusX_(roundedRadiusX),
    roundedRadiusY_(roundedRadiusY),
    dashWidthFactor_(dashWidthFactor),
    x_(0),
    y_(0),
    dotsPerRow_(dotsPerRow),
    dotWidthPix_(dotWidthMM * PIXEL_TO_MM),
    dotMarginPix_(dotMarginMM * PIXEL_TO_MM),
    canvasMarginPix_(canvasMarginMM * PIXEL_TO_MM),
    backgroundWidthPix_(dotsPerRow * dotWidthPix_ + dotsPerRow * dotMarginPix_ + canvasMarginPix_ * 2 - dotMarginPix_),
    backgroundHeightPix_(0),
    lineBuffer_() {
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
    this->os << "<defs><g id=\"foreground\"><g>" << std::endl;
  }

  void SVGMorseWriter::writeFooter() {
    if(!lineBuffer_.str().empty())
      this->newLine();

    std::stringstream sstream;
    sstream << std::setfill('0') << std::setw(6) << std::hex << background_;
    std::string strBackground = sstream.str();

    this->os << "</g></g><g id=\"background\">" << std::endl;
    this->os << "<rect" << std::endl;
    this->os << "width=\"" << backgroundWidthPix_ << "\"" << std::endl;
    this->os << "height=\"" << backgroundHeightPix_ << "\"" << std::endl;
    this->os << "x=\"0\"" << std::endl;
    this->os << "y=\"0\"" << std::endl;
    this->os << "id=\"-1\"" << std::endl;
    this->os << "style=\"stroke-width: 0px; fill: #" + strBackground + ";\"/>" << std::endl;
    this->os << "</g></defs>" << std::endl;
    //do the drawing in the right order
    this->os << "<use xlink:href=\"#background\" />" << std::endl;
    this->os << "<use xlink:href=\"#foreground\" />" << std::endl;
    this->os << "</svg>" << std::endl;
  }

  void SVGMorseWriter::newLine() {
    size_t remainder = this->dotsPerRow() - x_;
    double transX = 0;

    if(remainder > 0) {
      if(align_ == CENTER) {
        transX = ((double)(dotWidthPix_ * remainder + dotMarginPix_ * remainder))/2.0;
      } else if(align_ == RIGHT) {
        transX = dotWidthPix_ * remainder + dotMarginPix_ * remainder;
      } else {
        //nothing to do for LEFT
      }
    }

    this->os << "<g" << " transform=\"translate(" << transX << ",0)\"" << ">" << std::endl;
    this->os << lineBuffer_.str() << std::endl;
    this->os << "</g>" << std::endl;
    this->lineBuffer_.str("");
    ++this->y_;
    this->x_ = 0;
  }

  void SVGMorseWriter::writeDot(RGBColor c) {
    if(x_ + 1 > this->dotsPerRow()) {
      this->newLine();
    }

    std::stringstream sstream;
    sstream << std::setfill('0') << std::setw(6) << std::hex << c;
    std::string strColor = sstream.str();

    this->lineBuffer_ << "<rect" << "\n";
    this->lineBuffer_ << "width=\"" << dotWidthPix_ << "\"" << '\n';
    this->lineBuffer_ << "height=\"" << dotWidthPix_ << "\"" << '\n';
    this->lineBuffer_ << "rx=\"" << roundedRadiusX_ << "\"" << '\n';
    this->lineBuffer_ << "ry=\"" << roundedRadiusY_ << "\"" << '\n';
    this->lineBuffer_ << "x=\"" << canvasMarginPix_ + dotWidthPix_ * x_ + dotMarginPix_ * x_ << "\"" << '\n';
    this->lineBuffer_ << "y=\"" << canvasMarginPix_ + dotWidthPix_ * y_ + dotMarginPix_ * y_ << "\"" << '\n';
    this->lineBuffer_ << "id=\"" << glyphID++ << "\"" << '\n';
    this->lineBuffer_ << "style=\"fill:#" << strColor << ";stroke:none;\" />" << '\n';

    this->backgroundHeightPix_ = canvasMarginPix_ + dotWidthPix_ * y_ + dotMarginPix_ * y_ + dotWidthPix_ + canvasMarginPix_;
    ++x_;
  }

  void SVGMorseWriter::writeDash(RGBColor c) {
    if(x_ + dashWidthFactor_ > this->dotsPerRow()) {
      this->newLine();
    }

    std::stringstream sstream;
    sstream << std::setfill('0') << std::setw(6) << std::hex << c;
    std::string strColor = sstream.str();

    this->lineBuffer_ << "<rect" << '\n';
    this->lineBuffer_ << "width=\"" << dotWidthPix_ * dashWidthFactor_ + dotMarginPix_ * (dashWidthFactor_ - 1) << "\"" << '\n';
    this->lineBuffer_ << "height=\"" << dotWidthPix_ << "\"" << '\n';
    this->lineBuffer_ << "rx=\"" << roundedRadiusX_ << "\"" << '\n';
    this->lineBuffer_ << "ry=\"" << roundedRadiusY_ << "\"" << '\n';
    this->lineBuffer_ << "x=\"" << canvasMarginPix_ + dotWidthPix_ * x_ + dotMarginPix_ * x_ << "\"" << '\n';
    this->lineBuffer_ << "y=\"" << canvasMarginPix_ + dotWidthPix_ * y_ + dotMarginPix_ * y_ << "\"" << '\n';
    this->lineBuffer_ << "id=\"" << glyphID++ << "\"" << '\n';
    this->lineBuffer_ << "style=\"fill:#" << strColor << ";stroke:none;\" />" << '\n';

    this->backgroundHeightPix_ = canvasMarginPix_ + dotWidthPix_ * y_ + dotMarginPix_ * y_ + dotWidthPix_ + canvasMarginPix_;
    x_+=dashWidthFactor_;
  }

  void SVGMorseWriter::writeSpace() {
    if(x_ + 1 > this->dotsPerRow()) {
      this->newLine();
    }

    std::stringstream sstream;
    sstream << std::setfill('0') << std::setw(6) << std::hex << background_;
    std::string strColor = sstream.str();

    this->lineBuffer_ << "<rect" << '\n';
    this->lineBuffer_ << "width=\"" << dotWidthPix_ << "\"" << '\n';
    this->lineBuffer_ << "height=\"" << dotWidthPix_ << "\"" << '\n';
    this->lineBuffer_ << "rx=\"" << roundedRadiusX_ << "\"" << '\n';
    this->lineBuffer_ << "ry=\"" << roundedRadiusY_ << "\"" << '\n';
    this->lineBuffer_ << "x=\"" << canvasMarginPix_ + dotWidthPix_ * x_ + dotMarginPix_ * x_ << "\"" << '\n';
    this->lineBuffer_ << "y=\"" << canvasMarginPix_ + dotWidthPix_ * y_ + dotMarginPix_ * y_ << "\"" << '\n';
    this->lineBuffer_ << "id=\"" << glyphID++ << "\"" << '\n';
    this->lineBuffer_ << "style=\"fill:#" << strColor << ";stroke:none;\" />" << '\n';

    this->backgroundHeightPix_ = canvasMarginPix_ + dotWidthPix_ * y_ + dotMarginPix_ * y_ + dotWidthPix_ + canvasMarginPix_;
    ++x_;
  }
}

