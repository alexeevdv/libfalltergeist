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
#include "../Txt/CSVBasedFile.h"
#include "../Txt/CSVParser.h"

// Third party includes


namespace libfalltergeist
{
namespace Txt
{

template <typename ItemType>
CSVBasedFile<ItemType>::CSVBasedFile(std::ifstream* stream) : BaseFile(stream)
{
    _initialize();
}

template <typename ItemType>
CSVBasedFile<ItemType>::CSVBasedFile(Dat::Entry* datFileEntry) : BaseFile(datFileEntry)
{
    _initialize();
}

template <typename ItemType>
const std::list<ItemType>& CSVBasedFile<ItemType>::items() const
{
    return _items;
}

template <typename ItemType>
void CSVBasedFile<ItemType>::_parseText(std::istream& istr)
{
    CSVParser parser(istr);
    auto csv = parser.parse();
    for (auto& row : *csv)
    {
        try
        {
            _items.push_back(_parseItem(row));
        }
        catch (std::out_of_range)
        {
            // TODO: warnings?
        }
    }
}

template <>
EndDeath CSVBasedFile<EndDeath>::_parseItem(const std::vector<Ini::Value>& row)
{
    if (row.size() < 7)
    {
        throw std::out_of_range("Expected 7 elements.");
    }
    EndDeath item;
    item.globalVar = row[0].toInt();
    item.minValue = row[1].toInt();
    item.worldAreaKnown = row[2].toInt();
    item.worldAreaNotKnown = row[3].toInt();
    item.minLevel = row[4].toInt();
    item.chance = static_cast<unsigned char>(row[5].toInt());
    item.narratorFile = row[6].str();
    return item;
}

template <>
EndGame CSVBasedFile<EndGame>::_parseItem(const std::vector<Ini::Value>& row)
{
    if (row.size() < 4)
    {
        throw std::out_of_range("Expected at least 4 elements.");
    }
    EndGame item;
    item.globalVar = row[0].toInt();
    item.value = row[1].toInt();
    item.artIdx = row[2].toInt();
    item.narratorFile = row[3].str();
    if (row.size() > 4)
    {
        item.direction = row[4].toInt();
    }
    return item;
}

template <>
GenRep CSVBasedFile<GenRep>::_parseItem(const std::vector<Ini::Value>& row)
{
    GenRep item;
    item.threshold = row.at(0).toInt();
    item.messageId = row.at(1).toInt();
    return item;
}

template <>
Holodisk CSVBasedFile<Holodisk>::_parseItem(const std::vector<Ini::Value>& row)
{
    Holodisk item;
    item.globalVar = row.at(0).toInt();
    item.titleMessageId = row.at(1).toInt();
    item.textMessageId = row.at(2).toInt();
    return item;
}

template <>
KarmaVar CSVBasedFile<KarmaVar>::_parseItem(const std::vector<Ini::Value>& row)
{
    KarmaVar item;
    item.globalVar = row.at(0).toInt();
    item.artIdx = row.at(1).toInt();
    item.nameMessageId = row.at(2).toInt();
    item.descriptionMessageId = row.at(3).toInt();
    return item;
}

template <>
Quest CSVBasedFile<Quest>::_parseItem(const std::vector<Ini::Value>& row)
{
    if (row.size() < 5)
    {
        throw std::out_of_range("Expected 5 elements.");
    }
    Quest item;
    item.locationMessageId = row[0].toInt();
    item.descriptionMessageId = row[1].toInt();
    item.globalVar = row[2].toInt();
    item.displayTreshold = row[3].toInt();
    item.completedThreshold = row[4].toInt();
    return item;
}

template class CSVBasedFile<EndDeath>;
template class CSVBasedFile<EndGame>;
template class CSVBasedFile<GenRep>;
template class CSVBasedFile<Holodisk>;
template class CSVBasedFile<KarmaVar>;
template class CSVBasedFile<Quest>;

}
}