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
#ifndef _TileShell_UI_INotifyPropertyChanged_H__
#define _TileShell_UI_INotifyPropertyChanged_H__

#include <tileshell/required.hxx>
#include <tileshell.core/strongname.hxx>

namespace TileShell::UI
{

    ///
    /// @brief
    ///     Declares OnPropertyChanged method.
    ///
    /// @details
    ///     This interface provides support for notifying changes for specified type of properties.
    ///     Instead of using integral or string identifiers, for specifying property name it's using
    ///     strong name functionality.
    ///
    struct INotifyPropertyChanged
    {
        virtual ~INotifyPropertyChanged() { }

        ///
        /// @brief
        ///     Handles property change event.
        ///
        /// @param[in] property_name
        ///     A name of the changed property.
        ///
        /// @returns
        ///     true when successful, false otherwise.
        ///
        virtual bool OnPropertyChanged(const Core::StrongName& property_name) = 0;
    };

}

#endif /* _TileShell_UI_INotifyPropertyChanged_H__ */