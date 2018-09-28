#include <iostream>

#include "sorting_algorithms.h"
#include "sorting_algorithms.cpp"

using namespace std;

int main()
{
    int arrayLength = -1, arrayToSort[] = { 99, 25, 100, 300, 6, 37, 3, 9, 7 };

    arrayLength = sizeof(arrayToSort) / sizeof(int);

    sorting_algorithms<int> sortingAlgorithms(arrayLength, arrayToSort);
    // sortingAlgorithms.bubble_sort();
    sortingAlgorithms.insertion_sort();

    cout << "array: ";

    for (int i = 0; i < arrayLength; i++)
    {
        cout << arrayToSort[i] << ", ";
    }

    cout << endl;

    return 0;
}
