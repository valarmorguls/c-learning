/*************************************************************************
	> File Name: 3.constructor.cpp
	> Author: 
	> Mail: 
 ************************************************************************/

#include <iostream>
using namespace std;

void add_one(int &n) {
    n += 1;
    return ;
}

int main() {
    int a = 1, b = 3;
    cout << "normal param : " << a << " " << b << endl;
    add_one(a);
    add_one(b);
    cout << a << " " << b << endl;
    return 0;
}
