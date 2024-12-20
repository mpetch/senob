/*
 * Copyright (C) 2024 Nils Burkard
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "font.h"

// Definieren Sie ein einfaches 8x8 Bitmap-Font für ASCII-Zeichen von 0x20 bis 0x7E.
static uint8_t font[96][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x20 ' '
    {0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00}, // 0x21 '!'
    {0x36, 0x36, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x22 '"'
    {0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00}, // 0x23 '#'
    {0x18, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x18, 0x00}, // 0x24 '$'
    {0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00}, // 0x25 '%'
    {0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00}, // 0x26 '&'
    {0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x27 '''
    {0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00}, // 0x28 '('
    {0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00}, // 0x29 ')'
    {0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00}, // 0x2A '*'
    {0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00}, // 0x2B '+'
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x0C}, // 0x2C ','
    {0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00}, // 0x2D '-'
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00}, // 0x2E '.'
    {0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00}, // 0x2F '/'
    {0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00}, // 0x30 '0'
    {0x0C, 0x0E, 0x0F, 0x0C, 0x0C, 0x0C, 0x3F, 0x00}, // 0x31 '1'
    {0x3E, 0x63, 0x30, 0x1C, 0x06, 0x63, 0x7F, 0x00}, // 0x32 '2'
    {0x3E, 0x63, 0x30, 0x1C, 0x30, 0x63, 0x3E, 0x00}, // 0x33 '3'
    {0x1C, 0x1E, 0x1B, 0x19, 0x7F, 0x18, 0x1C, 0x00}, // 0x34 '4'
    {0x7F, 0x03, 0x3F, 0x60, 0x30, 0x63, 0x3E, 0x00}, // 0x35 '5'
    {0x3E, 0x63, 0x03, 0x3F, 0x63, 0x63, 0x3E, 0x00}, // 0x36 '6'
    {0x7F, 0x63, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00}, // 0x37 '7'
    {0x3E, 0x63, 0x63, 0x3E, 0x63, 0x63, 0x3E, 0x00}, // 0x38 '8'
    {0x3E, 0x63, 0x63, 0x7E, 0x60, 0x63, 0x3E, 0x00}, // 0x39 '9'
    {0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00}, // 0x3A ':'
    {0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x0C}, // 0x3B ';'
    {0x30, 0x18, 0x0C, 0x06, 0x0C, 0x18, 0x30, 0x00}, // 0x3C '<'
    {0x00, 0x00, 0x7E, 0x00, 0x00, 0x7E, 0x00, 0x00}, // 0x3D '='
    {0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00}, // 0x3E '>'
    {0x3E, 0x63, 0x30, 0x18, 0x18, 0x00, 0x18, 0x00}, // 0x3F '?'
    {0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x3E, 0x00}, // 0x40 '@'
    {0x18, 0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x00}, // 0x41 'A'
    {0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00}, // 0x42 'B'
    {0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00}, // 0x43 'C'
    {0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00}, // 0x44 'D'
    {0x7F, 0x03, 0x03, 0x1F, 0x03, 0x03, 0x7F, 0x00}, // 0x45 'E'
    {0x7F, 0x03, 0x03, 0x1F, 0x03, 0x03, 0x03, 0x00}, // 0x46 'F'
    {0x3E, 0x63, 0x03, 0x7B, 0x63, 0x63, 0x3E, 0x00}, // 0x47 'G'
    {0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00}, // 0x48 'H'
    {0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00}, // 0x49 'I'
    {0x78, 0x30, 0x30, 0x30, 0x30, 0x33, 0x1E, 0x00}, // 0x4A 'J'
    {0x67, 0x36, 0x1E, 0x0E, 0x1E, 0x36, 0x67, 0x00}, // 0x4B 'K'
    {0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x7F, 0x00}, // 0x4C 'L'
    {0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00}, // 0x4D 'M'
    {0x63, 0x67, 0x6F, 0x7F, 0x7B, 0x73, 0x63, 0x00}, // 0x4E 'N'
    {0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}, // 0x4F 'O'
    {0x3F, 0x66, 0x66, 0x3F, 0x03, 0x03, 0x03, 0x00}, // 0x50 'P'
    {0x3C, 0x66, 0x66, 0x66, 0x76, 0x3C, 0x70, 0x00}, // 0x51 'Q'
    {0x3F, 0x66, 0x66, 0x3F, 0x1E, 0x36, 0x63, 0x00}, // 0x52 'R'
    {0x3E, 0x63, 0x07, 0x1C, 0x70, 0x63, 0x3E, 0x00}, // 0x53 'S'
    {0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00}, // 0x54 'T'
    {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3E, 0x00}, // 0x55 'U'
    {0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00}, // 0x56 'V'
    {0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00}, // 0x57 'W'
    {0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00}, // 0x58 'X'
    {0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x00}, // 0x59 'Y'
    {0x7F, 0x63, 0x31, 0x18, 0x0C, 0x46, 0x7F, 0x00}, // 0x5A 'Z'
    {0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00}, // 0x5B '['
    {0x01, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x00}, // 0x5C '\'
    {0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00}, // 0x5D ']'
    {0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00}, // 0x5E '^'
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF}, // 0x5F '_'
    {0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x60 '`'
    {0x00, 0x00, 0x3C, 0x60, 0x7C, 0x66, 0x7C, 0x00}, // 0x61 'a'
    {0x03, 0x03, 0x3B, 0x67, 0x63, 0x63, 0x3F, 0x00}, // 0x62 'b'
    {0x00, 0x00, 0x3E, 0x63, 0x03, 0x63, 0x3E, 0x00}, // 0x63 'c'
    {0x60, 0x60, 0x7E, 0x63, 0x63, 0x63, 0x7E, 0x00}, // 0x64 'd'
    {0x00, 0x00, 0x3E, 0x63, 0x7F, 0x03, 0x3E, 0x00}, // 0x65 'e'
    {0x38, 0x6C, 0x0C, 0x1F, 0x0C, 0x0C, 0x0C, 0x00}, // 0x66 'f'
    {0x00, 0x00, 0x7E, 0x63, 0x63, 0x7E, 0x60, 0x3E}, // 0x67 'g'
    {0x03, 0x03, 0x3B, 0x67, 0x63, 0x63, 0x63, 0x00}, // 0x68 'h'
    {0x18, 0x00, 0x1C, 0x18, 0x18, 0x18, 0x3C, 0x00}, // 0x69 'i'
    {0x30, 0x00, 0x3C, 0x30, 0x30, 0x30, 0x33, 0x1E}, // 0x6A 'j'
    {0x03, 0x03, 0x63, 0x33, 0x1B, 0x0F, 0x1B, 0x00}, // 0x6B 'k'
    {0x1C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00}, // 0x6C 'l'
    {0x00, 0x00, 0x7F, 0x7F, 0x6B, 0x6B, 0x63, 0x00}, // 0x6D 'm'
    {0x00, 0x00, 0x3B, 0x67, 0x63, 0x63, 0x63, 0x00}, // 0x6E 'n'
    {0x00, 0x00, 0x3E, 0x63, 0x63, 0x63, 0x3E, 0x00}, // 0x6F 'o'
    {0x00, 0x00, 0x3F, 0x63, 0x63, 0x3F, 0x03, 0x03}, // 0x70 'p'
    {0x00, 0x00, 0x7E, 0x63, 0x63, 0x7E, 0x60, 0x60}, // 0x71 'q'
    {0x00, 0x00, 0x3B, 0x67, 0x03, 0x03, 0x03, 0x00}, // 0x72 'r'
    {0x00, 0x00, 0x7E, 0x03, 0x3E, 0x60, 0x3F, 0x00}, // 0x73 's'
    {0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x6C, 0x38, 0x00}, // 0x74 't'
    {0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x7E, 0x00}, // 0x75 'u'
    {0x00, 0x00, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00}, // 0x76 'v'
    {0x00, 0x00, 0x63, 0x63, 0x6B, 0x7F, 0x36, 0x00}, // 0x77 'w'
    {0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00}, // 0x78 'x'
    {0x00, 0x00, 0x63, 0x63, 0x63, 0x7E, 0x60, 0x3E}, // 0x79 'y'
    {0x00, 0x00, 0x3F, 0x31, 0x18, 0x4C, 0x3F, 0x00}, // 0x7A 'z'
    {0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00}, // 0x7B '{'
    {0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00}, // 0x7C '|'
    {0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00}, // 0x7D '}'
    {0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x7E '~'
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}  // 0x7F (DEL)
};

uint8_t* font_get_glyph(char c) {
    if (c < 0x20 || c > 0x7E) {
        return font[0]; // Leerzeichen für nicht definierte Zeichen
    }
    return font[c - 0x20];
}
