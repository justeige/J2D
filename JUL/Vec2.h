#ifndef JUL_VEC2_H
#define JUL_VEC2_H

/*
MIT License

Copyright(c) 2019 Julian Steigerwald

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


namespace jul
{

    template <class T>
    struct Vec2 {

        T x, y;

        Vec2() : x(T(0)), y(T(0)) {}
        Vec2(const T& value) : x(value), y(value)
        {

        }
        Vec2(const T& x, const T& y) : x(x), y(y) {}

        Vec2& operator += (const Vec2& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vec2& operator -= (const Vec2& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Vec2& operator *= (const T& scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        Vec2& operator /= (const T& scalar)
        {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        Vec2 operator - () const
        {
            return { -x, -y };
        }
    };


    template<class T> Vec2<T> operator + (const Vec2<T>& a, const Vec2<T>& b) { return Vec2<T>{a} += b; }
    template<class T> Vec2<T> operator - (const Vec2<T>& a, const Vec2<T>& b) { return Vec2<T>{a} -= b; }
    template<class T> Vec2<T> operator * (const Vec2<T>& a, const Vec2<T>& b) { return Vec2<T>{a} *= b; }
    template<class T> Vec2<T> operator / (const Vec2<T>& a, const Vec2<T>& b) { return Vec2<T>{a} /= b; }

    template<class T> Vec2<T> operator * (const Vec2<T>& a, const T& scalar) { return Vec2<T>{a} *= scalar; }
    template<class T> Vec2<T> operator * (const T& scalar, const Vec2<T>& a) { return Vec2<T>{a} *= scalar; }
    template<class T> Vec2<T> operator / (const Vec2<T>& a, const T& scalar) { return Vec2<T>{a} /= scalar; }

    template <class T> bool operator == (const Vec2<T>& a, const Vec2<T>& b) { return a.x == b.x && a.y == b.y; }
    template <class T> bool operator != (const Vec2<T>& a, const Vec2<T>& b) { return !(a == b); }


    template <class T>
    double length(const Vec2<T>& vec)
    {
        return sqrt((vec.x * vec.x) + (vec.y * vec.y));
    }

    template <class T>
    double squared_length(const Vec2<T>& vec)
    {
        return (vec.x * vec.x) + (vec.y * vec.y);
    }

    template <class T>
    Vec2<T> normal(const Vec2<T>& vec)
    {
        const auto magn = length(vec);
        return { vec / (T)magn };
    }

    template <class T>
    double dot_product(const Vec2<T>& a, const Vec2<T>& b)
    {
        return a.x * b.x + a.y * b.y;
    }

    template <class T>
    Vec2<T> unit_vector(const Vec2<T>& vec)
    {
        return vec / length(vec);
    }

}

#endif // JUL_VEC2_h