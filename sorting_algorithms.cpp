#include "sorting_algorithms.h"

template <class T>
sorting_algorithms<T>::sorting_algorithms(int arrayLength, T *arrayToSort)
{
    this->arrayToSort = arrayToSort;
    this->arrayLength = arrayLength;
}

template <class T>
sorting_algorithms<T>::~sorting_algorithms()
{
    arrayToSort = 0;
}

template <class T>
void sorting_algorithms<T>::bubble_sort()
{
    int temp = 0;

    for (int i = 0; i < arrayLength; i++)
    {
        for (int j = i + 1; j < arrayLength; j++)
        {
            if (arrayToSort[i] > arrayToSort[j])
            {
                temp = arrayToSort[j];
                arrayToSort[j] = arrayToSort[i];
                arrayToSort[i] = temp;
            }
        }
    }
}

template <class T>
void sorting_algorithms<T>::insertion_sort()
{
    for (int i = 1; i < arrayLength; i++)
    {
        int j = i - 1, currentValue = arrayToSort[i];

        while (j > -1 && currentValue < arrayToSort[j])
        {
            arrayToSort[j + 1] = arrayToSort[j];

            j--;
        }

        arrayToSort[j + 1] = currentValue;
    }
}
