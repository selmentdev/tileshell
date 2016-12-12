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
#ifndef _TileShell_MenuKit_ControlFactory_H__
#define _TileShell_MenuKit_ControlFactory_H__
//------------------------------------------------------------------------------------------------//
#include <TileShell/Required.h>
#include <TileShell/Core/StrongName.h>
#include <TileShell/Core/Types.h>
#include <TileShell/Core/Reference.h>
#include <TileShell/Core/Referenced.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace UI
{
namespace Controls
{
class Control;

class ControlFactory
{
public:
    typedef Control* (*CreateInstanceDelegate)();
    typedef std::map<Core::StrongName, CreateInstanceDelegate, std::less<Core::StrongName>, Core::StlAllocator<std::pair<const Core::StrongName, CreateInstanceDelegate>>>
    CreateInstanceDelegateCollection;

private:
    static CreateInstanceDelegateCollection    _cidc;

public:
    static bool Register(const Core::StrongName& tn, CreateInstanceDelegate cid);
    static bool Unregister(const Core::StrongName& tn);

    template <typename T> static bool Register()
    {
        return Register(T::GetTypeName(), T::CreateInstance);
    }

    template <typename T> static bool Unregister()
    {
        return Unregister(T::GetTypeName());
    }

    static Control* CreateInstance(const Core::StrongName& tn);
};

class RegisterControls
{
public:
    RegisterControls();
    ~RegisterControls();
};
}
}
}
//------------------------------------------------------------------------------------------------//
#endif /* _TileShell_MenuKit_ControlFactory_H__ */