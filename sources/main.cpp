#include <iostream>
#include <chrono>
#include "Switcher.h"
#include "MappedFile.h"

int main()
{
    using namespace std;
    using namespace chrono;

    const char* FILENAME = "input.data";
    MappedFile file(FILENAME, O_RDWR, S_IREAD | S_IWRITE, PROT_READ | PROT_WRITE);
    init_switcher();

    time_point start_switching = steady_clock::now();
    char* data = file.get_data();
    for (_off_t i = 0; i < file.size(); ++i)
        data[i] = switch_char(data[i]);
    time_point stop_switching = steady_clock::now();

    cout << "Total time: " << duration_cast<milliseconds>(stop_switching - start_switching).count() << "ms" << endl;

    file.close();

    system("pause");
    return 0;
}