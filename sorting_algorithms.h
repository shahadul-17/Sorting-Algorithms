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
        int merge_sort(bool);
        void quick_sort(bool, bool);

    private:
        typedef struct ThreadParameter
        {
            bool randomize;     // for quicksort algorithm...
            unsigned char flag;     // flag is used by "member function wrapper" to identify the caller (sorting algorithm)...
            int inversions, numberOfThreads, startIndex, endIndex;      // inversions variable is used for multithreaded merge sort...

            sorting_algorithms *sortingAlgorithms;
        } ThreadParameter;

        int arrayLength;
        Type maximumValue, *arrayToSort;

        int merge(int, int, int);
        int merge_sort(int, int);
        int multithreaded_merge_sort(ThreadParameter *);

        void swap(int, int);
        int partition(int, int);
        void quick_sort(bool, int, int);
        void multithreaded_quick_sort(ThreadParameter *);

        static void * member_function_wrapper(void *);      // a wrapper around member function to create POSIX thread...
};

#endif // SORTING_ALGORITHMS_H
