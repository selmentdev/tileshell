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
#include <TileShell/UI/Controls/Control.h>
#include <TileShell/Serialization/TypeSerializer.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace UI
{
namespace Controls
{
namespace Primitives
{

///
/// @brief
///     Text control base.
///
class TextBase
    : public Control
{
protected:
    string_t            _text;
    bool                _is_readonly;
    bool                _is_editable;
    Drawing::TextAlign  _text_align;

public:
    ///
    /// @brief
    ///     Creates instance of the TextBase class.
    ///
    TextBase();

    ///
    /// @brief
    ///     Destroys instance of the TextBase class.
    ///
    virtual ~TextBase();

public:
    virtual bool Deserialize(Xml::XmlNode* node) override;

public:
    ///
    /// @brief
    ///     Gets text.
    ///
    const string_t& GetText() const;

    ///
    /// @brief
    ///     Sets text.
    ///
    void SetText(const string_t& value);

    ///
    /// @brief
    ///     Gets readonly state.
    ///
    bool IsReadonly() const;

    ///
    /// @brief
    ///     Sets readonly state.
    ///
    void SetReadonly(bool value);

    ///
    /// @brief
    ///     Gets editable state.
    ///
    bool IsEditable() const;

    ///
    /// @brief
    ///     Sets editable state.
    ///
    void SetEditable(bool value);

    ///
    /// @brief
    ///     Gets text align.
    ///
    Drawing::TextAlign GetTextAlign() const;

    ///
    /// @brief
    ///     Sets text align.
    ///
    void SetTextAlign(Drawing::TextAlign value);
};
//------------------------------------------------------------------------------------------------//
inline const string_t& TextBase::GetText() const
{
    return _text;
}
//------------------------------------------------------------------------------------------------//
inline void TextBase::SetText(const string_t& value)
{
    _text = value;
    OnPropertyChanged(Core::StrongName("Text"));
}
//------------------------------------------------------------------------------------------------//
inline bool TextBase::IsReadonly() const
{
    return _is_readonly;
}
//------------------------------------------------------------------------------------------------//
inline void TextBase::SetReadonly(bool value)
{
    _is_readonly = value;
    OnPropertyChanged(Core::StrongName("IsReadonly"));
}
//------------------------------------------------------------------------------------------------//
inline bool TextBase::IsEditable() const
{
    return _is_editable;
}
//------------------------------------------------------------------------------------------------//
inline void TextBase::SetEditable(bool value)
{
    _is_editable = value;
    OnPropertyChanged(Core::StrongName("IsEditable"));
}
//------------------------------------------------------------------------------------------------//
inline Drawing::TextAlign TextBase::GetTextAlign() const
{
    return _text_align;
}
//------------------------------------------------------------------------------------------------//
inline void TextBase::SetTextAlign(Drawing::TextAlign value)
{
    _text_align = value;
    OnPropertyChanged(Core::StrongName("TextAlign"));
}
//------------------------------------------------------------------------------------------------//
}
}
}
}
//------------------------------------------------------------------------------------------------//