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
#ifndef _TileShell_Required_H__
#define _TileShell_Required_H__
//------------------------------------------------------------------------------------------------//
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
//------------------------------------------------------------------------------------------------//
#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include <cassert>
#include <cstring>
#include <cmath>
#include <cstdint>
#include <map>
#include <crtdbg.h>
//------------------------------------------------------------------------------------------------//
// Disable certain sets of warning on Visual Studio
#pragma warning(disable : 4324)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)
#pragma warning(disable : 4201)
#pragma warning(disable : 4127)
//------------------------------------------------------------------------------------------------//
typedef float float32_t;
//------------------------------------------------------------------------------------------------//
#ifdef _DEBUG
#   define TILESHELL_DEBUG
#endif
//------------------------------------------------------------------------------------------------//
#define TILESHELL_ALIGN(Bytes)                  __declspec(align(Bytes))
#define TILESHELL_MATHALIGN                     TILESHELL_ALIGN(16)

#define tileshell_assert assert
#define tileshell_unused(_Expression)           ((void)(_Expression))
//------------------------------------------------------------------------------------------------//
#include <TileShell/Core/Types.h>
//------------------------------------------------------------------------------------------------//
#endif /* _TileShell_Required_H__ */