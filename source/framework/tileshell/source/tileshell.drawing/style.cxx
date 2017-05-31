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
#include <tileshell.drawing/style.hxx>
#include <tileshell.drawing/stylemanager.hxx>
#include <tileshell.drawing/texturemanager.hxx>
#include <tileshell.drawing/fontmanager.hxx>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Drawing
{
//------------------------------------------------------------------------------------------------//
Style::Style()
    : _style_texture()
    , _style_9grid_collection()
    , _style_1quad_collection()
{

}
//------------------------------------------------------------------------------------------------//
Style::~Style()
{
}
//------------------------------------------------------------------------------------------------//
bool Style::Deserialize(Xml::XmlNode* node)
{
    Xml::XmlAttribute* attr_texture = node->first_attribute("Texture");
    Xml::XmlAttribute* attr_font = node->first_attribute("Font");

    if ((attr_texture == nullptr) || (attr_font == nullptr))
    {
        return false;
    }

    _style_texture = TextureManager::GetTexture(attr_texture->value());
    _style_font = FontManager::GetFont(attr_font->value());

    node = node->first_node();

    while (node != nullptr)
    {
        if (node->name_size() == 14)
        {
            if (std::strncmp(node->name(), "StyleItem1Quad", 14) == 0)
            {
                Drawing::StyleItem1Quad item;

                if (Serialization::StyleItem1QuadValueSerializer::Deserialize(item, node) == false)
                {
                    return false;
                }

                Xml::XmlAttribute* attr_name = node->first_attribute("Name");
                _style_1quad_collection.insert(std::make_pair(Core::StrongName::Create(attr_name->value()), item));
            }
            else if (std::strncmp(node->name(), "StyleItem9Grid", 14) == 0)
            {
                Drawing::StyleItem9Grid item;

                if (Serialization::StyleItem9GridValueSerializer::Deserialize(item, node) == false)
                {
                    return false;
                }

                Xml::XmlAttribute* attr_name = node->first_attribute("Name");
                _style_9grid_collection.insert(std::make_pair(Core::StrongName::Create(attr_name->value()), item));
            }
        }

        node = node->next_sibling();
    }

    return true;
}
//------------------------------------------------------------------------------------------------//
bool Style::Load(const string_t& name)
{
    Xml::XmlFile file(name.c_str());
    Xml::XmlDocument doc;
    doc.parse<0>(file.data());

    if (Deserialize(doc.first_node("Style")) != false)
    {
        // Because we use 0.0..1.0 texture coordinates, we must normalize them.

        Size texture_size = _style_texture->GetSize();
        texture_size.Width  = 1.0F / texture_size.Width;
        texture_size.Height = 1.0F / texture_size.Height;

        for (StyleItem9GridCollection::iterator it = _style_9grid_collection.begin();
             it != _style_9grid_collection.end();
             ++it)
        {
            it->second.Padding.Scale(texture_size);
            it->second.Rectangle.Scale(texture_size);
        }

        for (StyleItem1QuadCollection::iterator it = _style_1quad_collection.begin();
             it != _style_1quad_collection.end();
             ++it)
        {
            it->second.Rectangle.Scale(texture_size);
        }

        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------------------//
bool Style::GetItem(StyleItem1Quad& out_result, const Core::StrongName& name) const
{
    StyleItem1QuadCollection::const_iterator it = _style_1quad_collection.find(name);

    if (it != _style_1quad_collection.end())
    {
        out_result = it->second;

        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------------------//
bool Style::GetItem(StyleItem9Grid& out_result, const Core::StrongName& name) const
{
    StyleItem9GridCollection::const_iterator it = _style_9grid_collection.find(name);

    if (it != _style_9grid_collection.end())
    {
        out_result = it->second;

        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------------------//
}
}
//------------------------------------------------------------------------------------------------//