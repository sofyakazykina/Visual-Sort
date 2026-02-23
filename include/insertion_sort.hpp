#pragma once
#include <vector>
template<typename T>
void insertionSort(std::vector<T>& vec)
{
    for (int32_t i = 1; i < vec.size(); ++i)
    {
        T key = vec[i];
        int32_t j = i - 1;
        while (j >= 0 && vec[j] > key)
        {
            vec[j + 1] = vec[j]; --j;
        }
        vec[j + 1] = key; }
}