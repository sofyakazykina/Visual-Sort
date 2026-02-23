#pragma once
#include <vector>
template<typename T>
void selectionSort(std::vector<T>& vec)
{
    for (auto it = vec.begin(); it < vec.end()-1; ++it)
    {
        auto minIt = it;
        for (auto it2 = it + 1; it2 <vec.end(); ++it2)
        {
            if ((*it2) <(*minIt)) {
                minIt = it2;
            }
        }
        swap((*it), *(minIt));
    }
}