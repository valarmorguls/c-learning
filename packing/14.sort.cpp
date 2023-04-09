/*************************************************************************
	> File Name: 14.sort.cpp
	> Author: 
	> Mail: 
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(test1)

bool cmp1(int a, int b) {
    return a > b;
}

void output(int *first, int *last, const char *msg) {
    cout << msg;
    while (first != last) {
        cout << *first << " ";
        ++first;
    }
    cout << endl;
    return ;
}

class CMP {
public:
    bool operator()(int a, int b) {
        return a < b;
    }
};

int main() {
    int arr[100], n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];
    sort(arr, arr + n);
    output(arr, arr + n, "none : ");

    sort(arr, arr + n, cmp1);
    output(arr, arr + n, "cmp1 : ");

    CMP cmp2;
    sort(arr, arr + n, cmp2);
    output(arr, arr + n, "cmp2 : ");
    return 0; 
}

ENDS(test1)

BEGINS(test2)

bool cmp1(int a, int b) {
    return a > b;
}

void output(int *first, int *last, const char *msg) {
    cout << msg;
    while (first != last) {
        cout << *first << " ";
        ++first;
    }
    cout << endl;
    return ;
}

class CMP {
public:
    bool operator()(int a, int b) {
        return a < b;
    }
};

/*
void sort(int *first, int *last, function<bool(int, int)> cmp = less<int>()) {
    if (first >= last) return ;
    int *x = first, *y = last - 1, z = *first;
    while (x < y) {
        while (x < y && cmp(z, *y)) --y;
        if (x < y) *(x++) = *y;
        while (x < y && cmp(*x, z)) ++x;
        if (x < y) *(y--) = *x;
    }
    *x = z;
    sort(first, x, cmp);
    sort(x + 1, last, cmp);
    return ;
}
*/

const int threshold = 16;

void intro_loop(int *first, int *last, function<bool(int, int)> cmp = less<int>()) {
    while (last - first > threshold) {
        int *x = first, *y = last - 1, z = *first;
        do {
            while (cmp(*x, z)) ++x;
            while (cmp(z, *y)) --y;
            if (x <= y) {
                swap(*x, *y);
                ++x, --y;
            }
        } while(x <= y);
        sort(x, last, cmp);
        last = y + 1;
    }
    return ;
}

void insert_sort(
    int *first, int *last,
    function<bool(int, int)> cmp = less<int>()
) {
    int *ind = first;
    for (int *x = first + 1; x < last; ++x) {
        if (cmp(*x, *ind)) ind = x;
    }
    while (ind != first) {
        swap(*ind, *(ind - 1));
        --ind;
    }
    for (int *x = first + 2; x < last; ++x) {
        int *j = x;
        while (cmp(*j, *(j - 1))) {
            swap(*j, *(j - 1));
            --j;
        }
    }
    return ;
}

void sort(int *first, int *last, function<bool(int, int)> cmp = less<int>()) {
    intro_loop(first, last, cmp);
    insert_sort(first, last, cmp);
}

int main() {
    int arr[100], n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];
    sort(arr, arr + n);
    output(arr, arr + n, "none : ");

    sort(arr, arr + n, cmp1);
    output(arr, arr + n, "cmp1 : ");

    CMP cmp2;
    sort(arr, arr + n, cmp2);
    output(arr, arr + n, "cmp2 : ");
    return 0; 
}

ENDS(test2)

BEGINS(test3)

bool cmp1(int a, int b) {
    return a > b;
}

void output(int *first, int *last, const char *msg) {
    cout << msg;
    while (first != last) {
        cout << *first << " ";
        ++first;
    }
    cout << endl;
    return ;
}

class CMP {
public:
    bool operator()(int a, int b) {
        return a < b;
    }
};

/*
void sort(int *first, int *last, function<bool(int, int)> cmp = less<int>()) {
    if (first >= last) return ;
    int *x = first, *y = last - 1, z = *first;
    while (x < y) {
        while (x < y && cmp(z, *y)) --y;
        if (x < y) *(x++) = *y;
        while (x < y && cmp(*x, z)) ++x;
        if (x < y) *(y--) = *x;
    }
    *x = z;
    sort(first, x, cmp);
    sort(x + 1, last, cmp);
    return ;
}
*/

const int threshold = 16;

class RandomIter {
public:
    RandomIter(int *ptr) : ptr(ptr){}
    int &operator*() { return *ptr; }
    RandomIter operator-(int x) { return RandomIter(ptr - x); }
    RandomIter operator+(int x) { return RandomIter(ptr + x); }
    int operator-(const RandomIter &iter) { return ptr - iter.ptr; }
    RandomIter &operator++() { ++ptr; return *this; }
    RandomIter &operator--() { --ptr; return *this; }
    bool operator<(const RandomIter &iter) const {
        return ptr < iter.ptr;
    }
    bool operator>(const RandomIter &iter) const {
        return iter < *this;
    }
    bool operator<=(const RandomIter &iter) const {
        return !(iter < *this);
    }
    bool operator>=(const RandomIter &iter) const {
        return !(*this < iter);
    }
    bool operator==(const RandomIter &iter) const {
        return !(*this < iter) && !(iter < *this);  
    }
    bool operator!=(const RandomIter &iter) const {
        return !(*this == iter);
    }

private:
    int *ptr;
};

void intro_loop(RandomIter first, RandomIter last, function<bool(int, int)> cmp = less<int>()) {
    while (last - first > threshold) {
        RandomIter x = first, y = last - 1; 
        int z = *first;
        do {
            while (cmp(*x, z)) ++x;
            while (cmp(z, *y)) --y;
            if (x <= y) {
                swap(*x, *y);
                ++x, --y;
            }
        } while(x <= y);
        intro_loop(x, last, cmp);
        last = y + 1;
    }
    return ;
}

void insert_sort(
    RandomIter first, RandomIter last,
    function<bool(int, int)> cmp = less<int>()
) {
    RandomIter ind = first;
    for (RandomIter x = first + 1; x < last; ++x) {
        if (cmp(*x, *ind)) ind = x;
    }
    while (ind != first) {
        swap(*ind, *(ind - 1));
        --ind;
    }
    for (RandomIter x = first + 2; x < last; ++x) {
        RandomIter j = x;
        while (cmp(*j, *(j - 1))) {
            swap(*j, *(j - 1));
            --j;
        }
    }
    return ;
}

void sort(RandomIter first, RandomIter last, function<bool(int, int)> cmp = less<int>()) {
    intro_loop(first, last, cmp);
    insert_sort(first, last, cmp);
}

int main() {
    int arr[100], n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];
    sort(arr, arr + n);
    output(arr, arr + n, "none : ");

    sort(arr, arr + n, cmp1);
    output(arr, arr + n, "cmp1 : ");

    CMP cmp2;
    sort(arr, arr + n, cmp2);
    output(arr, arr + n, "cmp2 : ");
    return 0; 
}

ENDS(test3)

int main() {
    //test1::main(); 
    //test2::main();
    test3::main();
    return 0;
}
