#ifndef UTILS_H
#define UTILS_H
#include <fstream>
#include <stdexcept>

struct SwitcherThreadArgs
{
    MappedFile& input_file;
    MappedFile& output_file;
    _off_t offset;
    _off_t size;

    SwitcherThreadArgs(MappedFile& input_file, MappedFile& output_file, _off_t offset, _off_t size)
        : input_file(input_file), output_file(output_file), offset(offset), size(size)
    {
        
    }
};

inline void create_dummy_file(const char* filename, const size_t size)
{
    if (size < 1)
        throw std::runtime_error("Size must be greater than one.");
    
    std::ofstream file(filename, std::ios::trunc);
    file.seekp(size - 1);
    file.write("", 1);
    file.close();
}

#endif // UTILS_H
