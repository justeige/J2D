#ifndef JUL_TYPES_H
#define JUL_TYPES_H


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



#include <stdint.h>



namespace jul {
    namespace types {

        // typedefs - singed
        using i8  = int8_t;
        using i16 = int16_t;
        using i32 = int32_t;
        using i64 = int64_t;

        // numeric limits - singed
        constexpr i8  i8_Min = i8{ INT8_MIN };
        constexpr i8  i8_Max = i8{ INT8_MAX };
        constexpr i16 i16_Min = i16{ INT16_MIN };
        constexpr i16 i16_Max = i16{ INT16_MAX };
        constexpr i32 i32_Min = i32{ INT32_MIN };
        constexpr i32 i32_Max = i32{ INT32_MAX };
        constexpr i64 i64_Min = i64{ INT64_MIN };
        constexpr i64 i64_Max = i64{ INT64_MAX };



        // typedefs - unsigned
        using u8  = uint8_t;
        using u16 = uint16_t;
        using u32 = uint32_t;
        using u64 = uint64_t;

        // numeric limits - singed
        constexpr u8  u8_Min = u8{ 0 };
        constexpr u8  u8_Max = u8{ UINT8_MAX };
        constexpr u16 u16_Min = u16{ 0 };
        constexpr u16 u16_Max = u16{ UINT16_MAX };
        constexpr u32 u32_Min = u32{ 0 };
        constexpr u32 u32_Max = u32{ UINT32_MAX };
        constexpr u64 u64_Min = u64{ 0 };
        constexpr u64 u64_Max = u64{ UINT64_MAX };



        // typedefs - floating point types
        using f32 = float;
        using f64 = double;

        static_assert(sizeof(f32) == 4);
        static_assert(sizeof(f64) == 8);
    }
}
#endif // JUL_TYPES_H
