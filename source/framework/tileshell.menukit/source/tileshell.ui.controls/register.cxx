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
#include <tileshell.ui.controls/controlfactory.hxx>
#include <tileshell.ui.controls/button.hxx>
#include <tileshell.ui.controls/textblock.hxx>
#include <tileshell.ui.controls/progressbar.hxx>
#include <tileshell.ui.controls/checkbox.hxx>
#include <tileshell.ui.controls/selectbox.hxx>
#include <tileshell.ui.controls/combobox.hxx>
#include <tileshell.ui.controls/multibutton.hxx>
#include <tileshell.ui.controls/slider.hxx>
#include <tileshell.ui.controls/textbox.hxx>

namespace TileShell::UI::Controls
{

    RegisterControls::RegisterControls()
    {
        ControlFactory::Register<Button>();
        ControlFactory::Register<ProgressBar>();
        ControlFactory::Register<TextBlock>();
        ControlFactory::Register<CheckBox>();
        ControlFactory::Register<SelectBox>();
        ControlFactory::Register<ComboBox>();
        ControlFactory::Register<MultiButton>();
        ControlFactory::Register<Slider>();
        ControlFactory::Register<TextBox>();
    }

    RegisterControls::~RegisterControls()
    {
        ControlFactory::Unregister<TextBox>();
        ControlFactory::Unregister<Slider>();
        ControlFactory::Unregister<MultiButton>();
        ControlFactory::Unregister<ComboBox>();
        ControlFactory::Unregister<SelectBox>();
        ControlFactory::Unregister<CheckBox>();
        ControlFactory::Unregister<TextBlock>();
        ControlFactory::Unregister<ProgressBar>();
        ControlFactory::Unregister<Button>();
    }

}

