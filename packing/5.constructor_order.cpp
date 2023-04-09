/*************************************************************************
	> File Name: 5.constructor_order.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Apr 2023 10:33:20 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x)}

BEGINS(test1)

class A {
public:
    A() {
        cout << this << " default constructor" << endl;
    }
    A(int n, int m) : 
        n(n), m(m), 
        arr(nullptr), size(nullptr),
        offset(nullptr) {
        cout << "A(int) constructor" << endl;
    }
    A(int *size, int *offset) : size(size), offset(offset) {
        arr = new int[*size];
        arr += *offset;
        cout << "A(int *size) constructor" << endl;
    }
    ~A() {
        cout << this << " destructor" << endl;
        if (arr == nullptr) return ;
        arr -= *offset;
        delete[] arr;
    }
    int *arr, *size, *offset;
    int n, m;
};

void main() {
    A a(3, 4);
    A b(&a.n, &a.m);
    cout << "&a : " << &a << " &b : " << &b << endl;
    return ;
}

ENDS(test1)

BEGINS(test2)

#define ATTR_CLASS(x) class ATTR_##x { \
public: \
    ATTR_##x() { \
        cout << "ATTR_" #x " default constructor" << endl; \
    } \
    ~ATTR_##x() { \
        cout << "ATTR_" #x " destructor" << endl; \
    } \
}; \

ATTR_CLASS(1);
ATTR_CLASS(2);
ATTR_CLASS(3);
ATTR_CLASS(4);

class A {
public:
    A() {
        cout << "Class A constructor" << endl;
    }
    ~A() {
        cout << "Class A desturctor" << endl;
    }
    ATTR_1 a1;
    ATTR_2 a2;
    ATTR_3 a3;
    ATTR_4 a4;
};

void main() {
    A a;
    return ;
}

ENDS(test2)

int main() {
    test1::main();
    test2::main();
    return 0;
}
