#ifndef MAPPEDFILE_H
#define MAPPEDFILE_H
#include <stdexcept>
#include <fcntl.h>
#include <sys/stat.h>
#include "mman_lib/mman.h"

class MappedFile
{
private:
    char* _file_data;
    _off_t _file_size;
    int _file_handle;
    bool _closed;
    
    MappedFile() = delete;
    MappedFile(const MappedFile& mappedFile) = delete;
    MappedFile& operator=(const MappedFile& mappedFile) = delete;

public:
    MappedFile(
        const char* filename,
        const int oflag = O_RDONLY,
        const int pmode = S_IREAD,
        const int prot = PROT_READ,
        const int flags = MAP_PRIVATE,
        const _off_t offset = 0)
    {
        _closed = false;
        _file_handle = open(filename, oflag | pmode);

        struct stat file_stats;
        if (fstat(_file_handle, &file_stats) == -1)
            throw std::runtime_error("Unable to get size of file.");
        _file_size = file_stats.st_size;

        _file_data = static_cast<char*>(mmap(nullptr, _file_size, prot, flags, _file_handle, offset));
    }

    ~MappedFile()
    {
        if (!_closed)
            close();
    }

    inline char* get_data()
    {
        if (_closed)
            throw std::runtime_error("File was closed.");
        
        return _file_data;
    }

    inline _off_t size() const
    {
        return _file_size;
    }

    inline void close()
    {
        if (!_closed)
        {
            munmap(_file_data, _file_size);
            ::close(_file_handle);
            _closed = true;
            _file_handle = 0;
            _file_size = 0;
            _file_data = nullptr;
        }
    }
};

#endif // MAPPEDFILE_H
