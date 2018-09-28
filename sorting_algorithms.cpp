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
    arrayToSort = NULL;
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
