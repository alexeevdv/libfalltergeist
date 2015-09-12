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

#ifndef LIBFALLTERGEIST_TXT_CSVPARSER_H
#define LIBFALLTERGEIST_TXT_CSVPARSER_H

// C++ standard includes
#include <list>
#include <memory>
#include <string>
#include <vector>

// Libfalltergeist includes
#include "../Ini/Value.h"
#include "../Txt/Parser.h"

// Third party includes

namespace libfalltergeist
{
namespace Txt
{

typedef std::list<std::vector<Ini::Value>> CSVFile;

/**
 * @brief Parser of CSV files.
 */
class CSVParser : public Parser
{
public:
    CSVParser(std::istream &stream);
    ~CSVParser();

    std::unique_ptr<CSVFile> parse();

private:
    std::istream &_stream; // stream to parse

protected:

    void _stripComments(std::string& line);

};

}
}
#endif // LIBFALLTERGEIST_TXT_CSVPARSER_H
