#ifndef JUL_ARRAY_EXT_H
#define JUL_ARRAY_EXT_H

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

#include <array>



namespace jul {



	// ---------------------------------------------------------------------------------
	// Creates an array of combined size/values of two arrays.
	// ---------------------------------------------------------------------------------
	// Example:
	// std::array<int, 2> arr1{ 1, 2 };
	// std::array<int, 3> arr2{ 3, 4, 5 };
	// 
	// std::array<int, 5> combined = jul::appended(arr1, arr2);
	// combined == { 1, 2, 3, 4, 5 }
	// ---------------------------------------------------------------------------------
	template <class T, std::size_t SizeA, std::size_t SizeB>
	std::array<T, SizeA + SizeB> appended(const std::array<T, SizeA>& a, const std::array<T, SizeB>& b)
	{
		std::array<T, SizeA + SizeB> combined;
		std::copy(std::begin(a), std::end(a), std::begin(combined));
		std::copy(std::begin(b), std::end(b), std::begin(combined) + std::size(a));
		return combined;
	}
	

}

#endif // !JUL_ARRAY_EXT_H

