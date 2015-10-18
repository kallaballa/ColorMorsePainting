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

namespace kallaballa {

  class SVGMorseWriter {
    const double PIXEL_TO_MM = 3.5434;

    std::ostream& os;
    size_t dotWidthPix;
    size_t dotMarginPix;
    size_t canvasMarginPix;
    size_t backgroundWidthPix;
    size_t backgroundHeightPix;
    size_t glyphID = 0;

    void writeHeader();
    void writeFooter();
  public:
    SVGMorseWriter(std::ostream& ostream, size_t dotsPerRow, size_t dotWidthMM, size_t dotMarginMM, size_t canvasMarginMM) ;
    SVGMorseWriter(const char* filename, size_t dotsPerRow, size_t dotWidthMM, size_t dotMarginMM, size_t canvasMarginMM) ;
    virtual ~SVGMorseWriter();

    void writeDot(size_t x, size_t y, RGBColor c);
    void writeDash(size_t x, size_t y, RGBColor c);
  };
}

#endif /* SVGMORSEWRITER_HPP_ */
