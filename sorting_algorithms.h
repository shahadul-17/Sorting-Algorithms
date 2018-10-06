#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <cstring>
#include <cmath>

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

    protected:

    private:
        int arrayLength;
        T maximumValue, *arrayToSort;

        int merge(int, int, int);
        int merge_sort(int, int);
};

#endif // SORTING_ALGORITHMS_H
