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

#include <TileShell/UI/Controls/Control.h>
#include <TileShell/Serialization/TypeSerializer.h>

namespace TileShell
{
namespace UI
{
namespace Controls
{
namespace Primitives
{
typedef void*   SelectorItemTag;

struct SelectorItem
{
    string_t            _text;
    int32_t             _id;
    SelectorItemTag     _tag;
};

typedef std::vector<SelectorItem>   SelectorItemCollection;

///
/// @brief
///     Selector base.
///
/// @details
///     This control is base for all
///
class SelectorBase
    : public Control
{
protected:
    bool
    _is_dropdown;   // dropdown selector popups all items, non-dropdown shows only selected item
    bool                        _is_expanded;   // indicates whether dropdown selector is expanded
    Orientation                 _orientation;
    SelectorItemCollection      _items;
    size_t                      _selected_item_index;

public:
    ///
    /// @brief
    ///     Creates instance of the SelectorBase class.
    ///
    SelectorBase();

    ///
    /// @brief
    ///     Destroys instance of the SelectorBase class.
    ///
    virtual ~SelectorBase();

public:
    ///
    /// @brief
    ///     Gets drop down state.
    ///
    bool IsDropDown() const;

    ///
    /// @brief
    ///     Sets drop down state.
    ///
    void SetDropDown(bool value);

    ///
    /// @brief
    ///     Gets orientation.
    ///
    Orientation GetOrientation() const;

    ///
    /// @brief
    ///     Sets orientation.
    ///
    void SetOrientation(Orientation value);

public:
    ///
    /// @brief
    ///     Adds item.
    ///
    /// @param[in] text
    ///     A item text.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool AddItem(const string_t& text);

    ///
    /// @brief
    ///     Adds item.
    ///
    /// @param[in] text
    ///     A item text.
    /// @param[in] id
    ///     A item id.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool AddItem(const string_t& text, int32_t id);

    ///
    /// @brief
    ///     Adds item.
    ///
    /// @param[in] text
    ///     A item text.
    /// @param[in] id
    ///     A item id.
    /// @param[in] tag
    ///     An user specified tag.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool AddItem(const string_t& text, int32_t id, SelectorItemTag tag);

    ///
    /// @brief
    ///     Removes item by index.
    ///
    /// @param[in] index
    ///     An index of element to remove.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool RemoveItemByIndex(size_t index);

    ///
    /// @brief
    ///     Removes item by id.
    ///
    /// @param[in] id
    ///     An id of element to remove.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool RemoveItemById(int32_t id);

    ///
    /// @brief
    ///     Removes item by tag.
    ///
    /// @param[in] id
    ///     A tag of element to remove.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool RemoveItemByTag(SelectorItemTag tag);

    ///
    /// @brief
    ///     Gets item by index.
    ///
    /// @param[out] out_result
    ///     A result item.
    /// @param[in] index
    ///     An index of element to retrieve.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool GetItemByIndex(SelectorItem& out_result, size_t index) const;

    ///
    /// @brief
    ///     Gets item by id.
    ///
    /// @param[out] out_result
    ///     A result item.
    /// @param[in] id
    ///     An id of element to retrieve.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool GetItemById(SelectorItem& out_result, int32_t id) const;

    ///
    /// @brief
    ///     Gets item by tag.
    ///
    /// @param[out] out_result
    ///     A result item.
    /// @param[in] tag
    ///     A tag of element to retrieve.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool GetItemByTag(SelectorItem& out_result, SelectorItemTag tag) const;

    ///
    /// @brief
    ///     Gets index of selected item.
    ///
    /// @returns
    ///     The index of selected item.
    ///
    size_t GetSelectedItemIndex() const;

    ///
    /// @brief
    ///     Gets selected item.
    ///
    /// @param[out] out_result
    ///     A result item.
    ///
    /// @returns
    ///     true when successful, false otherwise.
    ///
    bool GetSelectedItem(SelectorItem& out_result) const;

    ///
    /// @brief
    ///     Gets number of items.
    ///
    size_t GetItemsCount() const;

public:
    virtual bool Deserialize(Xml::XmlNode* node) override;

public:
    ///
    /// @brief
    ///     Expands selector.
    ///
    /// @returns
    ///     true when sucecssful, false otherwise.
    ///
    bool Expand();

    ///
    /// @brief
    ///     Selects next item.
    ///
    void SelectNextItem();

    ///
    /// @brief
    ///     Selects previous item.
    ///
    void SelectPrevItem();

    ///
    /// @brief
    ///     Selects first item.
    ///
    void SelectFirstItem();

    ///
    /// @brief
    ///     Selects last item.
    ///
    void SelectLastItem();

    ///
    /// @brief
    ///     Selects item of specified index.
    ///
    void SelectItem(size_t index);

public:
    virtual bool OnPropertyChanged(const Core::StrongName& property_name) override;

public:
    virtual bool OnItemAdded();
    virtual bool OnItemRemoved();
};
//------------------------------------------------------------------------------------------------//
inline bool SelectorBase::IsDropDown() const
{
    return _is_dropdown;
}
//------------------------------------------------------------------------------------------------//
inline void SelectorBase::SetDropDown(bool value)
{
    _is_dropdown = value;
    OnPropertyChanged(Core::StrongName("IsDropDown"));
}
//------------------------------------------------------------------------------------------------//
inline Orientation SelectorBase::GetOrientation() const
{
    return _orientation;
}
//------------------------------------------------------------------------------------------------//
inline void SelectorBase::SetOrientation(Orientation value)
{
    _orientation = value;
    OnPropertyChanged(Core::StrongName("Orientation"));
}
//------------------------------------------------------------------------------------------------//
inline bool SelectorBase::AddItem(const string_t& text)
{
    return AddItem(text, -1, nullptr);
}
//------------------------------------------------------------------------------------------------//
inline bool SelectorBase::AddItem(const string_t& text, int32_t id)
{
    return AddItem(text, id, nullptr);
}
//------------------------------------------------------------------------------------------------//
inline size_t SelectorBase::GetSelectedItemIndex() const
{
    return _selected_item_index;
}
//------------------------------------------------------------------------------------------------//
inline bool SelectorBase::GetSelectedItem(SelectorItem& out_result) const
{
    return GetItemByIndex(out_result, static_cast<int32_t>(_selected_item_index));
}
//------------------------------------------------------------------------------------------------//
inline size_t SelectorBase::GetItemsCount() const
{
    return _items.size();
}
//------------------------------------------------------------------------------------------------//
inline bool SelectorBase::Expand()
{
    _is_expanded = !_is_expanded;
    OnPropertyChanged(Core::StrongName("IsExpanded"));
}
//------------------------------------------------------------------------------------------------//
inline void SelectorBase::SelectNextItem()
{
    _selected_item_index = (_selected_item_index + 1) % _items.size();

    OnPropertyChanged(Core::StrongName("SelectedItem"));
}
//------------------------------------------------------------------------------------------------//
inline void SelectorBase::SelectPrevItem()
{
    _selected_item_index = (_selected_item_index + _items.size() - 1) % _items.size();

    OnPropertyChanged(Core::StrongName("SelectedItem"));
}
//------------------------------------------------------------------------------------------------//
inline void SelectorBase::SelectFirstItem()
{
    _selected_item_index = 0;
    OnPropertyChanged(Core::StrongName("SelectedItem"));
}
//------------------------------------------------------------------------------------------------//
inline void SelectorBase::SelectLastItem()
{
    _selected_item_index = _items.size() - 1;
    OnPropertyChanged(Core::StrongName("SelectedItem"));
}
//------------------------------------------------------------------------------------------------//
inline void SelectorBase::SelectItem(size_t index)
{
    _selected_item_index = std::min(index, std::min<size_t>(_items.size() - 1, 0));
    OnPropertyChanged(Core::StrongName("SelectedItem"));
}
//------------------------------------------------------------------------------------------------//
}
}
}
namespace Serialization
{
//------------------------------------------------------------------------------------------------//
struct SelectorItemValueSerializer
{
    static bool Deserialize(UI::Controls::Primitives::SelectorItem& out_result,
                            const Xml::XmlNode* node)
    {
        if (node == nullptr)
        {
            return false;
        }

        UI::Controls::Primitives::SelectorItem item;

        if (StringValueSerializer::Deserialize(item._text, node->first_attribute("Text")) &&
            Int32ValueSerializer::Deserialize(item._id, node->first_attribute("Id")))
        {
            item._tag = nullptr;

            out_result = item;

            return true;
        }

        return false;
    }
};
//------------------------------------------------------------------------------------------------//
}
}
