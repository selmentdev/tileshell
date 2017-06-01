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
#ifndef _TileShell_Core_Referenced_H__
#define _TileShell_Core_Referenced_H__

#include <tileshell/required.hxx>
#include <tileshell.core/allocator.hxx>

namespace TileShell::Core
{
    typedef int32_t refcount_t;

    ///
    /// This class represents referenced object.
    ///
    class Referenced
    {
    private:
        refcount_t  _refcount;

    public:
        Referenced()
            : _refcount(0)
        {
        }

        virtual ~Referenced()
        {
            //assert(_refcount == 0);
        }

        ///
        /// Acquires reference of the specified object.
        ///
        /// @returns
        ///     A number of references to this object.
        ///
        refcount_t AddRef()
        {
            return ++_refcount;
        }

        ///
        /// Releases reference of the specified object.
        ///
        /// @returns
        ///     A number of references to this object.
        ///
        refcount_t Release()
        {
            if (--_refcount == 0)
            {
                delete this;

                return 0;
            }

            return _refcount;
        }
    };

}

#endif /* _TileShell_Core_Referenced_H__ */