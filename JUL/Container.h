#ifndef JUL_CONTAINER_H
#define JUL_CONTAINER_H



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



#include <vector>
#include <deque>
#include "Vector_Ext.h"
template <class T>
using Vec = std::vector<T>;

template <class T>
using Deq = std::deque<T>;


#include <map>
#include <unordered_map>
#include "Map_Ext.h"
template <class Key, class Value>
using Map = std::map<Key, Value>;

template <class Key, class Value>
using UMap = std::unordered_map<Key, Value>;



#include <set>
#include "Set_Ext.h"
template <class T>
using Set = std::set<T>;



#include <string>
#include "String_Ext.h"
using Str = std::string;



#include <array>
#include "Array_Ext.h"
template <class T, std::size_t Size>
using Arr = std::array<T, Size>;



#endif // !JUL_CONTAINER_H

