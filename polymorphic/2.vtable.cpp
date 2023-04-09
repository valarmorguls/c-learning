/*************************************************************************
	> File Name: 2.vtable.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 06 Apr 2023 09:49:24 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(test1)

class Base {
public:
    virtual ~Base() {}
}; 

class A : public Base {
public:
    int x;
};

class B {
public:
    int x;
};

int main() {
    cout << "sizeof(Base) = " << sizeof(Base) << endl;
    cout << "sizeof(A)    = " << sizeof(A) << endl;
    cout << "sizeof(B)    = " << sizeof(B) << endl;
    return 0; 
}

//Base 类头八个字节存储的Base的地址
//A类存储的虚函数表的地址不一样

ENDS(test1)

BEGINS(test2)

class Base {
public:
    virtual void func1() {
        cout << "Base func1" << endl;
    }
    virtual void func2() {
        cout << "Base func2" << endl;
    }
    virtual void func3() {
        cout << "Base func3" << endl;
    }
    virtual ~Base() {}
}; 

class A : public Base {
public:
    void func2() override {
        cout << "A func2" << endl;
        return ;
    }
    int x;
};

class B : public Base{
public:
    void func1() override {
        cout << "B func1" << endl;
    }
    void func3() override {
        cout << "B func3" << endl; 
    }
    int x;
};

typedef void (*func)();

int main() {
    A a;
    B b;
    a.func1();
    a.func2();
    a.func3();
    b.func1();
    b.func2();
    b.func3();
    ((func **)(&a))[0][1]();
    //((func **)(&a))[0][0] = ((func **)(&b))[0][0];
    //((func **)(&a))[0][0]();
    swap(((func **)(&a))[0], ((func **)(&b))[0]);
    ((func **)(&a))[0][0]();
    ((func **)(&a))[0][1]();
    ((func **)(&a))[0][2]();
    return 0; 
}

//Base 类头八个字节存储的Base的地址
//A类存储的虚函数表的地址不一样

ENDS(test2)

BEGINS(test3)

class Base {
public:
    virtual void func(int x) {
        cout << this << " class Base " << x << endl;
    }
    virtual ~Base() {}
};

class A : public Base {
public:
    void func(int x) override {
        cout << "this->x = " << this->x << endl;
        cout << this << " class A " << x << endl;
        return ;
    }
    int x;
};

typedef void (*func)(void *, int);

int main() {
    A a, b;
    a.x = 1000;
    b.x = 10000;
    a.func(2);
    ((func **)(&a))[0][0](&a, 123);
    ((func **)(&a))[0][0](&b, 123);
    return 0;
}

ENDS(test3)

int main() {
    //test1::main();
    //test2::main();
    test3::main();
    return 0;
}
