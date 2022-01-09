#ifndef JUL_PARSING_H
#define JUL_PARSING_H


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
#include <string>

namespace jul 
{
    // ---------------------------------------------------------------------------
    // Try to convert a string to a number. If this fails, the function will
    // return an empty optional<Number>.
    //
    // Allowed types are: int, long, float, double.
    // ---------------------------------------------------------------------------
    template <class Number>
    std::optional<Number> try_convert(const std::string& str)
    {
        try
        {
            if constexpr (std::is_same<Number, int>::value) {
                return std::stoi(str, nullptr, 0);
            }
            else if constexpr (std::is_same<Number, long>::value) {
                return std::stol(str, nullptr, 0);
            }
            else if constexpr (std::is_same<Number, float>::value) {
                return std::stof(str, nullptr, 0);
            }
            else if constexpr (std::is_same<Number, double>::value) {
                return std::stod(str, nullptr, 0);
            }
            else {
                static_assert(false, "Type is not supported!");
            }
        }
        catch (const std::exception&)
        {
            // all std:: conversation functions throw exceptions on a bad value...
            return std::nullopt;
        }
    }
    
    
    
    // ---------------------------------------------------------------------------
    // Cast an enum value to its underlying type.
    // ---------------------------------------------------------------------------
    template <class Enum>
    constexpr std::underlying_type_t<Enum> to_underlying(Enum value) noexcept 
    {
        static_assert(std::is_enum<Enum>::value, "Value has to be an enum!");
        return static_cast<std::underlying_type_t<Enum>>(value);
    }
}

#endif // JUL_PARSING_H
