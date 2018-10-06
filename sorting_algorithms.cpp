#include "sorting_algorithms.h"

template <class T>
sorting_algorithms<T>::sorting_algorithms(int arrayLength, T *arrayToSort)
{
    this->arrayLength = arrayLength;
    this->arrayToSort = arrayToSort;

    maximumValue = (T)pow(2.0, (double)((sizeof(T) * BYTE) - 1)) + 1;

    if (maximumValue < 0)
    {
        maximumValue = -maximumValue;
    }
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

template <class T>
int sorting_algorithms<T>::merge(int startIndex, int middleIndex, int endIndex)
{
    int inversions = 0, lengths[] = { middleIndex - startIndex + 1, endIndex - middleIndex };
    T leftSubArray[lengths[0] + 1], rightSubArray[lengths[1] + 1];

    leftSubArray[lengths[0]] = rightSubArray[lengths[1]] = maximumValue;

    memcpy(leftSubArray, arrayToSort + startIndex, lengths[0] * sizeof(T));
    memcpy(rightSubArray, arrayToSort + middleIndex + 1, lengths[1] * sizeof(T));

    for (int i = startIndex, j = 0, k = 0; i <= endIndex; i++)
    {
        if (leftSubArray[j] < rightSubArray[k])
        {
            arrayToSort[i] = leftSubArray[j];

            j++;
        }
        else
        {
            arrayToSort[i] = rightSubArray[k];
            inversions += lengths[0] - j + 1;

            k++;
        }
    }

    return inversions;
}

template <class T>
int sorting_algorithms<T>::merge_sort(int startIndex, int endIndex)
{
    if (startIndex < endIndex)
    {
        int inversions = 0, middleIndex = (startIndex + endIndex) / 2;

        inversions += merge_sort(startIndex, middleIndex);
        inversions += merge_sort(middleIndex + 1, endIndex);
        inversions += merge(startIndex, middleIndex, endIndex);

        return inversions;
    }

    return -1;
}

template <class T>
int sorting_algorithms<T>::merge_sort()
{
    return merge_sort(0, arrayLength - 1);
}
