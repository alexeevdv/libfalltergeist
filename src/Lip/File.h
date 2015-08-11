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

#ifndef LIBFALLTERGEIST_LIP_FILE_H
#define LIBFALLTERGEIST_LIP_FILE_H

// C++ standard includes
#include <string>
#include <vector>

// libfalltergeist includes
#include "../Dat/Item.h"

// Third party includes

namespace libfalltergeist
{
namespace Lip
{

class File : public Dat::Item
{

public:
    File(Dat::Entry* datFileEntry);
    File(std::ifstream* stream);
    ~File();
    void init();
    std::string acmName();
    uint32_t pcount();
    uint32_t mcount();
    uint32_t acmSize();
    std::vector<uint32_t>* timestamps();

protected:
    virtual void _initialize();
    uint32_t _version;
    uint32_t _unknown1;
    uint32_t _unknown2;
    uint32_t _unknown3;
    uint32_t _acm_size;
    uint32_t _phonems_count;
    uint32_t _unknown4;
    uint32_t _markers_count;
    uint8_t  _acm_name[8];
    uint8_t  _unknown5[4];
    std::vector<uint8_t> _phonems;
    std::vector<uint32_t> _marker_samples;
    std::vector<uint32_t> _marker_timestamps;

};

}
}
#endif // LIBFALLTERGEIST_LIP_FILE_H
