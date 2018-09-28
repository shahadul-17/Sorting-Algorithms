#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <iostream>

using namespace std;

template <class T>
class sorting_algorithms
{
    public:
        sorting_algorithms(int, T *);
        virtual ~sorting_algorithms();
        void bubble_sort();
        void insertion_sort();

    protected:

    private:
        int arrayLength;
        T *arrayToSort;
};

#endif // SORTING_ALGORITHMS_H
