#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <pthread.h>

#define BYTE 8

template <class Type>
class sorting_algorithms
{
    public:
        sorting_algorithms(int, Type *);
        virtual ~sorting_algorithms();
        void bubble_sort();
        void insertion_sort();
        int merge_sort();
        void quick_sort(bool, bool);

    private:
        typedef struct ThreadParameter
        {
            bool randomize;     // for quicksort algorithm...
            unsigned char flag;
            int numberOfThreads, startIndex, endIndex;

            sorting_algorithms *sortingAlgorithms;
        } ThreadParameter;

        int arrayLength;
        Type maximumValue, *arrayToSort;

        int merge(int, int, int);
        int merge_sort(int, int);

        void swap(int, int);
        int partition(int, int);
        void quick_sort(bool, int, int);
        void multithreaded_quick_sort(ThreadParameter *);
        static void * member_function_wrapper(void *);
};

#endif // SORTING_ALGORITHMS_H
