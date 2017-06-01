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

#include <tileshell.ui.controls.primitives/buttonbase.hxx>
#include <tileshell.core/allocator.hxx>

namespace TileShell::UI::Controls
{
    struct MultiButtonItem
    {
        string_t            _text;
        Core::StrongName    _activity;
        int32_t             _id;
    };
    typedef std::vector<MultiButtonItem> MultiButtonItemCollection;

    class MultiButton
        : public Primitives::ButtonBase
        , public Core::Allocator<MultiButton>
    {
        TILESHELL_DECLARE_CONTROLFACTORYMETHOD(MultiButton, "MultiButton");
    protected:
        Drawing::StyleItem9Grid     _styleitem_item_selected;
        Drawing::StyleItem9Grid     _styleitem_item_pushed;
        MultiButtonItemCollection   _items;
        Drawing::Size               _item_size;
        Drawing::Thickness          _item_padding;
        float32_t                   _hover_elevate;
        float32_t                   _hover_elevate_min;
        float32_t                   _hover_elevate_max;
        float32_t                   _hover_elevate_speed;
        float32_t                   _counter;
        size_t                      _hover_item_index;
        Drawing::Color              _hover_item_color;
        Drawing::Color              _hover_item_background_color;
        bool                        _is_shift_down;

    public:
        MultiButton();
        virtual ~MultiButton();

    public:
        virtual Control* GetNextLogicalControl(bool reverse) const override;

        bool CanSelectNext() const;

        bool CanSelectPrev() const;

    public:
        virtual bool GenerateGeometry(Drawing::GeometryBuilder& out_builder,
            GeometryType geometry_type) override;
        virtual bool Deserialize(Xml::XmlNode* node) override;
        virtual bool GetSelectorRectangle(Drawing::Rect& out_result) const override;

    public:
        virtual bool OnKeyDown(const Input::KeyEventArgs& e) override;
        virtual bool OnKeyUp(const Input::KeyEventArgs& e) override;
        virtual bool OnMouseDown(const Input::MouseEventArgs& e) override;
        virtual bool OnMouseUp(const Input::MouseEventArgs& e) override;
        virtual bool OnMouseMove(const Input::MouseEventArgs& e) override;
        virtual bool OnMouseLeave() override;

        virtual bool OnPropertyChanged(const Core::StrongName& property_name) override;
        virtual bool Update(float32_t delta) override;

    public:
        void SelectNextItem();

        void SelectPrevItem();

        void SelectFirstItem();

        void SelectLastItem();

    private:
        bool DoAction();
    };

    inline bool MultiButton::CanSelectNext() const
    {
        return _hover_item_index != (_items.size() - 1);
    }

    inline bool MultiButton::CanSelectPrev() const
    {
        return _hover_item_index != 0;
    }

    inline void MultiButton::SelectNextItem()
    {
        _hover_item_index = (_hover_item_index + 1) % _items.size();
        OnPropertyChanged(Core::StrongName("SelectedItem"));
    }

    inline void MultiButton::SelectPrevItem()
    {
        _hover_item_index = (_hover_item_index + _items.size() - 1) % _items.size();
        OnPropertyChanged(Core::StrongName("SelectedItem"));
    }

    inline void MultiButton::SelectFirstItem()
    {
        _hover_item_index = 0;
        OnPropertyChanged(Core::StrongName("SelectedItem"));
    }

    inline void MultiButton::SelectLastItem()
    {
        _hover_item_index = _items.size() - 1;
        OnPropertyChanged(Core::StrongName("SelectedItem"));
    }

}

namespace TileShell::Serialization
{
    struct MultiButtonItemSerializer
    {
        static bool Deserialize(UI::Controls::MultiButtonItem& out_result, Xml::XmlNode* node)
        {
            if (node == nullptr)
            {
                return false;
            }

            UI::Controls::MultiButtonItem item;

            if (StringValueSerializer::Deserialize(item._text, node->first_attribute("Text")) &&
                StrongNameValueSerializer::Deserialize(item._activity, node->first_attribute("TargetActivity")) &&
                Int32ValueSerializer::Deserialize(item._id, node->first_attribute("Id")))
            {
                out_result = item;

                return true;
            }

            return false;
        }
    };
}

