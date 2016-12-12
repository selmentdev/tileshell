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
//------------------------------------------------------------------------------------------------//
#include <TileShell/UI/Controls/Primitives/SelectorBase.h>
#include <TileShell/Core/Allocator.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace UI
{
namespace Controls
{
class SelectBox
    : public Primitives::SelectorBase
    , public Core::Allocator<SelectBox>
{
    TILESHELL_DECLARE_CONTROLFACTORYMETHOD(SelectBox, "SelectBox");
protected:
    Drawing::StyleItem9Grid     _styleitem_background;
    Drawing::StyleItem9Grid     _styleitem_hovered;
    Drawing::StyleItem1Quad     _styleitem_arrow_up_left;
    Drawing::StyleItem1Quad     _styleitem_arrow_up_right;
    Drawing::StyleItem1Quad     _styleitem_arrow_down_left;
    Drawing::StyleItem1Quad     _styleitem_arrow_down_right;
    Drawing::Rect               _rectangle_arrow_left;
    Drawing::Rect               _rectangle_arrow_right;
    bool                        _is_arrow_left_down;
    bool                        _is_arrow_right_down;

public:
    SelectBox();
    virtual ~SelectBox();

public:
    virtual bool GenerateGeometry(Drawing::GeometryBuilder& out_builder,
                                  GeometryType geometry_type) override;

public:
    virtual bool OnPropertyChanged(const Core::StrongName& property_name) override;

    virtual bool OnKeyDown(const Input::KeyEventArgs& e) override;
    virtual bool OnKeyUp(const Input::KeyEventArgs& e) override;
    virtual bool OnMouseDown(const Input::MouseEventArgs& e) override;
    virtual bool OnMouseUp(const Input::MouseEventArgs& e) override;
    virtual bool OnMouseMove(const Input::MouseEventArgs& e) override;
};
}
}
}
//------------------------------------------------------------------------------------------------//