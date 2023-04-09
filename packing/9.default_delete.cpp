/*************************************************************************
	> File Name: 9.default_delete.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Apr 2023 03:43:02 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

class A {
public:
    A() = default;
    A(const A &) = delete;
};

int main() {

    return 0;
}
