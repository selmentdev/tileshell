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
#ifndef _TileShell_Animation_Tween_H__
#define _TileShell_Animation_Tween_H__
//------------------------------------------------------------------------------------------------//
#include <TileShell/Required.h>
#include <TileShell/Drawing/Rect.h>
#include <TileShell/Drawing/Vector.h>
#include <TileShell/Drawing/Size.h>
#include <TileShell/Drawing/Point.h>
#include <TileShell/Drawing/Thickness.h>
//------------------------------------------------------------------------------------------------//
namespace TileShell
{
namespace Animation
{
template <typename T>
inline void Lerp(T& out_result, const T& value1, const T& value2, float32_t t)
{
    out_result = value1 + (value2 - value1) * t;
}

template <>
inline void Lerp<float32x2_t>(
    float32x2_t& out_result, const float32x2_t& value1, const float32x2_t& value2, float32_t t)
{
    Lerp(out_result.X, value1.X, value2.X, t);
    Lerp(out_result.Y, value1.Y, value2.Y, t);
}

template <>
inline void Lerp<float32x3_t>(
    float32x3_t& out_result, const float32x3_t& value1, const float32x3_t& value2, float32_t t)
{
    Lerp(out_result.X, value1.X, value2.X, t);
    Lerp(out_result.Y, value1.Y, value2.Y, t);
    Lerp(out_result.Z, value1.Z, value2.Z, t);
}

template <>
inline void Lerp<float32x4_t>(
    float32x4_t& out_result, const float32x4_t& value1, const float32x4_t& value2, float32_t t)
{
    Lerp(out_result.X, value1.X, value2.X, t);
    Lerp(out_result.Y, value1.Y, value2.Y, t);
    Lerp(out_result.Z, value1.Z, value2.Z, t);
    Lerp(out_result.W, value1.W, value2.W, t);
}

template<>
inline void Lerp<Drawing::Point>(
    Drawing::Point& out_result, const Drawing::Point& value1, const Drawing::Point& value2, float32_t t)
{
    Lerp(out_result.X, value1.X, value2.X, t);
    Lerp(out_result.Y, value1.Y, value2.Y, t);
}

template<>
inline void Lerp<Drawing::Size>(
    Drawing::Size& out_result, const Drawing::Size& value1, const Drawing::Size& value2, float32_t t)
{
    Lerp(out_result.Width, value1.Width, value2.Width, t),
         Lerp(out_result.Height, value1.Height, value2.Height, t);
}

template<>
inline void Lerp<Drawing::Rect>(
    Drawing::Rect& out_result, const Drawing::Rect& value1, const Drawing::Rect& value2, float32_t t)
{
    Lerp(out_result.X, value1.X, value2.X, t);
    Lerp(out_result.Y, value1.Y, value2.Y, t);
    Lerp(out_result.Width, value1.Width, value2.Width, t);
    Lerp(out_result.Height, value1.Height, value2.Height, t);
}

template<>
inline void Lerp<Drawing::Thickness>(
    Drawing::Thickness& out_result, const Drawing::Thickness& value1, const Drawing::Thickness& value2,
    float32_t t)
{
    Lerp(out_result.Left, value1.Left, value2.Left, t);
    Lerp(out_result.Top, value1.Top, value2.Top, t);
    Lerp(out_result.Right, value1.Right, value2.Right, t);
    Lerp(out_result.Bottom, value1.Bottom, value2.Bottom, t);
}

template <typename T>
inline void Bezier3(T& out_result, const T& value1, const T& value2, const T& value3, float32_t t)
{
    float32_t a2 = t * t;
    float32_t a1 = 1.0F - t;
    float32_t a12 = a1 * a1;

    out_result = value1 * a12 + 2.0F * value2 * a1 + value3 * a2;
}

template <>
inline void Bezier3<float32x2_t>(
    float32x2_t& out_result, const float32x2_t& value1, const float32x2_t& value2,
    const float32x2_t& value3, float32_t t)
{
    Bezier3(out_result.X, value1.X, value2.X, value3.X, t);
    Bezier3(out_result.Y, value1.Y, value2.Y, value3.Y, t);
}

template <>
inline void Bezier3<float32x3_t>(
    float32x3_t& out_result, const float32x3_t& value1, const float32x3_t& value2,
    const float32x3_t& value3, float32_t t)
{
    Bezier3(out_result.X, value1.X, value2.X, value3.X, t);
    Bezier3(out_result.Y, value1.Y, value2.Y, value3.Y, t);
    Bezier3(out_result.Z, value1.Z, value2.Z, value3.Z, t);
}

template <>
inline void Bezier3<float32x4_t>(
    float32x4_t& out_result, const float32x4_t& value1, const float32x4_t& value2,
    const float32x4_t& value3, float32_t t)
{
    Bezier3(out_result.X, value1.X, value2.X, value3.X, t);
    Bezier3(out_result.Y, value1.Y, value2.Y, value3.Y, t);
    Bezier3(out_result.Z, value1.Z, value2.Z, value3.Z, t);
    Bezier3(out_result.W, value1.W, value2.W, value3.W, t);
}

template<>
inline void Bezier3<Drawing::Point>(
    Drawing::Point& out_result, const Drawing::Point& value1, const Drawing::Point& value2,
    const Drawing::Point& value3, float32_t t)
{
    Bezier3(out_result.X, value1.X, value2.X, value3.X, t);
    Bezier3(out_result.Y, value1.Y, value2.Y, value3.Y, t);
}

template<>
inline void Bezier3<Drawing::Size>(
    Drawing::Size& out_result, const Drawing::Size& value1, const Drawing::Size& value2,
    const Drawing::Size& value3, float32_t t)
{
    Bezier3(out_result.Width, value1.Width, value2.Width, value3.Width, t),
            Bezier3(out_result.Height, value1.Height, value2.Height, value3.Height, t);
}

template<>
inline void Bezier3<Drawing::Rect>(
    Drawing::Rect& out_result, const Drawing::Rect& value1, const Drawing::Rect& value2,
    const Drawing::Rect& value3, float32_t t)
{
    Bezier3(out_result.X, value1.X, value2.X, value3.X, t);
    Bezier3(out_result.Y, value1.Y, value2.Y, value3.Y, t);
    Bezier3(out_result.Width, value1.Width, value2.Width, value3.Width, t);
    Bezier3(out_result.Height, value1.Height, value2.Height, value3.Height, t);
}

template<>
inline void Bezier3<Drawing::Thickness>(
    Drawing::Thickness& out_result, const Drawing::Thickness& value1, const Drawing::Thickness& value2,
    const Drawing::Thickness& value3, float32_t t)
{
    Bezier3(out_result.Left, value1.Left, value2.Left, value3.Left, t);
    Bezier3(out_result.Top, value1.Top, value2.Top, value3.Top, t);
    Bezier3(out_result.Right, value1.Right, value2.Right, value3.Right, t);
    Bezier3(out_result.Bottom, value1.Bottom, value2.Bottom, value3.Bottom, t);
}


///
/// Key frame.
///
/// @tparam T
///     A type of the animated value.
///
template <typename T>
struct KeyFrame
{
    ///
    /// Tween key time.
    ///
    float32_t KeyTime;

    ///
    /// Key frame value.
    ///
    T Value;
};

///
/// Two point linear tween.
///
/// @tparam T
///     A type of the animated value.
///
template <typename T>
struct TweenLerp2
{
    ///
    /// Tween frames.
    ///
    KeyFrame<T> Frames[2];

    ///
    /// Current tween time.
    ///
    float32_t Time;

    ///
    /// Creates instance of TweenLerp2 struct.
    ///
    TweenLerp2()
        : Time(0.0F)
    {
    }

    ///
    /// Resets tween.
    ///
    void Reset()
    {
        Time = Frames[0].KeyTime;
    }

    ///
    /// Increments tween time.
    ///
    void Increment(float32_t value)
    {
        Time += value;
    }

    ///
    /// Gets value indicating whether tween is ended.
    ///
    bool IsEnd() const
    {
        return Time > Frames[1].KeyTime;
    }

    ///
    /// Evaluates tween value at current time.
    ///
    void Evaluate(T& out_result) const
    {
        Lerp(out_result, Frames[0].Value, Frames[1].Value, Time / (Frames[1].KeyTime - Frames[0].KeyTime));
    }
};

///
/// Three point linear tween.
///
/// @tparam T
///     A type of the animated value.
///
template <typename T>
struct TweenLerp3
{
    ///
    /// Tween frames.
    ///
    KeyFrame<T> Frames[3];

    ///
    /// Current tween time.
    ///
    float32_t Time;

    ///
    /// Creates instance of TweenLerp3 struct.
    ///
    TweenLerp3()
        : Time(0.0F)
    {
    }

    ///
    /// Resets tween.
    ///
    void Reset()
    {
        Time = Frames[0].KeyTime;
    }

    ///
    /// Gets value indicating whether tween is ended.
    ///
    bool IsEnd() const
    {
        return Time > Frames[2].KeyTime;
    }

    ///
    /// Increments tween time.
    ///
    void Increment(float32_t value)
    {
        Time += value;
    }

    ///
    /// Evaluates tween value at current time.
    ///
    void Evaluate(T& out_result) const
    {
        if (Time < Frames[1].KeyTime)
        {
            Lerp(out_result, Frames[0].Value, Frames[1].Value, Time / (Frames[1].KeyTime - Frames[0].KeyTime));
        }
        else
        {
            Lerp(out_result, Frames[1].Value, Frames[2].Value,
                 (Time - Frames[1].KeyTime) / (Frames[2].KeyTime - Frames[1].KeyTime));
        }
    }
};

///
/// Four point linear tween.
///
/// @tparam T
///     A type of the animated value.
///
template <typename T>
struct TweenLerp4
{
    ///
    /// Tween frames.
    ///
    KeyFrame<T> Frames[4];

    ///
    /// Current tween time.
    ///
    float32_t Time;

    ///
    /// Creates instance of TweenLerp4 struct.
    ///
    TweenLerp4()
        : Time(0.0F)
    {
    }

    ///
    /// Resets tween.
    ///
    void Reset()
    {
        Time = Frames[0].KeyTime;
    }

    ///
    /// Gets value indicating whether tween is ended.
    ///
    bool IsEnd() const
    {
        return Time > Frames[3].KeyTime;
    }

    ///
    /// Increments tween time.
    ///
    void Increment(float32_t value)
    {
        Time += value;
    }

    void Evaluate(T& out_result) const
    {
        if (Time < Frames[1].KeyTime)
        {
            Lerp(out_result, Frames[0].Value, Frames[1].Value, Time / (Frames[1].KeyTime - Frames[0].KeyTime));
        }
        else if (Time < Frames[2].KeyTime)
        {
            Lerp(out_result, Frames[1].Value, Frames[2].Value,
                 (Time - Frames[1].KeyTime) / (Frames[2].KeyTime - Frames[1].KeyTime));
        }
        else
        {
            Lerp(out_result, Frames[2].Value, Frames[3].Value,
                 (Time - Frames[2].KeyTime) / (Frames[3].KeyTime - Frames[2].KeyTime));
        }
    }
};

///
/// Three point bezier tween.
///
/// @tparam T
///     A type of the animated value.
///
template <typename T>
struct TweenBezier3
{
    ///
    /// Tween frames.
    ///
    KeyFrame<T> Frames[3];

    ///
    /// Current tween time.
    ///
    float32_t Time;

    ///
    /// Creates instance of TweenBezier3 struct.
    ///
    TweenBezier3()
        : Time(0.0F)
    {
    }

    ///
    /// Resets tween.
    ///
    void Reset()
    {
        Time = Frames[0].KeyTime;
    }

    ///
    /// Increments tween time.
    ///
    void Increment(float32_t value)
    {
        Time += value;
    }

    ///
    /// Evaluates tween value at current time.
    ///
    void Evaulate(T& out_result) const
    {
        Bezier3(out_result, Frames[0], Frames[1], Frames[2], Time);
    }

    ///
    /// Gets value indicating whether tween is ended.
    ///
    bool IsEnd() const
    {
        return Time > Frames[2].KeyTime;
    }
};
}
}
//------------------------------------------------------------------------------------------------//
#endif /* _TileShell_Animation_Tween_H__ */