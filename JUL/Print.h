#ifndef JUL_PRINT_H
#define JUL_PRINT_H



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



#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <iterator>

namespace jul {



	// ----------------------------------------------------------
	// Iterator that skips the last element of a container.
	// ----------------------------------------------------------
	template <class Container>
	struct Skip_last_element_iterator {

		Container& c;

		friend auto begin(const Skip_last_element_iterator& it)	{ return std::begin(it.c); }

		friend auto end(const Skip_last_element_iterator& it)
		{
			auto e = std::end(it.c);
			if (e != begin(it)) {
				--e;
			}
			return e;
		}
	};



	// ----------------------------------------------------------
	// Factory method that creates Skip_last_element_iterators.
	// ----------------------------------------------------------
	template <class Container>
	Skip_last_element_iterator<Container> skip_last_element(Container& c) { return { c }; }



	// ----------------------------------------------------------
	// Iterator that skips the first element of a container.
	// ----------------------------------------------------------
	template <class Container>
	struct Skip_first_element_iterator {

		Container& c;

		friend auto begin(const Skip_first_element_iterator& it) {	return std::begin(it.c) + 1; }

		friend auto end(const Skip_first_element_iterator& it)   {	return std::end(it.c); }
	};



	// ----------------------------------------------------------
	// Factory method that creates Skip_first_element_iterators.
	// ----------------------------------------------------------
	template <class Container>
	Skip_first_element_iterator<Container> skip_first_element(Container& c) { return { c }; }
	

	
	// --------------------------------------------
	// Pretty-print a vector<T>.
	// Example:
	// auto vec = jul::make_vector(0, 10);
	// jul::print(vec);
	// = > { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
	// --------------------------------------------
	template <class T>
	void print(const std::vector<T>& vec, const char* delimiter = ", ", bool show_brackets = true, std::ostream& stream = std::cout)
	{
		if (std::size(vec) == 0) {
			if (show_brackets) { stream << "{}"; }
			return;
		}

		if (show_brackets) { stream << "{ "; }
		std::copy(
			std::begin(vec),
			std::end(vec) - 1,
			std::ostream_iterator<T> { stream, delimiter }
		);
		stream << vec.back();
		if (show_brackets) { stream << " }"; }
	}



	// --------------------------------------------
	// Pretty-print an array<T>.
	// --------------------------------------------
	template <class T, std::size_t Size>
	void print(const std::array<T, Size>& arr, const char* delimiter = ", ", bool show_brackets = true, std::ostream& stream = std::cout)
	{
		// not sure why one would create an std::array of size 0, 
		// but it would throw an exception if not handled...
		if constexpr (Size == 0) {
			stream << "{}";
			return;
		}
		else {
			if (show_brackets) { stream << "{ "; }
			std::copy(
				std::begin(arr),
				std::end(arr) - 1,
				std::ostream_iterator<T> { stream, delimiter }
			);
			stream << arr.back();
			if (show_brackets) { stream << " }"; }
		}
	}



	// --------------------------------------------
	// Pretty-print a map<K,V>.
	// --------------------------------------------
	template <class Key, class Value>
	void print(const std::map<Key, Value>& m, const char* delimiter = ", ", bool show_brackets = true, std::ostream& stream = std::cout)
	{
		// print an empty map
		if (std::size(m) == 0) {
			if (show_brackets) { stream << "{}"; }
			return;
		}

		// "full" map
		if (show_brackets) { stream << "{ "; }

		// print every value except the last with a delimiter
		for (const auto& [key, value] : skip_last_element(m)) {
			stream << "(" << key << ", " << value << ")" << delimiter;
		}

		// print the last value
		auto [key, value] = *std::rbegin(m);
		stream << "(" << key << ", " << value << ")";

		if (show_brackets) { stream << " }"; }
	}

}
#endif // !JUL_PRINT_H

