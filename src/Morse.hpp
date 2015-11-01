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

#ifndef MORSE_HPP_
#define MORSE_HPP_

#include <map>
#include <string>

namespace kallaballa {

class MorseTranslator {
  static std::map<const wchar_t, const std::wstring> morseMap_;

public:
  const std::wstring translate(const wchar_t& c) const {
    return morseMap_[c];
  }
};
}

#endif /* MORSE_HPP_ */
