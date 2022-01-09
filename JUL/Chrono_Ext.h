#ifndef JUL_CHRONO_EXT_H
#define JUL_CHRONO_EXT_H



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




#include <chrono>
using namespace std::chrono_literals;

#include <cassert>
#include <thread>   // for std::this_thread::xxx
#include <ctime>    // std::time_t, std::tm, std::localtime, std::mktime
#include <iomanip>  // std::put_time



namespace jul
{
	// ----------------------------------------------------------------
	// Wrapper for std::this_thread::sleep_for.
	//
	// Example:
	//	sleep_for(12h); 
	//	sleep_for(10ms);
	//	sleep_for(99min);
	// ----------------------------------------------------------------
	template <class Duration>
	void sleep_for(const Duration& duration)
	{
		if constexpr (std::is_same<Duration, std::chrono::nanoseconds>::value
			       || std::is_same<Duration, std::chrono::microseconds>::value
			       || std::is_same<Duration, std::chrono::milliseconds>::value
			       || std::is_same<Duration, std::chrono::seconds>::value
			       || std::is_same<Duration, std::chrono::minutes>::value
			       || std::is_same<Duration, std::chrono::hours>::value) {
			std::this_thread::sleep_for(duration);
		}
		else {
			static_assert(false, "Duration is not valid!");
		}
	}



	// ----------------------------------------------------------------
	// Sleep until a specific time in hour [0;23] and min [0;59].
	// System-clock is used as base time!
	//
	// Example:
	//	sleep_until(12h, 39min); // code will stop here until 12:39!
	//
	// ----------------------------------------------------------------
	inline void sleep_until(std::chrono::hours hour, std::chrono::minutes min)
	{
		// use the underlying values and check for valid hour/minute values
		const int h = hour.count();
		const int m = min.count();
		assert(h <= 23 && h > 0);
		assert(m <= 59 && m > 0);

		using namespace std::chrono;

		std::time_t raw_time = system_clock::to_time_t(system_clock::now());
		std::tm* time = std::localtime(&raw_time);

		time->tm_hour = h;
		time->tm_min = m;
		time->tm_sec = 0;

		std::this_thread::sleep_until(system_clock::from_time_t(std::mktime(time)));
	}
}

#endif // JUL_CHRONO_EXT_H

