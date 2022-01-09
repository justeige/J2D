#ifndef JUL_SORT_H
#define JUL_SORT_H



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



#include <algorithm>
#include <execution>

namespace jul 
{



    // -------------------------------------------------------------------------------
    // Best case:  Almost sorted array.  -> O(n)
    // Worst case: Reverse sorted array. -> O(n²)
    // This algo can outperform std::sort for a large, almost sorted array like container.
    // (Profile your application!!!)
    // -------------------------------------------------------------------------------
    template <class ArrayLike>
    void insertion_sort(ArrayLike& container)
    {
        const auto size = std::size(container);

        for (std::size_t n = 1; n < size; ++n) {
            auto temp = container[n];
            int  m = n - 1;
            while ((m >= 0) && (temp < container[m])) {
                container[m + 1] = container[m];
                m = m - 1;
            }
            container[m + 1] = temp;
        }
    }



    // ----------------------------------------------------------
    // Is a container sorted? Wrapper for std::is_sorted.
    // Example:
    // assert(is_sorted(std::vector<int>{ 0, 1, 2, 3 }));
    // assert(is_sorted(std::set<int>{ 5, 1, 4, 3 }));
    // ----------------------------------------------------------
    template <class Container>
    constexpr bool is_sorted(const Container& c)
    {
        return std::is_sorted(std::execution::par, std::begin(c), std::end(c));
    }



    // ---------------------------------------------------------------------------------
    // Get the index of the last sorted element, return -1 if the container is empty
    // ---------------------------------------------------------------------------------
    template <class Container>
    int last_sorted_index(const Container& c)
    {
        auto sorted_end = std::is_sorted_until(std::begin(c), std::end(c));
        auto distance = std::distance(std::begin(c), sorted_end);
        return distance - 1;
    }



    // ---------------------------------------------------------------------------------
    // Wrapper for std::sort for a complete container.
    // ---------------------------------------------------------------------------------
    template <class Container>
    void sort(Container& c)
    {
        std::sort(std::execution::par, std::begin(c), std::end(c));
    }



    // ---------------------------------------------------------------------------------
    // Wrapper for std::sort for a complete container with a custom predicate.
    // ---------------------------------------------------------------------------------
    template <class Container, class Predicate>
    void sort(Container& c, Predicate&& pred)
    {
        std::sort(std::execution::par, std::begin(c), std::end(c), pred);
    }



    // ---------------------------------------------------------------------------------
    // Wrapper for std::sort for a complete container, returns a copy of the container.
    // ---------------------------------------------------------------------------------
    template <class Container>
    Container sorted(Container c)
    {
        std::sort(std::execution::par, std::begin(c), std::end(c));
        return c;
    }



    // ---------------------------------------------------------------------------------
    // Wrapper for std::sort for a complete container, returns a copy and uses a custom predicate.
    // ---------------------------------------------------------------------------------
    template <class Container, class Predicate>
    Container sorted(Container c, Predicate&& pred)
    {
        std::sort(std::execution::par, std::begin(c), std::end(c), pred);
        return c;
    }
    


    // ---------------------------------
    // Functor for x > y
    // ---------------------------------
    template <class T>
    auto greater_than(const T& value)
    {
        return [value](const T& n) {
            return n > value;
        };
    }



    // ---------------------------------
    // Functor for x < y
    // ---------------------------------
    template <class T>
    auto less_than(const T& value)
    {
        return [value](const T& n) {
            return n < value;
        };
    }



    // ---------------------------------
    // Functor for x == y
    // ---------------------------------
    template <class T>
    auto equal_to(const T& value)
    {
        return [value](const T& n) {
            return n == value;
        };
    }



    // ---------------------------------
    // Functor for x >= y
    // ---------------------------------    
    template <class T>
    auto greater_equal_than(const T& value)
    {
        return [value](const T& n) {
            return n >= value;
        };
    }



    // ---------------------------------
    // Functor for x <= y
    // ---------------------------------
    template <class T>
    auto less_equal_than(const T& value)
    {
        return [value](const T& n) {
            return n <= value;
        };
    }
}

#endif // JUL_SORT_H
