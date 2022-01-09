#ifndef JUL_FILE_H
#define JUL_FILE_H

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



#include <fstream>
#include <string>
#include <cassert>
#include <cstdio>
#include <vector>

namespace jul 
{
    // -------------------------------------------------------------------------------------
    // Copy a file. This function will not throw like std::filesystem::copy_file but just
    // return 'false' on a missing file / directory.
    // Depending on the local std::ifstream/ofstream implementation this function should 
    // be non-blocking on the file to copy (fingers crossed)
    // -------------------------------------------------------------------------------------
    inline bool copy_file(const std::string& src_name, const std::string& dst_name)
    {
        assert(!src_name.empty());
        assert(!dst_name.empty());

        std::ifstream src(src_name, std::ios::binary);
        if (!src.is_open()) { return false; }

        std::ofstream dst(dst_name, std::ios::binary);
        if (!dst.is_open()) { return false; }

        dst << src.rdbuf();        
        return true;
    }



    // -------------------------------------------------------------------------------------
    // Parse a file line by line. Fails silent on missing files by just returning an empty vector
    // -------------------------------------------------------------------------------------
    inline std::vector<std::string> file_to_lines(const std::string& file_name)
    {
        assert(!file_name.empty());
        
        std::ifstream file(file_name);
        std::vector<std::string> lines{};
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        return lines;
    }


    // -------------------------------------------------------------------------------------
    // Parse a file line by line. Apply a 'Function' to each line.
    // -------------------------------------------------------------------------------------
    template <class Function>
    void for_each_line(const std::string& file_name, Function&& fn)
    {
        assert(!file_name.empty());

        std::ifstream file(file_name);
        std::string line;
        while (std::getline(file, line)) {
            fn(line);
        }
    }



    // -------------------------------------------------------------------------------------
    // Does a file exist?
    // -------------------------------------------------------------------------------------
    inline bool file_exists(const char* file_name)
    {
        std::FILE* f = std::fopen(file_name, "r");
        if (f != nullptr) {
            std::fclose(f);
            return true;
        }

        return false;
    }

    // -------------------------------------------------------------------------------------
    // File (class): Wrapper class for c file functions.
    // -------------------------------------------------------------------------------------
    class File {
    public:

        using Bytes  = std::size_t;

        enum class Mode {
            Read, 	        // Open a file for reading from start, fails on non exisiting file.
            Write, 	        // Create or overwrite file.
            Append,         // Append to a file or create new if the file doesn't exist.
            Read_extended,  // Open a file for read and write, fail on non existing file.
            Write_extended, // Create a file for read and write (or overwrite).
            Append_extended //	Append to a file or create new if the file doesn't exist. File is open for read/write
        };

        enum class Position {
            Beginning = SEEK_SET, // File beginning.
            Current   = SEEK_CUR, // Current stream position.
            End       = SEEK_END  // File end.
        };

        File()  {}
        ~File() { close(); }

        // no copy & move
        File(File&&)                 = delete;
        File(const File&)            = delete;
        File& operator=(File&&)      = delete;
        File& operator=(const File&) = delete;


        bool open(const char* file_name, Mode mode)
        {
            const auto m = mode_to_string(mode);
            m_handle = std::fopen(file_name, m);
            return m_handle != nullptr;
        }

        std::size_t read(void* buffer, Bytes element_size, std::size_t element_count)
        {
            assert(m_handle);
            assert(buffer);
            assert(element_size > 0);

            return std::fread(buffer, element_size, element_count, m_handle);
        }

        template <class T>
        std::size_t read(std::vector<T>& buffer)
        {
            assert(m_handle);
            assert(std::size(buffer) > 0);

            return std::fread(&buffer[0], sizeof(T), std::size(buffer), m_handle);
        }


        std::size_t write(const void* buffer, Bytes element_size, std::size_t element_count)
        {
            assert(m_handle);
            assert(buffer);
            assert(element_size > 0);

            return std::fwrite(buffer, element_size, element_count, m_handle);
        }

        template <class T>
        std::size_t write(const std::vector<T>& buffer)
        {
            assert(m_handle);
            assert(std::size(buffer) > 0);

            return std::fwrite(buffer.data(), sizeof(T), std::size(buffer), m_handle);
        }


        int error() const
        {
            assert(m_handle);
            return std::ferror(m_handle);
        }

        // reads the file size in bytes, will set the stream position to the beginning!
        Bytes file_size()
        {
            seek(0, Position::End);
            Bytes size = tell();
            seek(0, Position::Beginning);
            return size;
        }

        bool seek(long offset, Position pos)
        {
            assert(m_handle);
            return std::fseek(m_handle, offset, (int) pos) == 0;
        }

        long tell()
        {
            assert(m_handle);
            return std::ftell(m_handle);
        }

        // Moves the file position indicator to the beginning of the given file stream.
        // The function is equivalent to std::fseek(stream, 0, SEEK_SET);, except that end - of - file and error indicators are cleared.
        void rewind()
        {
            assert(m_handle);
            ::rewind(m_handle);
        }

        void close()
        {
            if (m_handle) {
                std::fclose(m_handle);
                m_handle = nullptr;
            }
        }

        bool eof() const
        {
            assert(m_handle);
            return std::feof(m_handle) != 0;
        }

        bool flush() const
        {
            assert(m_handle);
            return std::fflush(m_handle) == 0;
        }

        std::FILE* handle() { return m_handle; }


    private:

        std::FILE* m_handle = nullptr;

        constexpr const char* mode_to_string(Mode mode)
        {
            switch (mode)
            {
            case Mode::Read:
                return "r";
            case Mode::Write:
                return "w";
            case Mode::Append:
                return "a";
            case Mode::Read_extended:
                return "r+";
            case Mode::Write_extended:
                return "w+";
            case Mode::Append_extended:
                return "a+";
            default:
                assert(false);
            }
            return "";
        }
    };

}

#endif // JUL_FILE_H
