#ifndef JUL_RANDOM_H
#define JUL_RANDOM_H

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


#include <random>
#include <vector>
#include <cassert>
#include <type_traits>

namespace jul {
    // ----------------------------------------------------------------------------------------------
    // The following functions are wrapper for C++ complicated random library.
    // ATTENTION! Those functions aren't really the best practises for using those random functions,
    // but are very usefull for fast prototyping.
    // ----------------------------------------------------------------------------------------------


    // ----------------------------------------------------------------------------
    // Get a random int from a certain range of ints.
    // Example:
    // long value = random_int<long>(0, 10);
    // => value = 5
    // ----------------------------------------------------------------------------
    template <class Integer = int>
    Integer random_int(Integer min, Integer max)
    {
        // static checks:
        static_assert(std::is_integral<Integer>::value, "Type is no integer!");

        // runtime checks:
        assert(min < max);

        static std::random_device rd; // create object for seeding
        static std::mt19937 mt{ rd() }; // create engine and seed it

        std::uniform_int_distribution<> dist{ min, max };
        return dist(mt);
    }



    // ----------------------------------------------------------------------------
    // Get multiple random integers.
    // ----------------------------------------------------------------------------
    template <class Integer = int>
    std::vector<Integer> random_ints(Integer min, Integer max, std::size_t num_of_ints)
    {
        // static checks:
        static_assert(std::is_integral<Integer>::value, "Type is no integer!");

        // runtime checks:
        assert(min < max);
        assert(num_of_ints != 0);

        static std::random_device rd; // create object for seeding
        static std::mt19937 mt{ rd() }; // create engine and seed it

        std::uniform_int_distribution<> dist{ min, max };

        std::vector<Integer> v;
        for (std::size_t n = 0; n < num_of_ints; ++n) {
            v.push_back(dist(mt));
        }
        return v;
    }



    // ----------------------------------------------------------------------------
    // Get a random boolean by percentage.
    // Example:
    // bool maybe_enable = random_bool(0.75);
    // => maybe_enable has a 75% chance to be true
    // ----------------------------------------------------------------------------
    template <class FloatingPoint = double>
    bool random_bool(FloatingPoint percentage_of_true = FloatingPoint{ 0.5 })
    {
        // static checks:
        static_assert(std::is_floating_point<FloatingPoint>::value, "Type is no floating point!");

        static std::random_device rd; // create object for seeding
        static std::mt19937 mt{ rd() }; // create engine and seed it

        std::bernoulli_distribution dist{ percentage_of_true };
        return dist(mt);
    }



    // ----------------------------------------------------------------------------
    // Shuffle a range with an (optional) seed value.
    // ----------------------------------------------------------------------------
    template <class Container>
    void shuffle(Container& c, const unsigned int seed_value = std::default_random_engine::default_seed)
    {
        std::shuffle(std::begin(c), std::end(c), std::default_random_engine{ seed_value });
    }



    // ----------------------------------------------------------------------------
    // Get a shuffled range with an (optional) seed value.
    // ----------------------------------------------------------------------------
    template <class Container>
    Container shuffled(Container c, const unsigned int seed_value = std::default_random_engine::default_seed)
    {
        std::shuffle(std::begin(c), std::end(c), std::default_random_engine{ seed_value });
        return c;
    }
}

#endif // JUL_RANDOM_H
