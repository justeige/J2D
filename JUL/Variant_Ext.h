#ifndef JUL_VARIANT_H
#define JUL_VARIANT_H


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


namespace jul 
{

    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...)->overloaded<Ts...>;

    // ---------------------------------------------------------------------------------------
    // match: A nicer syntax for visiting variants... should be a keyword in c++... 
    // example:
    //
    // std::variant<int, float, std::string> ifs{ "Should be 2" };
    // int val = jul::match(ifs,
    //    [](const int& i)         -> int { return 0;},
    //    [](const float& f)       -> int { return 1;},
    //    [](const std::string& s) -> int { return 2;}
    // );
    // => val = 2
    // ---------------------------------------------------------------------------------------
    template <typename Variant, typename... Cases>
    auto match(Variant&& variant, Cases&& ... cases)
    {
        return std::visit(overloaded{ std::forward<Cases>(cases)... }, std::forward<Variant>(variant));
    }

}

#endif // JUL_VARIANT_H