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
#include "../Map/Script.h"

// Third party includes

namespace libfalltergeist
{
namespace Map
{

Script::Script()
{
}

Script::~Script()
{
}

int32_t Script::PID() const
{
    return _PID;
}

void Script::setPID(int32_t PID)
{
    _PID = PID;
}

int32_t Script::scriptId() const
{
    return _scriptId;
}

void Script::setScriptId(int32_t value)
{
    _scriptId = value;
}

}
}
