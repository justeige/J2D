#ifndef JUL_EITHER_H
#define JUL_EITHER_H

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


#include <optional>

namespace jul {

    // --------------------------------------------------------------------------
    // Either (class): A union wrapper that tracks which value type it holds.
    // Very similar to a variant type, but way simpler. 
    // Example:
    // 
    // Either<int, std::string> Machine::fetch_status()
    // {
    //     int status_bit = this.read_value(STATUS_BIT);
    //     if (status_bit == ERROR_FLAG)
    //         return { "Machine has an error!" };
    //     else
    //         return { status_bit };
    // }
    // --------------------------------------------------------------------------
    template <class TLeft, class TRight>
    class Either {
    public:

        // there are several solution to make this type work with two same values, but I don't think
        // its worth it to be honest.
        static_assert(!std::is_same<TLeft, TRight>::value, "Types can't be the same!");

        // constructors
        constexpr Either(const TLeft& value) : m_is_left { true }, m_left_value { value } {}
        constexpr Either(TLeft&& value)      : m_is_left { true }, m_left_value { std::move(value) } {}

        constexpr Either(const TRight& value) : m_is_left { false }, m_right_value{ value } {}
        constexpr Either(TRight&& value)     : m_is_left  { false }, m_right_value{ std::move(value) } {}

        // desctructor; manual calling the destructor of a type looks a bit weird, but is allowed
        ~Either()
        {
            if (m_is_left)
                m_left_value.~TLeft();
            else
                m_right_value.~TRight();
        }

        // acessors
        std::optional<TLeft> left() const
        {
            return m_is_left ? m_left_value : std::nullopt;
        }

        std::optional<TLeft> right() const
        {
            return m_is_left ? std::nullopt : m_right_value;
        }


    private:

        // data
        union {
            TLeft  m_left_value;
            TRight m_right_value;
        };

        bool m_is_left = true;
    };

}
#endif // JUL_EITHER_H