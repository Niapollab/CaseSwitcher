#ifndef UTILS_H
#define UTILS_H
#include <fstream>
#include <stdexcept>
#include <vector>
#include <thread>

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

inline std::vector<SwitcherThreadArgs> distribute_switcher_tasks(const _off_t file_size, _off_t threads_count, MappedFile& input_file, MappedFile& output_file)
{
    std::vector<SwitcherThreadArgs> tasks;
    if (threads_count < 1)
    {
        tasks.emplace_back(input_file, output_file, 0, file_size);
        return std::move(tasks);
    }

    if (threads_count > file_size)
        threads_count = file_size;

    _off_t segment_size = file_size / threads_count;
    for (_off_t i = 0; i < threads_count - 1; ++i)
    {
        _off_t offset = i * segment_size;
        tasks.emplace_back(input_file, output_file, offset, segment_size);
    }

    _off_t last_thread_index = threads_count - 1;
    _off_t last_segment_offset = last_thread_index * segment_size;
    _off_t last_segment_size = file_size - (last_thread_index * segment_size);
    tasks.emplace_back(input_file, output_file, last_segment_offset, last_segment_size);

    return std::move(tasks);
}

inline void join_all(std::vector<std::thread>& threads)
{
    for (auto& thread : threads)
        thread.join();
}

#endif // UTILS_H
