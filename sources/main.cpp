#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <fstream>
#include <algorithm>
#include <chrono>

const size_t NUMBER_OF_THREADS = 4;

using namespace std;

inline string process_line(string& str)
{
    for (char& ch : str)
    {
        if (isdigit(ch))
        {
            int d = ch - '0';
            if (d < 9)
                ch = '0' + d + 1;
            else
                ch = '0';
        }
        else if (isupper(ch))
            ch = tolower(ch);
        else
            ch = toupper(ch);
    }

    return str;
}

void process_thread(vector<string>& lines, size_t offset, size_t number_of_threads)
{
    for (size_t i = offset; i < lines.size(); i += number_of_threads)
        lines[i] = process_line(lines[i]);
}

int main()
{
    const char* INPUT_FILENAME = "input.data";
    const char* OUTPUT_FILENAME = "output_cpp.data";
    
    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    try
    {
        cout << "Load input data" << endl;
        ifstream in_file(INPUT_FILENAME);

        if (!in_file.is_open())
        {
            cout << "Fail to open file!" << endl;
            return 0;
        }

        vector<string> lines;
        string buffer;
        while (in_file >> buffer)
            lines.push_back(buffer + "\n");
        in_file.close();

        chrono::steady_clock::time_point data_load = std::chrono::steady_clock::now();

        cout << "Start " << NUMBER_OF_THREADS << " threads" << endl;
        vector<thread> thread_pool;
        for (size_t i = 0; i < NUMBER_OF_THREADS; i++)
            thread_pool.emplace_back(process_thread, ref(lines), i, NUMBER_OF_THREADS);

        cout << "Wait for finish" << endl;
        for (thread& th : thread_pool)
            th.join();

        cout << "Save output data" << endl;
        ofstream out_file(OUTPUT_FILENAME);
        for (auto &line : lines)
        {
            out_file.write(line.c_str(), line.size());
        }
        out_file.close();

        cout << "Done" << endl;
        chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::cout << "data load time: " << std::chrono::duration_cast<std::chrono::milliseconds>(data_load - begin).count() << "ms" << std::endl;
        std::cout << "total execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
    }
    catch (const exception &e)
    {
        cout << e.what();
    }
    
    system("pause");
    return 0;
}