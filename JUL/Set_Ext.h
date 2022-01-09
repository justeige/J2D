#ifndef JUL_SET_H
#define JUL_SET_H

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


#include <set>
#include <unordered_set>

namespace jul
{
    // ---------------------------------------------------------------------------------
    // Does a set contain a certain value?
    // example:
    // std::set<int> ints = { 0,1,2,3 };
    // bool has_two = contains(ints, 2);
    //
    // => has_two = true
    // ---------------------------------------------------------------------------------
    template <class T>
    bool contains(const std::set<T>& s, const T& value)
    {
        auto last = std::end(s);
        return s.find(value) != last;
    }

    template <class T>
    bool contains(const std::unordered_set<T>& s, const T& value)
    {
        auto last = std::end(s);
        return s.find(value) != last;
    }

}

#endif // JUL_SET_H