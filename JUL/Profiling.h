#ifndef JUL_PROFILING_H
#define JUL_PROFILING_H


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


// helper macros to create a scope timer
#if defined(_DEBUG) || defined(DEBUG)
#define measure_time() jul::detail::Scope_Timer scope_timer {__func__, std::cout}
#else
#define measure_time() ((void)0)
#endif

namespace jul {
namespace detail {

    template <class Out = std::ostream>
    struct Scope_Timer {
        using Clock = std::chrono::steady_clock;

        const char* function_name = {};
        const Clock::time_point start = {};
        Out& out;

        Scope_Timer(const char* func_name, Out& output) :
            function_name{ func_name },
            start{ Clock::now() },
            out{ output }
        {}
        ~Scope_Timer()
        {
            using namespace std::chrono;

            auto end = Clock::now();
            auto duration_in_ms = duration_cast<milliseconds>(end - start).count();
            if (duration_in_ms != 0) {
                out << function_name << ": " << duration_in_ms << " ms\n";
                return;
            }

            auto duration_in_ns = duration_cast<nanoseconds>(end - start).count();
            out << function_name << ": 0." << duration_in_ns << " ms\n";
        }
    };

 }
}

#endif // JUL_PROFILING_H