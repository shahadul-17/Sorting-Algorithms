#include "sorting_algorithms.h"

template <class Type>
sorting_algorithms<Type>::sorting_algorithms(int arrayLength, Type *arrayToSort)
{
    this->arrayLength = arrayLength;
    this->arrayToSort = arrayToSort;

    maximumValue = (Type)pow(2.0, (double)((sizeof(Type) * BYTE) - 1)) + 1;

    if (maximumValue < 0)
    {
        maximumValue = -maximumValue;
    }
}

template <class Type>
sorting_algorithms<Type>::~sorting_algorithms()
{
    arrayToSort = 0;
}

template <class Type>
void sorting_algorithms<Type>::bubble_sort()
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

template <class Type>
void sorting_algorithms<Type>::insertion_sort()
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

template <class Type>
int sorting_algorithms<Type>::merge(int startIndex, int middleIndex, int endIndex)
{
    int inversions = 0, lengths[] = { middleIndex - startIndex + 1, endIndex - middleIndex };
    Type leftSubArray[lengths[0] + 1], rightSubArray[lengths[1] + 1];

    leftSubArray[lengths[0]] = rightSubArray[lengths[1]] = maximumValue;

    memcpy(leftSubArray, arrayToSort + startIndex, lengths[0] * sizeof(Type));
    memcpy(rightSubArray, arrayToSort + middleIndex + 1, lengths[1] * sizeof(Type));

    for (int i = startIndex, j = 0, k = 0; i <= endIndex; i++)
    {
        if (leftSubArray[j] <= rightSubArray[k])
        {
            arrayToSort[i] = leftSubArray[j];

            j++;
        }
        else
        {
            arrayToSort[i] = rightSubArray[k];
            inversions += lengths[0] - j;

            k++;
        }
    }

    return inversions;
}

template <class Type>
int sorting_algorithms<Type>::merge_sort(int startIndex, int endIndex)
{
    if (startIndex < endIndex)
    {
        int inversions = 0, middleIndex = (startIndex + endIndex) / 2;

        inversions += merge_sort(startIndex, middleIndex);
        inversions += merge_sort(middleIndex + 1, endIndex);
        inversions += merge(startIndex, middleIndex, endIndex);

        return inversions;
    }

    return 0;
}

template <class Type>
int sorting_algorithms<Type>::merge_sort()
{
    return merge_sort(0, arrayLength - 1);
}

template <class Type>
void sorting_algorithms<Type>::swap(int firstIndex, int secondIndex)
{
    Type temp = arrayToSort[firstIndex];
    arrayToSort[firstIndex] = arrayToSort[secondIndex];
    arrayToSort[secondIndex] = temp;
}

template <class Type>
int sorting_algorithms<Type>::partition(int startIndex, int endIndex)
{
    int partitioningIndex = startIndex - 1, pivot = arrayToSort[endIndex];

    for (int i = startIndex; i < endIndex; i++)
    {
        if (pivot >= arrayToSort[i])
        {
            partitioningIndex++;

            swap(i, partitioningIndex);
        }
    }

    partitioningIndex++;

    swap(partitioningIndex, endIndex);

    return partitioningIndex;
}

template <class Type>
void sorting_algorithms<Type>::quick_sort(bool randomize, int startIndex, int endIndex)
{
    if (startIndex < endIndex)
    {
        int partitioningIndex = -1;

        if (randomize)      // if randomize is true, it will generate a random index (pivot) and swap it with the last index...
        {
            srand(time(NULL));

            swap(startIndex + (rand() % (endIndex - startIndex)), endIndex);
        }

        partitioningIndex = partition(startIndex, endIndex);

        quick_sort(randomize, startIndex, partitioningIndex - 1);
        quick_sort(randomize, partitioningIndex + 1, endIndex);
    }
}

template <class Type>
void sorting_algorithms<Type>::multithreaded_quick_sort(ThreadParameter *threadParameter)
{
    if ((*threadParameter).numberOfThreads < 2)
    {
        quick_sort((*threadParameter).randomize, (*threadParameter).startIndex, (*threadParameter).endIndex);
    }
    else if ((*threadParameter).startIndex < (*threadParameter).endIndex)
    {
        if ((*threadParameter).randomize)      // if randomize is true, it will generate a random index (pivot) and swap it with the last index...
        {
            srand(time(NULL));

            swap((*threadParameter).startIndex + (rand() % ((*threadParameter).endIndex - (*threadParameter).startIndex)), (*threadParameter).endIndex);
        }

        int i = 0, partitioningIndex = partition((*threadParameter).startIndex, (*threadParameter).endIndex);

        ThreadParameter *threadParameters = new ThreadParameter[2];

        for (i = 0; i < 2; i++)
        {
            threadParameters[i].randomize = (*threadParameter).randomize;
            threadParameters[i].flag = (*threadParameter).flag;
            threadParameters[i].numberOfThreads = (*threadParameter).numberOfThreads / 2;
            threadParameters[i].sortingAlgorithms = this;
        }

        threadParameters[0].startIndex = (*threadParameter).startIndex;
        threadParameters[0].endIndex = partitioningIndex - 1;
        threadParameters[1].startIndex = partitioningIndex + 1;
        threadParameters[1].endIndex = (*threadParameter).endIndex;

        pthread_t *threads = new pthread_t[2];

        for (i = 0; i < 2; i++)
        {
            pthread_create(&threads[i], NULL, member_function_wrapper, (void *)(&threadParameters[i]));
        }

        for (i = 0; i < 2; i++)     // waiting for both threads to finish...
        {
            pthread_join(threads[i], NULL);
        }

        delete [] threads;
        delete [] threadParameters;
    }
}

template <class Type>
void sorting_algorithms<Type>::quick_sort(bool randomize, bool multithreaded)
{
    if (multithreaded)
    {
        ThreadParameter threadParameter;
        threadParameter.randomize = randomize;
        threadParameter.flag = 1;       // flag == 1 for multithreaded quicksort...
        threadParameter.numberOfThreads = 8;        // number of threads could be changed...
        threadParameter.startIndex = 0;
        threadParameter.endIndex = arrayLength - 1;

        member_function_wrapper((void *)(&threadParameter));
    }
    else
    {
        quick_sort(randomize, 0, arrayLength - 1);
    }
}

template <class Type>
void * sorting_algorithms<Type>::member_function_wrapper(void *argument)
{
    ThreadParameter *threadParameter = (ThreadParameter *)argument;

    switch ((*threadParameter).flag)
    {
    case 0:
        break;
    case 1:
        ((*threadParameter).sortingAlgorithms)->multithreaded_quick_sort(threadParameter);

        break;
    }

    return NULL;
}
