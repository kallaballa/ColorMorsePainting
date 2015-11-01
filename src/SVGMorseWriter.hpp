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

#ifndef SVGMORSEWRITER_HPP_
#define SVGMORSEWRITER_HPP_

#include "Color.hpp"
#include <stdint.h>
#include <iostream>
#include <sstream>

namespace kallaballa {

  class SVGMorseWriter {
public:
    enum Alignment {
      LEFT,
      CENTER,
      RIGHT
    };
private:
    const double PIXEL_TO_MM = 3.5434;

    std::ostream& os;
    Alignment align_;
    RGBColor background_;
    size_t roundedRadiusX_;
    size_t roundedRadiusY_;
    size_t dashWidthFactor_;
    size_t x_;
    size_t y_;
    size_t dotsPerRow_;
    size_t dotWidthPix_;
    size_t dotMarginPix_;
    size_t canvasMarginPix_;
    size_t backgroundWidthPix_;
    size_t backgroundHeightPix_;
    size_t glyphID = 0;
    std::ostringstream lineBuffer_;

    void writeHeader();
    void writeFooter();
    void newLine();
public:

    SVGMorseWriter(std::ostream& ostream, Alignment align, RGBColor background, size_t roundedRadiusX, size_t roundedRadiusY, size_t dashWidthFactor, size_t dotsPerRow, size_t dotWidthMM, size_t dotMarginMM, size_t canvasMarginMM) ;
    virtual ~SVGMorseWriter();

    void writeDot(RGBColor c);
    void writeDash(RGBColor c);
    void writeSpace();

    size_t dotsPerRow() const {
      return dotsPerRow_;
    }
  };
}

#endif /* SVGMORSEWRITER_HPP_ */
