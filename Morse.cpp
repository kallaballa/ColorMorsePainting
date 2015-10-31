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

#include "Morse.hpp"

namespace kallaballa {
  // International standard code take from: https://de.wikipedia.org/wiki/Morsezeichen#Standard-Codetabelle
  std::map<const wchar_t, const std::wstring> MorseTranslator::morseMap_  = {
      {' ', L" "},
      {L'\n', L"\n"},
      {L'A', L".-"},
      {L'B', L"-..."},
      {L'C', L"-.-."},
      {L'D', L"-.."},
      {L'E', L"."},
      {L'F', L"..-."},
      {L'G', L"--."},
      {L'H', L"...."},
      {L'I', L".."},
      {L'J', L".---"},
      {L'K', L"-.-"},
      {L'L', L".-.."},
      {L'M', L"--"},
      {L'N', L"-."},
      {L'O', L"---"},
      {L'P', L".--."},
      {L'Q', L"--.-"},
      {L'R', L".-."},
      {L'S', L"..."},
      {L'T', L"-"},
      {L'U', L"..-"},
      {L'V', L"...-"},
      {L'W', L".--"},
      {L'X', L"-..-"},
      {L'Y', L"-.--"},
      {L'Z', L"--.."},
      {L'1', L".----"},
      {L'2', L"..---"},
      {L'3', L"...--"},
      {L'4', L"....-"},
      {L'5', L"....."},
      {L'6', L"-...."},
      {L'7', L"--..."},
      {L'8', L"---.."},
      {L'9', L"----."},
      {L'0', L"-----"},
      {L'.', L".-.-.-"},
      {L',', L"--..--"},
      {L':', L"---..."},
      {L';', L"-.-.-."},
      {L'?', L"..--.."},
      {L'-', L"-....-"},
      {L'_', L"..--.-"},
      {L'(', L"-.--."},
      {L')', L"-.--.-"},
      {L'\'', L".----."},
      {L'=', L"-...-"},
      {L'+', L".-.-."},
      {L'/', L"-..-."},
      {L'@', L".--.-."},
      {L'À', L".--.-"},
      {L'Å', L".--.-"},
      {L'Ä', L".-.-"},
      {L'È', L".-..-"},
      {L'É', L"..-.."},
      {L'Ö', L"---."},
      {L'Ü', L"..--"},
      {L'ß', L"...--.."},
      {L'Ñ', L"--.--"},
      {L'\x04', L"...-.-"}, //EOT = SK
  };
}
