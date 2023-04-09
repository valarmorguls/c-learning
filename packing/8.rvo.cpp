/*************************************************************************
	> File Name: 8.rvo.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Apr 2023 03:33:34 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

class A {
public:
    A() {
        cout << this << " default constructor" << endl;
    }
    A(int x) {
        cout << this << " param constructor" << endl;
    }
    A (const A &a) {
        cout << this << " deep constructor" << endl;
    }
};

A func() {
    A temp(3);
    cout << "object temp : " << &temp << endl;
    return temp;
}

int main() {
    A a = func(); 
    cout << "object a : " << &a << endl;
    return 0;
}
