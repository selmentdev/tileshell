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
#include <tileshell.ui.controls.primitives/selectorbase.hxx>
#include <tileshell.serialization/typeserializer.hxx>

namespace TileShell::UI::Controls::Primitives
{

    SelectorBase::SelectorBase()
        : Control()
        , _is_dropdown(false)
        , _is_expanded(false)
        , _orientation(Orientation::Horizontal)
        , _items()
        , _selected_item_index(0)
    {
    }

    SelectorBase::~SelectorBase()
    {
    }

    bool SelectorBase::AddItem(const string_t& text, int32_t id, SelectorItemTag tag)
    {
        SelectorItem item;
        item._text = text;
        item._id = id;
        item._tag = tag;

        _items.push_back(item);

        return true;
    }

    bool SelectorBase::RemoveItemByIndex(size_t index)
    {
        if (index < _items.size())
        {
            _items.erase(_items.begin() + index);
            return true;
        }

        return false;
    }

    bool SelectorBase::RemoveItemById(int32_t id)
    {
        for (SelectorItemCollection::iterator it = _items.begin(), end = _items.end();
            it != end;
            ++it)
        {
            if ((*it)._id == id)
            {
                _items.erase(it);

                return true;
            }
        }

        return false;
    }

    bool SelectorBase::RemoveItemByTag(SelectorItemTag tag)
    {
        for (SelectorItemCollection::iterator it = _items.begin(), end = _items.end();
            it != end;
            ++it)
        {
            if ((*it)._tag == tag)
            {
                _items.erase(it);

                return true;
            }
        }

        return false;
    }

    bool SelectorBase::GetItemByIndex(SelectorItem& out_result, size_t index) const
    {
        if (index < _items.size())
        {
            out_result = *(_items.begin() + index);
            return true;
        }

        return false;
    }

    bool SelectorBase::GetItemById(SelectorItem& out_result, int32_t id) const
    {
        for (SelectorItemCollection::const_iterator it = _items.begin(), end = _items.end();
            it != end;
            ++it)
        {
            if ((*it)._id == id)
            {
                out_result = (*it);

                return true;
            }
        }

        return false;
    }

    bool SelectorBase::GetItemByTag(SelectorItem& out_result, SelectorItemTag tag) const
    {
        for (SelectorItemCollection::const_iterator it = _items.begin(), end = _items.end();
            it != end;
            ++it)
        {
            if ((*it)._tag == tag)
            {
                out_result = (*it);

                return true;
            }
        }

        return false;
    }

    bool SelectorBase::Deserialize(Xml::XmlNode* node)
    {
        if (Control::Deserialize(node) == false)
        {
            return false;
        }

        using namespace Serialization;

        Xml::XmlNode* items = node->first_node("Items");

        if (items != nullptr)
        {
            Xml::XmlNode* item = items->first_node("Item");

            while (item != nullptr)
            {
                SelectorItem selector_item;

                if (SelectorItemValueSerializer::Deserialize(selector_item, item))
                {
                    _items.push_back(selector_item);
                    OnItemAdded();
                }

                item = item->next_sibling("Item");
            }
        }

        return true;
    }

    bool SelectorBase::OnPropertyChanged(const Core::StrongName& property_name)
    {
        if (!Control::OnPropertyChanged(property_name))
        {
            return false;
        }

        if (property_name == Core::StrongName("SelectedItem"))
        {
            if (_event_handler != nullptr)
            {
                _event_handler->OnSelectionChanged(this);
            }
        }

        return true;
    }

    bool SelectorBase::OnItemAdded()
    {
        return true;
    }

    bool SelectorBase::OnItemRemoved()
    {
        return true;
    }

}

