#include <iostream>
#include <chrono>
#include "Switcher.h"
#include "MappedFile.h"
#include "Utils.h"

int main()
{
    using namespace std;
    using namespace chrono;

    const char* INPUT_FILENAME = "input.data";
    const char* OUTPUT_FILENAME = "output.data";

    time_point start_program = steady_clock::now();
    MappedFile input_file(INPUT_FILENAME, O_RDONLY, S_IREAD, PROT_READ);

    create_dummy_file(OUTPUT_FILENAME, input_file.size());
    MappedFile outfile_file(OUTPUT_FILENAME, O_RDWR, S_IWRITE, PROT_WRITE);

    init_switcher();

    time_point start_switching = steady_clock::now();

    char* input_data = input_file.get_data();
    char* output_data = outfile_file.get_data();

    for (_off_t i = 0; i < input_file.size(); ++i)
        output_data[i] = switch_char(input_data[i]);

    time_point stop_switching = steady_clock::now();

    input_file.close();
    outfile_file.close();
    time_point stop_program = steady_clock::now();

    cout << "Total switching time: " << duration_cast<milliseconds>(stop_switching - start_switching).count() << "ms" << endl;
    cout << "All execution time: " << duration_cast<milliseconds>(stop_program - start_program).count() << "ms" << endl;
    return 0;
}