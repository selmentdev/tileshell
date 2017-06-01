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

#include <tileshell.ui.controls/progressbar.hxx>
#include <tileshell.ui.controls/activity.hxx>

namespace TileShell::UI::Controls
{

#define TILESHELL_CONTROL_RESOURCE_PROGRESSBAR_STYLEITEM_BACKGROUND     "ProgressBarNormal"
#define TILESHELL_CONTROL_RESOURCE_PROGRESSBAR_STYLEITEM_PROGRESS       "ProgressBarProgress"

    ProgressBar::ProgressBar()
        : Primitives::RangeBase()
    {
        _is_focusable = false;
    }

    ProgressBar::~ProgressBar()
    {
    }

    bool ProgressBar::GenerateGeometry(Drawing::GeometryBuilder& out_builder,
        GeometryType geometry_type)
    {
        if (geometry_type == GeometryType::Static)
        {
            out_builder.DrawStyleItem(
                _global_transform_matrix,
                Drawing::Color(0xFFFFFFFF),
                _global_zorder,
                _rectangle, _padding,
                _styleitem_background);
        }
        else if (geometry_type == GeometryType::Dynamic)
        {
            Drawing::Rect progress = _rectangle;

            if (_orientation == Orientation::Horizontal)
            {
                progress.Width *= GetPercentage();
            }
            else
            {
                float32_t height = progress.Height;
                progress.Height *= GetPercentage();
                progress.Y += (height - progress.Height);
            }

            out_builder.DrawStyleItem(
                _global_transform_matrix,
                Drawing::Color(0xFFFFFFFF),
                _global_zorder + 10.0F,
                progress, _padding,
                _styleitem_progress);
        }

        return true;
    }

    bool ProgressBar::OnPropertyChanged(const Core::StrongName& property_name)
    {
        if (!RangeBase::OnPropertyChanged(property_name))
        {
            return false;
        }

        if (property_name == Core::StrongName("Style"))
        {
            GetStyle()->GetItem(
                _styleitem_background,
                Core::StrongName(TILESHELL_CONTROL_RESOURCE_PROGRESSBAR_STYLEITEM_BACKGROUND));
            GetStyle()->GetItem(
                _styleitem_progress,
                Core::StrongName(TILESHELL_CONTROL_RESOURCE_PROGRESSBAR_STYLEITEM_PROGRESS));
        }

        return true;
    }

}

