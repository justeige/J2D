#ifndef JUL_SPIN_LOCK_H
#define JUL_SPIN_LOCK_H

#include <atomic>

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

namespace jul {


	// -----------------------------------------------------------------------------------------
	// A simple spin lock implementation based on std::atomic_flag.
	// General: Spin locks performane better than mutexes when the locking period is "short".
	// Please do some actual performance profiling before using this class over a std::mutex!
	//
	// Ref: https://en.cppreference.com/w/cpp/atomic/atomic_flag
	// -----------------------------------------------------------------------------------------
	class Spin_Lock final {
	public:

		Spin_Lock()  = default;
		~Spin_Lock() = default;
		
		void lock()
		{
			while (m_flag.test_and_set(std::memory_order_acquire))
			{
				/* spin and do nothing */
			}
		}

		void unlock()
		{
			m_flag.clear(std::memory_order_release);
		}

	private:
		std::atomic_flag m_flag = ATOMIC_FLAG_INIT;


		// no copies or moves!
		Spin_Lock(Spin_Lock&& other)                 = delete;
		Spin_Lock& operator=(const Spin_Lock& other) = delete;
		Spin_Lock(const Spin_Lock& other)       = delete;
		Spin_Lock& operator=(Spin_Lock&& other) = delete;
	};

}


#endif // JUL_SPIN_LOCK_H
