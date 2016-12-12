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
#include <TileShell/Drawing/Geometry.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Drawing
{
//------------------------------------------------------------------------------------------------//
Geometry::Geometry()
    : _vertex_array()
    , _primitive_type(PrimitiveType_LineList)
{
}
//------------------------------------------------------------------------------------------------//
Geometry::~Geometry()
{
}
//------------------------------------------------------------------------------------------------//
void Geometry::Resize(size_t size)
{
    _vertex_array.resize(size);
}
//------------------------------------------------------------------------------------------------//
void Geometry::Clear()
{
    _vertex_array.clear();
}
//------------------------------------------------------------------------------------------------//
Vertex& Geometry::operator [] (size_t index)
{
    return _vertex_array[index];
}
//------------------------------------------------------------------------------------------------//
const Vertex& Geometry::operator [] (size_t index) const
{
    return _vertex_array[index];
}
//------------------------------------------------------------------------------------------------//
void Geometry::Append(const Vertex& value)
{
    _vertex_array.push_back(value);
}
//------------------------------------------------------------------------------------------------//
PrimitiveType Geometry::GetPrimitiveType() const
{
    return _primitive_type;
}
//------------------------------------------------------------------------------------------------//
void Geometry::SetPrimitiveType(PrimitiveType value)
{
    _primitive_type = value;
}
//------------------------------------------------------------------------------------------------//
Vertex* Geometry::GetData()
{
    return _vertex_array.data();
}
//------------------------------------------------------------------------------------------------//
const Vertex* Geometry::GetData() const
{
    return _vertex_array.data();
}
//------------------------------------------------------------------------------------------------//
}
}
//------------------------------------------------------------------------------------------------//