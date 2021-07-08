#include <iostream>
#include <chrono>
#include <thread>
#include "Switcher.h"
#include "MappedFile.h"
#include "Utils.h"

inline void switch_task(const SwitcherThreadArgs& args)
{
    char* input_data = args.input_file.get_data();
    char* output_data = args.output_file.get_data();

    for (_off_t i = args.offset; i < args.size; ++i)
        output_data[i] = switch_char(input_data[i]);
}

int main()
{
    using namespace std;
    using namespace chrono;

    const char* INPUT_FILENAME = "input.data";
    const char* OUTPUT_FILENAME = "output.data";
    const int NUMBER_OF_THREADS = 4;

    time_point start_program = steady_clock::now();
    MappedFile input_file(INPUT_FILENAME, O_RDONLY, S_IREAD, PROT_READ);

    create_dummy_file(OUTPUT_FILENAME, input_file.size());
    MappedFile outfile_file(OUTPUT_FILENAME, O_RDWR, S_IWRITE, PROT_WRITE);

    init_switcher();
    vector<SwitcherThreadArgs> thread_args = distribute_switcher_tasks(input_file.size(), NUMBER_OF_THREADS, input_file, outfile_file);

    time_point start_switching = steady_clock::now();
    vector<thread> threads;
    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        threads.emplace_back(switch_task, thread_args[i]);

    join_all(threads);
    time_point stop_switching = steady_clock::now();

    input_file.close();
    outfile_file.close();
    time_point stop_program = steady_clock::now();

    cout << "Total switching time: " << duration_cast<milliseconds>(stop_switching - start_switching).count() << "ms" << endl;
    cout << "All execution time: " << duration_cast<milliseconds>(stop_program - start_program).count() << "ms" << endl;
    return 0;
}