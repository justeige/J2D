#ifndef JUL_RING_H
#define JUL_RING_H


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


#include <array>
#include <algorithm>

namespace jul {

    // ---------------------------------------------------------------
    // Ring (class) = static circular buffer
    // Pushes values on top like an array but overwrites values from 
    // the beginning after going over the buffer-size.
    // Allocates an std::array of static size.
    // ---------------------------------------------------------------
    template <class T, std::size_t Size>
    class Ring {
    public:

        static_assert(Size > 0, "A Ring of 0 is not allowed!");

        // member types
        using value_type      = T;
        using size_type       = decltype(Size);
        using difference_type =	std::ptrdiff_t;
        using reference 	  = value_type&;
        using const_reference = const value_type &;
        using pointer 	      = value_type*;
        using const_pointer   = const value_type*;
        using iterator 	      = typename std::array<T, Size>::iterator;

        // constructor
        Ring() {}
        Ring(value_type init) { m_buffer.fill(init); }
        Ring(const std::array<T, Size>& arr) : m_buffer{ arr } {}

        // operator
        reference  operator[](size_type index)       { return m_buffer[index]; }
        value_type operator[](size_type index) const { return m_buffer[index]; }

        value_type current() const { return m_buffer[m_index]; }

        // push a value at the current index;
        // true:  next value will overwrite an old value / index went over limit
        // false: next value will still be appended.
        bool push(const_reference value)
        {
            m_buffer[m_index] = value;

            // has to overwrite from the beginning?
            if (m_index + 1 >= Size) {
                m_index = 0;
                return true;
            }
            
            // just append to buffer
            m_index++;
            return false;
        }

        // does the Ring container that value?
        bool contains(const_reference value)
        {
            for (auto v : m_buffer) {
                if (v == value) return true;
            }
            return false;
        }

        // getter for the member variables
        constexpr size_type size() const { return Size; }
        size_type index() const { return m_index; }

        // iterators
        auto begin()       { return std::begin(m_buffer);  }
        auto end()         { return std::end(m_buffer);    }
        auto begin() const { return std::begin(m_buffer);  }
        auto end()   const { return std::end(m_buffer);    }
        auto cbegin()      { return std::cbegin(m_buffer); }
        auto cend()        { return std::cend(m_buffer);   }
        auto rbegin()      { return std::rbegin(m_buffer); }
        auto rend()        { return std::rend(m_buffer);   }


        template <class Function>
        void apply_each(Function&& fn)
        {
            std::transform(std::begin(m_buffer), std::end(m_buffer), std::begin(m_buffer), fn);
        }

    private:
        std::array<T, Size> m_buffer = {};
        size_type           m_index  = 0;
    };

    // ----------------
    // Free functions 
    // ----------------
    
    // ----------------------------------------------------------------
    // Create a ring: 
    // Ring<int, 3> ring = make_ring<int>(1,2,3);
    // or
    // auto ring = make_ring<int>(1,2,3);
    // ----------------------------------------------------------------
    template <class T, class ... Params>
    auto make_ring(Params&& ... params)
    {
        constexpr std::size_t Size = sizeof...(Params);
        return jul::Ring<T, Size> { { std::forward<Params>(params)... }};
    }

    template <class T, std::size_t Size>
    bool contains(const Ring<T, Size>& ring, const T& value)
    {
        return ring.conains(value);
    }

    template <class T, std::size_t SizeA, std::size_t SizeB>
    Ring<T, SizeA + SizeB> operator + (const Ring<T, SizeA>& a, const Ring<T, SizeB>& b)
    {
        Ring<T, SizeA + SizeB> combined;
        std::copy(std::begin(a), std::end(a), std::begin(combined));
        std::copy(std::begin(b), std::end(b), std::begin(combined) + std::size(a));
        return combined;
    }
}

#endif // JUL_RING_H