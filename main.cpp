#include <iostream>

#include "sorting_algorithms.h"
#include "sorting_algorithms.cpp"

using namespace std;

int main()
{
    int arrayLength = -1, arrayToSort[] = { 1, 1, 9, 3, 6, 6, 4, 1, 5, 3 };

    arrayLength = sizeof(arrayToSort) / sizeof(int);

    cout << "unsorted-array: ";

    for (int i = 0; i < arrayLength; i++)
    {
        cout << arrayToSort[i] << ", ";
    }

    cout << endl;

    sorting_algorithms<int> sortingAlgorithms(arrayLength, arrayToSort);
    // sortingAlgorithms.bubble_sort();
    // sortingAlgorithms.insertion_sort();
    // cout << "number of inversions: " << sortingAlgorithms.merge_sort() << endl;
    sortingAlgorithms.quick_sort(true);

    cout << "sorted-array: ";

    for (int i = 0; i < arrayLength; i++)
    {
        cout << arrayToSort[i] << ", ";
    }

    cout << endl;

    return 0;
}
