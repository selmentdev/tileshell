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
#ifndef _TileShell_Core_Reference_H__
#define _TileShell_Core_Reference_H__
//------------------------------------------------------------------------------------------------//
#include <TileShell/Required.h>
#include <TileShell/Core/Referenced.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Core
{

///
/// This class represents reference to the type T.
///
/// @tparam T
///     A referenced type.
///
template <typename T>
class Reference
{
private:
    T* _pointer;

public:
    typedef T Type;

    Reference(T* pointer = nullptr)
        : _pointer(pointer)
    {
        if ((pointer != nullptr))
        {
            pointer->AddRef();
        }
    }

    Reference(const Reference<T>& reference)
        : _pointer(reference._pointer)
    {
        if ((_pointer != nullptr))
        {
            _pointer->AddRef();
        }
    }

    ~Reference()
    {
        if ((_pointer != nullptr))
        {
            _pointer->Release();
        }
    }

    Reference<T>& operator = (T* pointer)
    {
        if ((_pointer != nullptr))
        {
            _pointer->Release();
        }

        _pointer = pointer;

        if ((_pointer != nullptr))
        {
            _pointer->AddRef();
        }

        return (*this);
    }

    Reference<T>& operator = (const Reference<T>& reference)
    {
        if (this != &reference)
        {
            if ((reference._pointer != nullptr))
            {
                reference._pointer->AddRef();
            }

            if ((_pointer != nullptr))
            {
                _pointer->Release();
            }

            _pointer = reference._pointer;
        }

        return (*this);
    }

    template <typename U>
    Reference<T>& operator = (U* pointer)
    {
        if ((_pointer != nullptr))
        {
            _pointer->Release();
        }

        _pointer = static_cast<T*>(pointer);

        if ((_pointer != nullptr))
        {
            _pointer->AddRef();
        }

        return (*this);
    }

    template <typename U>
    Reference<T>& operator = (const Reference<U>& reference)
    {
        if ((_pointer != nullptr))
        {
            _pointer->Release();
        }

        _pointer = static_cast<T*>(reference._pointer);

        if ((_pointer != nullptr))
        {
            _pointer->AddRef();
        }

        return (*this);
    }

    operator T* () const
    {
        return _pointer;
    }

    operator const T* () const
    {
        return _pointer;
    }

    T& operator * () const
    {
        assert(_pointer != nullptr);
        return (*_pointer);
    }

    T* operator -> () const
    {
        assert(_pointer != nullptr);
        return _pointer;
    }

    bool IsValid() const
    {
        return _pointer != nullptr;
    }

    T* GetPointer() const
    {
        return _pointer;
    }

    operator bool () const
    {
        return _pointer != nullptr;
    }

    bool operator ! () const
    {
        return _pointer == nullptr;
    }

    bool operator == (const T* pointer) const
    {
        return _pointer == pointer;
    }

    bool operator == (const Reference<T>& reference) const
    {
        return _pointer == reference._pointer;
    }

    bool operator != (const T* pointer) const
    {
        return _pointer != pointer;
    }

    bool operator != (const Reference<T>& reference) const
    {
        return _pointer != reference._pointer;
    }

    template <typename TTarget>
    TTarget* cast()
    {
        return static_cast<TTarget*>(_pointer);
    }

    template <typename TTarget>
    TTarget* safe_cast()
    {
        return dynamic_cast<TTarget*>(_pointer);
    }
};
//------------------------------------------------------------------------------------------------//
template <typename T>
inline bool operator == (const Reference<T>& reference, nullptr_t)
{
    return (T*)reference == nullptr;
}
//------------------------------------------------------------------------------------------------//
template <typename T>
inline bool operator == (nullptr_t, const Reference<T>& reference)
{
    return (T*)reference == nullptr;
}
//------------------------------------------------------------------------------------------------//
template <typename T>
inline bool operator != (const Reference<T>& reference, nullptr_t)
{
    return (T*)reference != nullptr;
}
//------------------------------------------------------------------------------------------------//
template <typename T>
inline bool operator != (nullptr_t, const Reference<T>& reference)
{
    return (T*)reference != nullptr;
}
//------------------------------------------------------------------------------------------------//
}
}
//------------------------------------------------------------------------------------------------//
#endif /* _TileShell_Core_Reference_H__ */