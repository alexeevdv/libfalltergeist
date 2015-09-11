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
#include "Lexer.h"

// Third party includes

namespace libfalltergeist
{

namespace Txt
{


int Lexer::lex()
{
    if (_recallToken)
    {
        _recallToken = false;
    }
    else
    {
        _lastToken = _nextToken();
    }
    return _lastToken.type;
}

void Lexer::unLex()
{
    _recallToken = true;
}

bool Lexer::eof()
{
    return _stream.eof();
}

bool Lexer::expect(int type)
{
    if (lex() != type)
    {
        unLex();
        return false;
    }
    return true;
}

const Lexer::Token& Lexer::last()
{
    return _lastToken;
}

Lexer::Token Lexer::_nextToken()
{
    Lexer::Token token;
    auto ch = _stream.get();
    // skip any leading whitespaces
    while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
    {
        ch = _stream.get();
    }
    if (ch >= '0' && ch <= '9')
    {
        do
        {
            token.intData *= 10;
            token.intData += (ch - '0');
            token.data.push_back((char)ch);
            ch = _stream.get();
        } while (ch >= '0' && ch <= '9');

        if (ch == '%') // skip percent sign
        {
            token.data.push_back('%');
        }
        else
        {
            _stream.unget();
        }
        token.type = T_CONSTANT;
    }
    else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
    {
        std::string lc;
        do
        {
            lc.push_back((char)std::tolower(ch));
            token.data.push_back((char)ch);
            ch = _stream.get();
        } while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || (ch == '_'));
        _stream.unget();
        if (lc == "if")
        {
            token.type = T_IF;
        }
        else if (lc == "and")
        {
            token.type = T_AND;
        }
        else if (lc == "or")
        {
            token.type = T_OR;
        }
        else
        {
            token.type = T_IDENTIFIER;
        }
    }
    else if (ch == '>')
    {
        if (_stream.get() == '=')
        {
            token.type = T_GREATER_EQUAL;
        }
        else
        {
            token.type = '>';
            _stream.unget();
        }
    }
    else if (ch == '<')
    {
        if (_stream.get() == '=')
        {
            token.type = T_LESS_EQUAL;
        }
        else
        {
            token.type = '<';
            _stream.unget();
        }
    }
    else if (ch == '=')
    {
        if (_stream.get() == '=')
        {
            token.type = T_EQUAL;
        }
        else
        {
            token.type = '=';
            _stream.unget();
        }
    }
    else if (ch != std::char_traits<char>::eof())
    {
        token.type = (int)ch;
        //token.data.push_back((char)ch);
    }
    else
    {
        token.type = T_EOF;
    }
    return token;
}

char Lexer::_get(Lexer::Token& token)
{
    char ch = (char)_stream.get();
    token.data += ch;
    return ch;
}


Lexer::Lexer(const std::string& line) : _stream(line)
{
}

}
}
