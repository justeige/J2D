#ifndef JUL_POINTER_H
#define JUL_POINTER_H


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


#include <memory> // for std::unique_ptr, std::shared_ptr
#include <cassert>

namespace jul {

    // reference counted non-sharing
    template <class T>
    using Unique = std::unique_ptr<T>;



    // reference counted sharing
    template <class T>
    using Shared = std::shared_ptr<T>;



    // raw pointer
    template <class T>
    using Ptr = T *;



    // reference
    template <class T>
    using Ref = T &;



    // RAII wrapper for raw pointer, no reference counting
    template <class T>
    class Scoped {
    public:
        explicit Scoped()       : m_ptr{nullptr} {}

        explicit Scoped(T* ptr) : m_ptr{ptr}     
        {
            assert(ptr != nullptr);
        }

        ~Scoped() { release(); }

        void release() 
        { 
            if (m_ptr) {
                delete(m_ptr);
                m_ptr = nullptr;
            }
        }

        void operator = (T* ptr) 
        { 
            assert(ptr != nullptr   && "Assignment of a nullptr is now allowed!");
            assert(m_ptr == nullptr && "Reassigment without releasing the memory!");

            m_ptr = ptr; 
        }

        T& operator * () { return *m_ptr; }
        T* operator ->() { return m_ptr;  }

    private:
        T* m_ptr;
    };
}

#endif // JUL_POINTER_H