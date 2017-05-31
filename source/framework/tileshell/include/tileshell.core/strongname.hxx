//
//
// The MIT License(MIT)
// 
// Copyright(c) 2015 by Karol Grzybowski
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 
//
#pragma once
#ifndef _TileShell_Core_StrongName_H__
#define _TileShell_Core_StrongName_H__
//------------------------------------------------------------------------------------------------//
#include <tileshell/required.hxx>
#include <tileshell.core/types.hxx>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Core
{
namespace Internal
{
#define TILESHELL_STRONGNAME_HASH

template <uint32_t N, uint32_t I>
struct StringHash
{
    static uint32_t Hash(const char (&text)[N])
    {
        return (StringHash < N, I - 1 >::Hash(text) ^ text[I - 1]) * 16777619U;
    }
};

template <uint32_t N>
struct StringHash<N, 1>
{
    static uint32_t Hash(const char (&text)[N])
    {
        return (2166136261U ^ text[0]) * 16777619U;
    }
};
//((216 ^ t[0]) * 16) ^ t[1]) * 16) ^ t[2]) * 16
}

///
/// This struct represents internal TileShell strong name.
///
/// @remarks
///     In debug compilation, this struct contains raw, non-hashed string.
///
struct StrongName
{
private:
#ifndef TILESHELL_STRONGNAME_HASH
    TileShell::string_t     _name;
#else
    uint32_t                _name;

    explicit StrongName(uint32_t name)
        : _name(name)
    {
    }
#endif

public:
    ///
    /// Creates empty name.
    ///
    StrongName()
    {
#ifndef TILESHELL_STRONGNAME_HASH
        _name = "";
#else
        _name = 0U;
#endif
    }

    ///
    /// Creates name from specified string.
    ///
#ifndef TILESHELL_STRONGNAME_HASH
    explicit StrongName(const TileShell::string_t& text)
    {
        _name = text;
    }
#else
    template <uint32_t N>
    explicit StrongName(const char (&text)[N])
    {
        _name = Internal::StringHash<N, N>::Hash(text);
    }
#endif

    ///
    /// Creates name from dynamic string.
    ///
    static StrongName Create(const string_t& text)
    {
#ifndef TILESHELL_STRONGNAME_HASH
        return StrongName(text);
#else
        uint32_t hash = 2166136261U;

        for (string_t::const_iterator it = text.begin();
             it != text.end();
             ++it)
        {
            hash = (hash ^ *it) * 16777619U;
        }

        hash *= 16777619U;

        return StrongName(hash);
#endif
    }

    ///
    /// Gets empty strong name.
    ///
    static StrongName Empty()
    {
        return StrongName(0U);
    }

    bool operator == (const StrongName& value) const
    {
        return this->_name == value._name;
    }

    bool operator != (const StrongName& value) const
    {
        return this->_name != value._name;
    }

    bool operator < (const StrongName& value) const
    {
        return this->_name < value._name;
    }

    bool operator <= (const StrongName& value) const
    {
        return this->_name <= value._name;
    }

    bool operator > (const StrongName& value) const
    {
        return this->_name > value._name;
    }

    bool operator >= (const StrongName& value) const
    {
        return this->_name >= value._name;
    }
};

}
}
//------------------------------------------------------------------------------------------------//
#endif /* _TileShell_Core_StrongName_H__ */