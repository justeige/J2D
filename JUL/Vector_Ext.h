#ifndef JUL_VECTOR_EXT_H
#define JUL_VECTOR_EXT_H

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
#include <algorithm>
#include <cassert>
#include <numeric>


namespace jul {
    // ---------------------------------------------------------------------------------
    // Flatten a vector of vectors.
    // Example:
    // std::vector<int> a{ 1,2,3 }, b{ 4,5,6 };
    // std::vector<std::vector<int>> vec_vec { a, b };
    //
    // auto flattened = jul::flatten(vec_vec);
    // => flattened = { 1, 2, 3, 4, 5, 6 }
    // ---------------------------------------------------------------------------------
    template <typename T>
    std::vector<T> flatten(const std::vector<std::vector<T>>& v)
    {
        auto total_size = 0U;
        for (const auto& sub : v) {
            total_size += sub.size();
        }

        std::vector<T> result;
        result.reserve(total_size);
        for (const auto& sub : v) {
            result.insert(std::end(result), std::begin(sub), std::end(sub));
        }
        return result;
    }


    // ---------------------------------------------------------------------------------
    // Does a vector contain a certain value?
    // example:
    // std::vector<int> ints = { 0,1,2,3 };
    // bool has_two = contains(ints, 2);
    //
    // => has_two = true
    // ---------------------------------------------------------------------------------
    template <class T>
    bool contains(const std::vector<T>& v, const T& value)
    {
        auto first = std::begin(v);
        auto last = std::end(v);
        return std::find(first, last, value) != last;
    }



    // ---------------------------------------------------------------------------------
    // Removes all values from a vector.
    // example:
    // std::vector<int> ints = { 0,1,0,3 };
    // remove_all(ints, 0);
    //
    // => ints = {1,3}
    // ---------------------------------------------------------------------------------
    template <class T>
    void remove_all(std::vector<T>& v, T value)
    {
        v.erase(std::remove(std::begin(v), std::end(v), value), std::end(v));
    }



    // ---------------------------------------------------------------------------------
    // Removes all values from a vector and returns a copy.
    // example:
    // std::vector<int> ints = { 0,1,0,3 };
    // auto without_zero = removed_all(ints, 0);
    //
    // => without_zero = {1,3}
    // ---------------------------------------------------------------------------------
    template <class T>
    std::vector<T> removed_all(std::vector<T> v, T value)
    {
        v.erase(std::remove(std::begin(v), std::end(v), value), std::end(v));
        return v;
    }



    // ---------------------------------------------------------------------------------
    // Wrapper for std::transform for a complete vector.
    // ---------------------------------------------------------------------------------
    template <class T, class Function>
    void apply_each(std::vector<T>& v, Function&& fn)
    {
        std::transform(std::begin(v), std::end(v), std::begin(v), fn);
    }



    // ---------------------------------------------------------------------------------
    // Returns the max value of the vector.
    // Precondition: vector can't be empty!
    // ---------------------------------------------------------------------------------
    template <class T>
    T max_value(const std::vector<T>& v)
    {
        assert(std::size(v) != 0);
        return *std::max_element(std::begin(v), std::end(v));
    }



    // ---------------------------------------------------------------------------------
    // Returns the max value of the vector with a custom compare function.
    // Precondition: vector can't be empty!
    // ---------------------------------------------------------------------------------
    template <class T, class Compare>
    T max_value(const std::vector<T>& v, Compare&& comp)
    {
        assert(std::size(v) != 0);
        return *std::max_element(std::begin(v), std::end(v), comp);
    }



    // ---------------------------------------------------------------------------------
    // Returns the min value of the vector.
    // Precondition: vector can't be empty!
    // ---------------------------------------------------------------------------------
    template <class T>
    T min_value(const std::vector<T>& v)
    {
        assert(std::size(v) != 0);
        return *std::min_element(std::begin(v), std::end(v));
    }



    // ---------------------------------------------------------------------------------
    // Returns the int value of the vector with a custom compare function.
    // Precondition: vector can't be empty!
    // ---------------------------------------------------------------------------------
    template <class T, class Compare>
    T min_value(const std::vector<T>& v, Compare&& comp)
    {
        assert(std::size(v) != 0);
        return *std::min_element(std::begin(v), std::end(v), comp);
    }



    // ---------------------------------------------------------------------------------
    // Get a copy of all elements within limits.
    // Example:
    // std::vector<int> ints = { 0,1,0,3 };
    // auto limited = within_limits(ints, 0, 1);
    //
    // => limited = {0,1,0}
    // ---------------------------------------------------------------------------------
    template <class T>
    std::vector<T> within_limits(std::vector<T> values, T min, T max)
    {
        auto filter = [=](T value) {return value < min || value > max;};
        values.erase(std::remove_if(std::begin(values), std::end(values), filter), std::end(values));
        return values;
    }



    // ---------------------------------------------------------------------------------
    // Get a copy of all elements outside limits.
    // Example:
    // std::vector<int> ints = { 0,1,0,3 };
    // auto outside = out_of_limits(ints, 0, 1);
    //
    // => outside = {3}
    // ---------------------------------------------------------------------------------
    template <class T>
    std::vector<T> out_of_limits(std::vector<T> values, T min, T max)
    {
        auto filter = [=](T value) {return value >= min && value <= max;};
        values.erase(std::remove_if(std::begin(values), std::end(values), filter), std::end(values));
        return values;
    }



    // ---------------------------------------------------------------------------------
    // Creates a empty std::vector<T> with a reserved size.
    // Example:
    // auto vec = jul::make_vector(10);
    // vec.capacity() == 10
    // ---------------------------------------------------------------------------------
    template <class T>
    constexpr std::vector<T> make_vector(std::size_t capacity)
    {
        std::vector<T> range{};
        range.reserve(capacity);
        return range;
    }



    // ---------------------------------------------------------------------------------
    // Creates a std::vector<T> filled with (ascending) values.
    // Example:
    // auto vec = jul::make_vector(-3, 3);
    // vec == { -3, -2, -1, 0, 1, 2, 3 }
    // ---------------------------------------------------------------------------------
    template <class T>
    constexpr std::vector<T> make_vector(const T& start_value, const T& end_value)
    {
        auto size = (end_value  - start_value) + 1; // including the right border!
        assert(size >= 0 && "Invalid range!");

        std::vector<T> range(size);
        std::iota(std::begin(range), std::end(range), start_value);
        return range;
    }



    // ---------------------------------------------------------------------------------
    // Creates a std::vector<T> filled with (descending) values.
    // Example:
    // auto vec = jul::make_rvector(0, 4);
    // vec == { 4, 3, 2, 1, 0 }
    // ---------------------------------------------------------------------------------
    template <class T>
    constexpr std::vector<T> make_rvector(const T& end_value, const T& start_value)
    {
        auto size = (end_value - start_value) + 1; // including the right border!
        assert(size >= 0 && "Invalid range!");

        std::vector<T> range(size);
        std::iota(std::rbegin(range), std::rend(range), start_value);
        return range;
    }



    // ---------------------------------------------------------------------------------
    // Calculate the mean value of some values.
    // ---------------------------------------------------------------------------------
    template <class T>
    double mean(const std::vector<T>& values)
    {
        auto beg = std::begin(values);
        auto end = std::end(values);
        assert(beg != end && "Calculation of mean is not possible on empty range!");

        const double sum   = static_cast<double>(std::accumulate(beg, end, T {0}));
        const double count = std::size(values);

        return sum / count;
    }



    // ---------------------------------------------------------------------------------
    // Calculate the standard_deviation of some values.
    // ---------------------------------------------------------------------------------
    template <class T>
    double standard_deviation(const std::vector<T>& values)
    {
        const double m = mean(values);
        double sum = 0.0;
        std::for_each(std::begin(values), std::end(values), [&](const double d) {
            sum += (d - m) * (d - m);
        });

        return static_cast<double>(sqrt(sum / (values.size() - 1)));
    }

}

#endif // JUL_VECTOR_EXT_H
