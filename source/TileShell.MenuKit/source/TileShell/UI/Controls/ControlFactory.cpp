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
#include <TileShell/UI/Controls/Control.h>
#include <TileShell/UI/Controls/ControlFactory.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace UI
{
namespace Controls
{
//------------------------------------------------------------------------------------------------//
ControlFactory::CreateInstanceDelegateCollection ControlFactory::_cidc;
//------------------------------------------------------------------------------------------------//
bool ControlFactory::Register(const Core::StrongName& tn,
                              ControlFactory::CreateInstanceDelegate cid)
{
    CreateInstanceDelegateCollection::const_iterator it = _cidc.find(tn);

    if (it == _cidc.end())
    {
        _cidc.insert(std::make_pair(tn, cid));

        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------------------//
bool ControlFactory::Unregister(const Core::StrongName& tn)
{
    CreateInstanceDelegateCollection::const_iterator it = _cidc.find(tn);

    if (it != _cidc.end())
    {
        _cidc.erase(it);

        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------------------//
Control* ControlFactory::CreateInstance(const Core::StrongName& tn)
{
    CreateInstanceDelegateCollection::const_iterator it = _cidc.find(tn);

    if (it != _cidc.end())
    {
        CreateInstanceDelegate cid = it->second;
        tileshell_assert(cid != nullptr);

        Control* control = cid();

        if (control != nullptr)
        {
            //control->AddRef();
            return control;
        }
    }

    return nullptr;
}
//------------------------------------------------------------------------------------------------//
}
}
}
//------------------------------------------------------------------------------------------------//