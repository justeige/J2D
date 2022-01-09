#ifndef JUL_MACRO_H
#define JUL_MACRO_H


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


#include <cassert>



// macros for loops:
#define forever        for (;;)
#define repeat(cnt, N) for (int cnt = 0; cnt < N; ++cnt)



// assert that n is a valid number (NaN will fail this!)
#define nan_check(n) assert(n == n)



// disable copy and assignment
#define no_copy_and_assign(obj)     \
    obj(obj const& other) = delete; \
    void operator=(obj const& other) = delete;




// disable move and assignment
#define no_move_and_assign(obj) \
    obj(obj && other) = delete; \
    void operator=(obj && other) = delete;


#endif // JUL_MACRO_H