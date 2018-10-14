#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>

#define BYTE 8

template <class T>
class sorting_algorithms
{
    public:
        sorting_algorithms(int, T *);
        virtual ~sorting_algorithms();
        void bubble_sort();
        void insertion_sort();
        int merge_sort();
        void quick_sort(bool);

    protected:

    private:
        int arrayLength;
        T maximumValue, *arrayToSort;

        int merge(int, int, int);
        int merge_sort(int, int);

        void swap(int, int);
        int partition(int, int);
        void quick_sort(bool, int, int);
};

#endif // SORTING_ALGORITHMS_H
