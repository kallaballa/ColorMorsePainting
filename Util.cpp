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

namespace kallaballa {

std::wstring utf8_to_utf32(const std::string& s) {
    typedef unsigned char byte;
    struct Level {
        byte Head, Data, Null;
        Level(byte h, byte d) {
            Head = h; // the head shifted to the right
            Data = d; // number of data bits
            Null = h << d; // encoded byte with zero data bits
        }
        bool encoded(byte b) { return b>>Data == Head; }
    }; // struct Level
    Level lev[] = {
        Level(2, 6),
        Level(6, 5),
        Level(14, 4),
        Level(30, 3),
        Level(62, 2),
        Level(126, 1)
    };

    wchar_t wc = 0;
    const char * p = s.c_str();
    std::wstring result;
    while (*p != 0) {
        byte b = *p++;
        if (b>>7 == 0) { // deal with ASCII
            wc = b;
            result.push_back(wc);
            continue;
        } // ASCII
        bool found = false;
        for (size_t i = 1; i < sizeof(lev)/sizeof(lev[0]); ++i) {
            if (lev[i].encoded(b)) {
                wc = b ^ lev[i].Null; // remove the head
                wc <<= lev[0].Data * i;
                for (size_t j = i; j > 0; --j) { // trailing bytes
                    if (*p == 0) return result; // unexpected
                    b = *p++;
                    if (!lev[0].encoded(b)) // encoding corrupted
                        return result;
                    wchar_t tmp = b ^ lev[0].Null;
                    wc |= tmp << lev[0].Data*(j-1);
                } // trailing bytes
                result.push_back(wc);
                found = true;
                break;
            } // lev[i]
        }   // for lev
        if (!found) return result; // encoding incorrect
    }   // while
    return result;
}

}
