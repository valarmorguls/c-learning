/*************************************************************************
	> File Name: 4.constructor.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Apr 2023 09:25:34 AM CST
 ************************************************************************/

#include <iostream>
using namespace std;

class A {
public:
    //必须含有默认构造
    A(int x) : x(x) {
        cout << this <<  "Class A : " << x << endl;
    }
    A(const A &a) {
        cout << this << " copy from " << &a.x << endl;
    }
    void operator=(const A &a) {
        cout << this << " assign from " << &a << endl;
        return ;
    }
    int x;
};

class B1 {
public:
    B1() = default;
    B1(const B1 &) {
        cout << "B1 copy constructor" << endl;
    }
};

class B2 {
public:
    B2() = default;
    B2(const B2 &) {
        cout << "B2 copy constructor" << endl;
    }
};

class B3 {
public:
    B3() = default;
    B3(const B3 &) {
        cout << "B3 copy constructor" << endl;
    }
};

class B {
public:
    B1 b1;
    B2 b2;
    B3 b3;
};

//初始化列表规定了每一个成员属性的构造行为
class Data {
public:
    Data() : __x(100), __y(100), a(100) {
        //this->__x = 0;
        //this->__y = 0;
        cout << "default constructor" << endl;
    }
    int X() { return __x; }
    int Y() { return __y; }
    ~Data() {
        cout << "destructor" << endl;    
    }    
private:
    int __x, __y;
    A a;
};

int main() {
    B b1;
    B b2 = b1;

    Data d;
    cout << d.X() << " " << d.Y() << endl;
    A a = 45; // 2 constructor
    cout << "address a:" << &a << endl;
    a = 78; 
    return 0;
}
