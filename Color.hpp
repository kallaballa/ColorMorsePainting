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

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include "CIEDE2000.hpp"
#include <cstdint>
#include <cmath>
#include <random>

namespace kallaballa
{
  typedef uint32_t RGBColor;

  inline std::vector<size_t> unpack(RGBColor c) {
    size_t r = (c & 0xff0000) >> 16;
    size_t g =(c & 0x00ff00) >> 8;
    size_t b = c & 0x0000ff;

    return {r,g,b};
  }

  inline std::vector<double> toXYC(RGBColor c) {
    std::vector<size_t> rgb = unpack(c);
    std::vector<double> xyz(3);
    double r = (rgb[0] / 255.0);
    double g = (rgb[1] / 255.0);
    double b = (rgb[2] / 255.0);

    if (r > 0.04045)
      r = pow(((r + 0.055) / 1.055),2.4);
    else
      r = r / 12.92;

    if (g > 0.04045)
      g = pow(((g + 0.055) / 1.055),2.4);
    else
      g = g / 12.92;

    if (b > 0.04045)
      b = pow(((b + 0.055) / 1.055),2.4);
    else
      b = b / 12.92;

    r *= 100;
    g *= 100;
    b *= 100;

  //Observer. = 2°, Illuminant = D65
    xyz[0] = r * 0.4124 + g * 0.3576 + b * 0.1805;
    xyz[1] = r * 0.2126 + g * 0.7152 + b * 0.0722;
    xyz[2] = r * 0.0193 + g * 0.1192 + b * 0.9505;
    return xyz;
  }

  inline std::vector<double> toLAB(RGBColor c) {
    std::vector<double> xyz = toXYC(c);
    std::vector<double> lab(3);
    double x = xyz[0] / 95.047; //Observer. = 2°, Illuminant = D65
    double y = xyz[1] / 100.000;
    double z = xyz[2] / 108.883;

    if ( x > 0.008856 )
      x = pow(x,( (double)1.0/3.0 ));
    else
      x = ( 7.787 * x ) + ( 16 / 116 );

    if ( y > 0.008856 )
      y = pow(y,( (double)1.0/3.0  ));
    else
      y = ( 7.787 * y ) + ( 16 / 116 );

    if ( z > 0.008856 )
      z = pow(z, (double)( 1.0/3.0  ));
    else
      z = ( 7.787 * z ) + ( 16 / 116 );

    lab[0] = ( 116 * y ) - 16;
    lab[1] = 500 * ( x - y );
    lab[2] = 200 * ( y - z );

    return lab;
  }

  inline double euclidian_distance(RGBColor a, RGBColor b) {
    auto rgbA = unpack(a);
    auto rgbB = unpack(b);
    return std::hypot(std::hypot(rgbA[0]-rgbB[0],rgbA[1]-rgbB[1]),rgbA[2]-rgbB[2]);
  }

  inline double ciede2000_distance(RGBColor a, RGBColor b) {
    auto labA = toLAB(a);
    auto labB = toLAB(b);
    CIEDE2000::LAB lab1 = {labA[0], labA[1], labA[2]};
    CIEDE2000::LAB lab2 = {labB[0], labB[1], labB[2]};

    return CIEDE2000::CIEDE2000(lab1, lab2);
  }

  inline std::vector<RGBColor> readColorsFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    std::vector<RGBColor> colors;
    std::string line;
    RGBColor c;
    while (std::getline(ifs, line)) {
      c = strtol(line.substr(1).c_str(), NULL, 16);
      colors.push_back(c);
    }

    return colors;
  }

  class ColorSelector {
    static std::random_device randDev_;
    RGBColor lastColor_ = 0;
    std::vector<RGBColor> palette_;

    std::mt19937 rng_;
    std::uniform_int_distribution<int> uni_;
  public:
    ColorSelector(std::vector<RGBColor> palette) : palette_(palette), rng_(randDev_()), uni_(0,palette.size() - 1) {
    }

    RGBColor next() {
      if(lastColor_ == 0) {
        return lastColor_ = palette_[uni_(rng_)];
      } else {
        RGBColor selected;
        while(ciede2000_distance(lastColor_, selected = palette_[uni_(rng_)] ) < 50.0) {}
        return lastColor_ = selected;;
      }
    }
  };
}

/* namespace kallaballa */
#endif /* COLOR_HPP_ */
