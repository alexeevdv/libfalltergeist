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

// Libfalltergeist includes
#include "../Txt/BaseFile.h"

// Third party includes


namespace libfalltergeist
{
namespace Txt
{


BaseFile::BaseFile(std::ifstream* stream) : Item(stream)
{
}

BaseFile::BaseFile(Dat::Entry* datFileEntry) : Item(datFileEntry)
{
}

void BaseFile::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    std::istream istr(this);
    _parseText(istr);
}

}
}