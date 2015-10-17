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

#ifndef COLORMORSEPAINTING_COLOR_HPP_
#define COLORMORSEPAINTING_COLOR_HPP_

#include <cstdint>
#include <cmath>

namespace kallaballa
{
  typedef uint32_t Color;

  std::vector<size_t> toRGB(Color c) {
    size_t r = (c & 0xff0000) >> 16;
    size_t g =(c & 0x00ff00) >> 8;
    size_t b = c & 0x0000ff;

    return {r,g,b};
  }

  double euclideanDistance(Color a, Color b) {
    auto rgbA = toRGB(a);
    auto rgbB = toRGB(b);
    return std::hypot(std::hypot(rgbA[0]-rgbB[0],rgbA[1]-rgbB[1]),rgbA[2]-rgbB[2]);
  }
}

/* namespace kallaballa */
#endif /* COLORMORSEPAINTING_COLOR_HPP_ */
