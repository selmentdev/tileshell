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
#ifndef _TileShell_Core_Allocator_H__
#define _TileShell_Core_Allocator_H__

#include <tileshell/required.hxx>

namespace TileShell::Core
{
    ///
    /// This structure provides access to memory status.
    ///
    class MemoryStats
    {
        template <typename T> friend struct Allocator;
        template <typename T> friend struct AlignedAllocator;
        template <typename T> friend class StlAllocator;
    public:
        ///
        /// Gets total number of allocated memory.
        ///
        static size_t GetAllocatedMemory()
        {
            return _allocated;
        }

        ///
        /// Gets peek memory usage.
        ///
        static size_t GetMemoryPeak()
        {
            return _peak;
        }

    private:
        static size_t _allocated;
        static size_t _peak;

        ///
        /// Marks certain number of memory bytes as allocated.
        ///
        static size_t MarkAllocated(size_t amount)
        {
            _allocated += amount;
            _peak = std::max(_peak, _allocated);
            return _allocated;
        }

        ///
        /// Marks certain number of memory bytes as deallocated.
        static size_t MarkDeallocated(size_t amount)
        {
            _allocated -= amount;
            return _allocated;
        }
    };

    ///
    /// Aligned memory allocator.
    ///
    /// @tparam T
    ///     A type used for allocation.
    ///
    /// @note
    ///     Provides new and delete operators for memory aligned allocations.
    ///
    template <typename T>
    struct AlignedAllocator
    {
        static void* operator new (size_t size)
        {
            MemoryStats::MarkAllocated(sizeof(T));

            const size_t alignment = __alignof(T);
            static_assert(alignment > 8, "Allocator is useful for types with 8 > alignment");

            void* ptr = ::_aligned_malloc(size, alignment);

            return ptr;
        }

        static void operator delete(void* ptr)
        {
            MemoryStats::MarkDeallocated(sizeof(T));
            ::_aligned_free(ptr);
        }

        static void* operator new[](size_t size)
        {
            return operator new(size);
        }

            static void operator delete[](void* ptr)
        {
            operator delete (ptr);
        }
    };

    ///
    /// Default memory allocator.
    ///
    /// @tparam T
    ///     A type used for allocation.
    ///
    template <typename T>
    struct Allocator
    {
        static void* operator new (size_t size)
        {
            MemoryStats::MarkAllocated(sizeof(T));
            return ::operator new(size);
        }

        static void operator delete(void* ptr)
        {
            MemoryStats::MarkDeallocated(sizeof(T));
            ::operator delete(ptr);
        }

        static void* operator new[](size_t size)
        {
            return operator new(size);
        }

            static void operator delete[](void* ptr)
        {
            operator delete (ptr);
        }
    };

    template <typename T>
    class StlAllocator : public std::allocator<T>
    {
    public:
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T value_type;

        template <typename U>
        struct rebind
        {
            typedef StlAllocator<U> other;
        };

        pointer allocate(size_type n, const void* hint = nullptr)
        {
            MemoryStats::MarkAllocated(sizeof(T));
            return std::allocator<T>::allocate(n, hint);
        }

        void deallocate(pointer p, size_type n)
        {
            MemoryStats::MarkDeallocated(sizeof(T));
            return std::allocator<T>::deallocate(p, n);
        }

        StlAllocator() throw() : std::allocator<T>() {}
        StlAllocator(const StlAllocator& allocator) throw() : std::allocator<T>(allocator) {}
        template <typename U>
        StlAllocator(const StlAllocator<U>& x) throw()
        {
            (void)x;
        }
        ~StlAllocator() throw() {}
    };

}

#endif /* _TileShell_Core_Allocator_H__ */