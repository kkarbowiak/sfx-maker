/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef FILE_BINARY_FILE_H__DDK
#define FILE_BINARY_FILE_H__DDK

#include <string>
#include <cstdio>

namespace file
{
    class BinaryFile
    {
        public:
            enum eAccessFlags
            {
                AF_READ  = 0x01,
                AF_WRITE = 0x02
            };

        public:
            BinaryFile();
            BinaryFile(std::string const & file_name, unsigned int flags);
            ~BinaryFile();

            bool open(std::string const & file_name, unsigned int flags);
            bool close();

            template<typename T>
            bool write(T value);

            template<typename T>
            T read();

        private:
            bool writeData(void const * data_ptr, std::size_t size);
            bool readData(void * data_ptr, std::size_t size);

        private:
            FILE *       mFilePtr;
            unsigned int mAccessFlags;
    };
}

namespace file
{
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool BinaryFile::write(T value)
{
    return writeData(&value, sizeof(value));
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline T BinaryFile::read()
{
    T result;

    (void) readData(&result, sizeof(result));

    return result;
}
///////////////////////////////////////////////////////////////////////////////
}

#endif /* FILE_BINARY_FILE_H__DDK */

