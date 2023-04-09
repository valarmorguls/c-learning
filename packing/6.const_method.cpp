/*************************************************************************
	> File Name: 6.const_method.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Apr 2023 11:03:02 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(test1)

class A {
public:
    A() { cout << "changliaotianxia" << endl; }
    void say() const {
        cout << x << endl;
    }
    int x;
};


void main() {
    const A a;
    a.say();
    return ;
}

ENDS(test1)

int main() {
    test1::main(); 
    return 0;
}
