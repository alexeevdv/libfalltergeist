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

#ifndef LIBFALLTERGEIST_DAT_FILE_H
#define LIBFALLTERGEIST_DAT_FILE_H

// C++ standard includes
#include <cstdint>
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
namespace Dat
{

class Item;
class Entry;

class File
{

public:
    File();
    File(std::string pathToFile);
    virtual ~File();

    std::string filename();
    File* setFilename(std::string filename);

    Item* item(std::string filename);

    File* readBytes(char* destination, unsigned int numberOfBytes);
    File* skipBytes(unsigned int numberOfBytes);
    File* setPosition(unsigned int position);
    unsigned int position();
    unsigned int size();

    File& operator>>(int32_t &value);
    File& operator>>(uint32_t &value);
    File& operator>>(int16_t &value);
    File& operator>>(uint16_t &value);
    File& operator>>(int8_t &value);
    File& operator>>(uint8_t &value);
    File& operator>>(Entry &entry);

protected:
    std::map<std::string, Item*> _items;
    std::vector<Entry*> _entries;
    std::ifstream* _stream = nullptr;
    std::string _filename;
    bool _initialized = false;
    void _initialize();

};

}
}
#endif // LIBFALLTERGEIST_DAT_FILE_H
