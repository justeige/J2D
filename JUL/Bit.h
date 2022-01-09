#ifndef JUL_BIT_H
#define JUL_BIT_H

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

#include <cstddef>
#include <cstdint>

namespace jul 
{



    // -----------------------------------------------------------
    // Set a bit at a position n.
    // Example:
    // assert(set_bit(0, 0) == 1);
    // assert(set_bit(0, 1) == 2);
    // assert(set_bit(0, 2) == 4);
    // -----------------------------------------------------------
    template <class Integer>
    constexpr Integer set_bit(Integer i, std::size_t position)
    {
        return i | (1 << position);
    }



    // -----------------------------------------------------------
    // Clear a bit at a position n.
    // Example:
    // assert(clear_bit(1, 0) == 0);
    // assert(clear_bit(2, 1) == 0);
    // assert(clear_bit(4, 2) == 0);
    // -----------------------------------------------------------
    template <class Integer>
    constexpr Integer clear_bit(Integer i, std::size_t n)
    {
        return i & ~(1 << n);
    }



    // -----------------------------------------------------------
    // Is bit at position n set?
    // Example:
    // assert(check_bit(0b001, 0)    == true);
    // assert(check_bit(0b010, 1)    == true);
    // assert(check_bit(0b000000, 5) == false);
    // -----------------------------------------------------------
    template <class Integer>
    constexpr bool check_bit(Integer i, std::size_t n)
    {
        return i & (1 << n);
    }



    // -----------------------------------------------------------
    // Toggle a bit at position n.
    // Example:
    // assert(toggle_bit(0b010, 0) == 0b011);
    // assert(toggle_bit(0b010, 1) == 0b000);
    // assert(toggle_bit(0b010, 2) == 0b110);
    // -----------------------------------------------------------
    template <class Integer>
    constexpr Integer toggle_bit(Integer i, std::size_t n)
    {
        return i ^ (1 << n);
    }



    // -----------------------------------------------------------
    // Count the number of set bits with the Brian Kernighans method.
    // Example:
    // assert(count_bits(0b011)   == 2);
    // assert(count_bits(0b11010) == 3);
    // -----------------------------------------------------------
    template <class Integer>
    constexpr Integer count_bits(Integer n)
    {
        Integer cnt = 0;
        while (n) {
            n &= (n - 1);
            cnt++;
        }
        return cnt;
    }



    // -----------------------------------------------------------
    // How many bits are in a number?
    // Example:
    // assert(how_many_bits(std::int16_t{}) == 16);
    // assert(how_many_bits(std::int32_t{}) == 32);
    // assert(how_many_bits(std::int64_t{}) == 64);
    // 
    // assert(how_many_bits(std::uint16_t{}) == 16);
    // assert(how_many_bits(std::uint32_t{}) == 32);
    // assert(how_many_bits(std::uint64_t{}) == 64);
    // -----------------------------------------------------------
    template <class Number>
    constexpr Number how_many_bits(Number n)
    {
        return sizeof(n) * 8;
    }



}

#ifdef JUL_STATIC_TEST

static_assert(jul::set_bit(0, 0) == 1);
static_assert(jul::set_bit(0, 1) == 2);
static_assert(jul::set_bit(0, 2) == 4);

static_assert(jul::clear_bit(1, 0) == 0);
static_assert(jul::clear_bit(2, 1) == 0);
static_assert(jul::clear_bit(4, 2) == 0);

static_assert(jul::check_bit(0b001, 0)    == true);
static_assert(jul::check_bit(0b010, 1)    == true);
static_assert(jul::check_bit(0b000000, 5) == false);

static_assert(jul::toggle_bit(0b010, 0) == 0b011);
static_assert(jul::toggle_bit(0b010, 1) == 0b000);
static_assert(jul::toggle_bit(0b010, 2) == 0b110);

static_assert(jul::count_bits(0b011)   == 2);
static_assert(jul::count_bits(0b11010) == 3);

static_assert(jul::how_many_bits(std::int16_t{}) == 16);
static_assert(jul::how_many_bits(std::int32_t{}) == 32);
static_assert(jul::how_many_bits(std::int64_t{}) == 64);

static_assert(jul::how_many_bits(std::uint16_t{}) == 16);
static_assert(jul::how_many_bits(std::uint32_t{}) == 32);
static_assert(jul::how_many_bits(std::uint64_t{}) == 64);

#endif

#endif // !JUL_BIT_H
