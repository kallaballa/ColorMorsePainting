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

#ifndef COLORMORSEPAINTING_HPP_
#define COLORMORSEPAINTING_HPP_

#include <stdint.h>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include "Color.hpp"

namespace kallaballa
{
using std::string;
using std::map;
using std::vector;
using std::ostream;

typedef unsigned char sample_t;

float PIXEL_TO_MM = 3.5434;

class SVGMorseWriter {
	std::ofstream ofs;
	size_t dotWidthPix;
	size_t dotMarginPix;
	size_t canvasMarginPix;
  size_t backgroundWidthPix;
  size_t backgroundHeightPix;
  size_t pixelID = 0;

	void writeHeader();
	void writeFooter();
public:
	SVGMorseWriter(const char* filename, size_t dotsPerRow, size_t dotWidthMM, size_t dotMarginMM, size_t canvasMarginMM) ;
	virtual ~SVGMorseWriter();

	void writeDot(size_t x, size_t y, RGBColor c);
  void writeDash(size_t x, size_t y, RGBColor c);

};
}

/* namespace kallaballa */
#endif /* COLORMORSEPAINTING_HPP_ */
