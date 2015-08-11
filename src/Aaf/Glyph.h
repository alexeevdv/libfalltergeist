/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2015 Falltergeist developers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef LIBFALLTERGEIST_GLYPH_H
#define LIBFALLTERGEIST_GLYPH_H

// C++ standard includes
#include <cstdint>
#include <vector>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
namespace Aaf
{

class Glyph
{

public:
    Glyph(uint16_t width, uint16_t height);
    ~Glyph();

    std::vector<unsigned char>* data();

    uint16_t width() const;
    void setWidth(uint16_t width);

    uint16_t height() const;
    void setHeight(uint16_t height);

    uint32_t dataOffset() const;
    void setDataOffset(uint32_t value);

protected:
    uint16_t _width = 0;
    uint16_t _height = 0;
    uint32_t _dataOffset = 0;

    std::vector<unsigned char> _data;

};

}
}
#endif // LIBFALLTERGEIST_GLYPH_H
