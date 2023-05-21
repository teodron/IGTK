/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

size_t quick_partition(std::vector<int>& data, size_t start, size_t end)
{
    size_t r = (start + end) / 2;
    std::swap(data[r], data[end]);
    size_t i = start;
    for (size_t j = start; j <= end; ++j)
    {
        if (data[j] < data[end])
        {
            std::swap(data[j], data[i]);
            ++i;
        }
    }
    std::swap(data[i], data[end]);
    return i;
}

int quick_select(std::vector<int>& data, size_t start, size_t end, size_t k)
{
    while (true)
    {
        if (start > end)
        {
            return -1;
        }

        if (start == end)
        {
            return data[start];
        }
        size_t pivot = quick_partition(data, start, end);
        if (pivot == k)
        {
            return data[k];
        }

        if (k < pivot)
        {
            end = pivot - 1;
        }
        else
        {
            start = pivot + 1;
        }
    }
}

void print(const std::vector<int>& data)
{
    for (auto element : data)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main()
{


    std::vector<int> in = { 8, 5, 7, 6, 3, 9, 1 };
    print(in);
    //std::cout << quick_partition(in, 0, in.size() - 1) << " <> " << std::endl;
    std::cout << quick_select(in, 0, in.size() - 1, 2 - 1) << std::endl;
    print(in);

    return 0;
}
