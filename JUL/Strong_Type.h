#ifndef JUL_STRONG_TYPE_H
#define JUL_STRONG_TYPE_H

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



// -------------------------------------------------------------------------------
// Macros to create number-like types and their operators without boilerplate.
// -------------------------------------------------------------------------------

#define jul_declare_strong_type(T, underlying_type) \
struct T {                                                                       \
    explicit T(const underlying_type& v) : value(v) {};                          \
    T() : value() {};                                                            \
    T(const T& other) : value{ other.value } {}                                  \
                                                                                 \
    underlying_type value;                                                       \
                                                                                 \
    T& operator=(const T& other) { value = other.value; return *this; }          \
    T& operator=(const underlying_type& other) { value = other; return *this; }  \
                                                                                 \
    operator underlying_type& () { return value; }                               \
    operator const underlying_type& () const { return value; }                   \
                                                                                 \
    bool operator == (const T& other) const { return value == other.value; }     \
    bool operator != (const T& other) const { return value != other.value; }     \
    bool operator <  (const T& other) const { return value < other.value; }      \
    bool operator >  (const T& other) const { return value > other.value; }      \
}

#define jul_strong_type_op(type, op) type operator op (const type& a, const type& b) { return type{ a.value op b.value }; }
#define jul_strong_type_arithmetic(type) \
    jul_strong_type_op(type, +) \
    jul_strong_type_op(type, -) \
    jul_strong_type_op(type, *) \
    jul_strong_type_op(type, /)


#endif // JUL_STRONG_TYPE_H