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

// C++ standard includes
#include <string>
#include <cstdlib>

// libfalltergeist includes
#include "../Msg/File.h"
#include "../Msg/Message.h"
#include "../Exception.h"

// Third party includes

namespace libfalltergeist
{
namespace Msg
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
    for (auto message : _messages)
    {
        delete message;
    }
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    /*
     * Because of bug in CMBATAI2.MSG in messages #1382 and #32020 we need to explode each line with '{' symbol
     * Any extra '}' symbols must be trimed from exploded parts
     */

    while (this->position() < this->size())
    {
        uint8_t chr = uint8();
        if (chr == '{')
        {
            std::string number;
            std::string sound;
            std::string text;
            chr = 0;
            // number
            while (chr != '{')
            {
                chr = uint8();
                if (chr != '{' && chr != '}')
                {
                    number += chr;
                }
            }

            // sound
            chr = 0;
            while (chr != '{')
            {
                chr = uint8();
                if (chr != '{' && chr != '}')
                {
                    sound += chr;
                }
            }

            chr = 0;
            // text
            while (chr != '}' && chr != '{' && this->position() < this->size())
            {
                chr = uint8();
                if (chr != '{' && chr != '}')
                {
                    text += chr;
                }
            }

            // "put back" last character
            this->setPosition(this->position() - 1);

            while (text.find("\n") != std::string::npos)
            {
                text.replace(text.find("\n"), 1, "");
            }

            auto message = new Message();
            message->setNumber(std::stoi(number));
            message->setSound(sound);
            message->setText(text);
            _messages.push_back(message);
        }
    }
}

std::vector<Message*>* File::messages()
{
    return &_messages;
}

Message* File::message(unsigned int number)
{
    for (auto message : _messages)
    {
        if (message->number() == number)
        {
            return message;
        }
    }
    throw Exception("File::message() - number is out of range: " + std::to_string(number));
}

}
}
