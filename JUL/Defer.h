#ifndef JUL_DEFER_H
#define JUL_DEFER_H

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

#include <exception> // for std::uncaught_exceptions()

// ---------------------------------------------------------------------------------
// This is a copy of the Golang keyword 'defer'.
// The concept is in C++ known under ScopeGuard, ExitGuard and similar constructs.
// Basically, it uses RAII for arbitrary code segments.
//
// Example:
// void my_function() {
//     m = allocate_memory();
//     defer(delete_memory(m););
//     /* other code */    
// } <- at function end, the defer-block will be called!
// ---------------------------------------------------------------------------------
#define defer(func) auto JUL_DEFER_UNIQUE_NAME = jul::detail::Deferred { []() { func ; } }



// ---------------------------------------------------------------------------------
// Same as defer, but is only called if there ARE NO uncaught exceptions in scope.
// ---------------------------------------------------------------------------------
#define defer_on_success(func)   auto JUL_DEFER_UNIQUE_NAME = jul::detail::Deferred_Success   { []() { func ; } }



// ---------------------------------------------------------------------------------
// Same as defer, but is only called if there ARE uncaught exceptions in scope.
// ---------------------------------------------------------------------------------
#define defer_on_exception(func) auto JUL_DEFER_UNIQUE_NAME = jul::detail::Deferred_Exception { []() { func ; } }



// helper macros to create a unique name for every defer-block
#define JUL_DEFER_CONCAT_(x,y) x##y
#define JUL_DEFER_CONCAT(x,y) JUL_DEFER_CONCAT_(x,y)
#define JUL_DEFER_UNIQUE_NAME JUL_DEFER_CONCAT(defer_, __LINE__)

namespace jul {
	namespace detail {

		template <class Function>
		class Deferred final {
		public:
			explicit Deferred(Function f) noexcept : m_f(std::move(f)) {}

			~Deferred() { m_f(); }

		private:
			Function m_f;
		};

		template <class Function>
		class Deferred_Success final {
		public:
			explicit Deferred_Success(Function f) noexcept : m_f(std::move(f)) {}

			~Deferred_Success() noexcept(noexcept(m_f()))
			{
				// are there new uncaught exceptions since constructions?
				// if no, the deferred function will be called.
				if (m_uncaught_exceptions == std::uncaught_exceptions()) {
					m_f();
				}
			}

		private:
			Function m_f;
			const int m_uncaught_exceptions = std::uncaught_exceptions();
		};


		template <class Function>
		class Deferred_Exception final {
		public:
			explicit Deferred_Exception(Function f) noexcept : m_f(std::move(f)) {}

			~Deferred_Exception() noexcept(noexcept(m_f()))
			{
				// are there new uncaught exceptions since constructions?
				// if yes, the deferred function will be called.
				if (m_uncaught_exceptions < std::uncaught_exceptions()) {
					m_f();
				}
			}

		private:
			Function m_f;
			const int m_uncaught_exceptions = std::uncaught_exceptions();
		};

	}
}

#endif // JUL_DEFER_H
