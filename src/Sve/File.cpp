/*
 * Copyright 2012-2015 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

// C++ standard includes

// libfalltergeist includes
#include "../Sve/File.h"
#include "../Exception.h"

// Third party includes

namespace libfalltergeist
{
namespace Sve
{

File::File(Dat::Entry* datFileEntry) : Dat::Item(datFileEntry)
{
    _initialize();
}

File::File(std::ifstream* stream) : Dat::Item(stream)
{
    _initialize();
}

File::~File()
{
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    std::string line;

    unsigned char ch;
    for(unsigned int i = 0; i != this->size(); ++i)
    {
        *this >> ch;
        if (ch == 0x0D) // \r
        {
            // do nothing
        }
        else if (ch == 0x0A) // \n
        {
            _addString(line);
            line.clear();
        }
        else
        {
            line += ch;
        }
    }
    if (line.size() != 0)
    {
        _addString(line);
    }
}

void File::_addString(std::string line)
{
    auto pos = line.find(":");
    if (pos != std::string::npos)
    {
        auto frame = line.substr(0, pos);
        line = line.substr(pos+1);
        _subs.insert(std::pair<int,std::string>(std::stoi(frame),line));
    }
}

std::pair<int,std::string> File::getSubLine(int frame)
{
    _initialize();
    auto it = _subs.lower_bound(frame);

    if (it != _subs.end())
        return *it;
    else
        return std::pair<int,std::string>(999999, "");
}

}
}
