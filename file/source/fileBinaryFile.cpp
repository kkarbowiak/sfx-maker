#include "fileBinaryFile.h"

#include <cstddef> // NULL
#include <cassert>

namespace file
{
///////////////////////////////////////////////////////////////////////////////
BinaryFile::BinaryFile()
  : mFilePtr(NULL)
  , mAccessFlags(0)
{
}
///////////////////////////////////////////////////////////////////////////////
BinaryFile::BinaryFile(std::string const & file_name, unsigned int flags)
  : mFilePtr(NULL)
  , mAccessFlags(flags)
{
    if ((flags & AF_READ) != 0)
    {
        mFilePtr = std::fopen(file_name.c_str(), "rb");
    }
    else if ((flags & AF_WRITE) != 0)
    {
        mFilePtr = std::fopen(file_name.c_str(), "wb");
    }
}
///////////////////////////////////////////////////////////////////////////////
BinaryFile::~BinaryFile()
{
    if (mFilePtr != NULL)
    {
        (void) std::fclose(mFilePtr);
    }
}
///////////////////////////////////////////////////////////////////////////////
bool BinaryFile::open(std::string const & file_name, unsigned int flags)
{
    mAccessFlags = flags;

    if ((flags & AF_READ) != 0)
    {
        mFilePtr     = std::fopen(file_name.c_str(), "rb");
    }
    else if ((flags & AF_WRITE) != 0)
    {
        mFilePtr = std::fopen(file_name.c_str(), "wb");
    }

    return (mFilePtr != NULL);
}
///////////////////////////////////////////////////////////////////////////////
bool BinaryFile::close()
{
    assert(mFilePtr != NULL);

    bool result = false;
    if (std::fclose(mFilePtr) == 0)
    {
        mFilePtr = NULL;
        result   = true;
    }

    return result;
}
///////////////////////////////////////////////////////////////////////////////
bool BinaryFile::writeData(void const * data_ptr, std::size_t size)
{
    assert(mFilePtr != NULL);
    assert((mAccessFlags & AF_WRITE) != 0);

    return (std::fwrite(data_ptr, size, 1, mFilePtr) == 1);
}
///////////////////////////////////////////////////////////////////////////////
bool BinaryFile::readData(void * data_ptr, std::size_t size)
{
    assert(mFilePtr != NULL);
    assert((mAccessFlags & AF_READ) != 0);

    bool result = false;

    long int current_position = std::ftell(mFilePtr);
    if (std::fseek(mFilePtr, 0, SEEK_END) == 0)
    {
        long int end_position = std::ftell(mFilePtr);
        if (static_cast<std::size_t>(end_position - current_position) >= size)
        {
            if (std::fseek(mFilePtr, current_position, SEEK_SET) == 0)
            {
                result = (std::fread(data_ptr, size, 1, mFilePtr) == 1);
            }
        }
    }

    return result;
}
///////////////////////////////////////////////////////////////////////////////
}

