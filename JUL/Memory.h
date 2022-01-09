#ifndef JUL_MEMORY_H
#define JUL_MEMORY_H

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



// -------------------------------------------------------------------
// This is a collection of very, very special memory functions.
// These are mostly for replacing legacy code or should be used when REALLY
// needed.
// Quick reminder what few advantages 'malloc' has over 'new':
//
// - malloc() doesn't call constructors
// - malloc will return NULL instead of throwing on fail (only usefull in low mem. environments)
// - new() can't reallocate memory explicit
//
// All other memory functions have the same implied warning 
// - ONLY USE THESE IF YOU KNOW WHAT YOU ARE DOING! -
// -------------------------------------------------------------------

#include <cstddef>
#include <cassert>
#include <type_traits>
#include <cstring> // for memcpy

namespace jul {

    
    // ---------------------------------------------------------------
    // Type safe version of malloc.
    // ---------------------------------------------------------------
    template <class T>
    T* allocate()
    {
        static_assert(std::is_pod<T>::value, "allocating a non-pod type!");
        return static_cast<T*>(std::malloc(sizeof(T)));
    }



    // ---------------------------------------------------------------
    // Type safe version of memcpy.
    // ---------------------------------------------------------------
    template <class T, class D>
    T copy_memory(D* raw_data)
    {
        static_assert(std::is_pod<T>::value, "allocating a non-pod type!");
        assert(raw_data != nullptr);

        T obj = {};
        std::memcpy(&obj, raw_data, sizeof(T));
        return obj;
    }



    // ---------------------------------------------------------------
    // Type safe version of memcmp, will return the bigger obj.
    // ---------------------------------------------------------------
    template <class T>
    T* compare_memory(T* a, T* b)
    {
        static_assert(std::is_pod<T>::value, "allocating a non-pod type!");
        assert(a != nullptr);
        assert(b != nullptr);

        const int result = std::memcmp(a, b, sizeof(a));
        return result >= 0 ? a : b;
    }


    // ---------------------------------------------------------------
    // Custom version of realloc/free.
    // ---------------------------------------------------------------
    template <class T>
    T reallocate(T memory, std::size_t old_size, std::size_t new_size)
    {
        if (new_size == 0) {
            std::free(memory);
            return nullptr;
        }

        return static_cast<T>(std::realloc(memory, new_size));
    }



    // ---------------------------------------------------------------
    // Custom version of realloc.
    // ---------------------------------------------------------------
    template <class T>
    T grow_memory(T memory, std::size_t old_count, std::size_t new_count)
    {
        return jul::reallocate(memory, sizeof(T) * old_count, sizeof(T) * new_count);
    }



    // ---------------------------------------------------------------
    // Custom version of realloc for array types.
    // ---------------------------------------------------------------
    template <class T>
    void free_array(T memory, std::size_t allocated)
    {
        const auto new_mem = reallocate(memory, sizeof(T) * allocated, 0);
        assert(new_mem == nullptr); // sanity check
    }


}


#endif // JUl_MEMORY_H
