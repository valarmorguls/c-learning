/*************************************************************************
	> File Name: 2.succeed_copy.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Apr 2023 03:21:01 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(test1)

class ATTR_BASE {
public:
    ATTR_BASE(string name) : name(name) {
        cout << " construct : " << name << endl;
    }
    ATTR_BASE(const ATTR_BASE &a) : name(a.name) {
        cout << "default copy constructor : " << name << endl;
    }
    ATTR_BASE &operator=(const ATTR_BASE &a) {
        name = a.name;
        cout << "operator= : " << name << endl;
        return *this;
    }
    ~ATTR_BASE() {
        cout << "destructor :" << name << endl;
    }
    string name;
};

class ATTR1 : public ATTR_BASE {
public:
    ATTR1(string name = "none") : ATTR_BASE(name) {}
};

class ATTR2 : public ATTR_BASE {
public:
    ATTR2(string name = "none") : ATTR_BASE(name) {}
};

class Base {
public:
    Base() : attr1("attr1 in Base"), attr2("attr2 in Base") {
        cout << "Base constructor done" << endl;
    }
    Base(const Base &b) : attr1(b.attr1), attr2(b.attr2) {
        cout << "Base copy constructor done" << endl;
    }
    Base &operator=(const Base &b) {
        attr1 = b.attr1;
        attr2 = b.attr2;
        cout << "Base operator = done" << endl;
        return *this;
    }
    ~Base() {
        cout << "Base destructor done" << endl;
    }
private:
    ATTR1 attr1;
    ATTR2 attr2;
};

class A : public Base {
public:
    A() : attr1("attr1 in A"), attr2("attr2 in A") {
        cout << "A constructor done" << endl;
    } 
    A(const A &a) : Base(a), attr1(a.attr1), attr2(a.attr2) {
        cout << "A copy constructor done" << endl;    
    }
    A &operator=(const A &a) {
        //显示调用父类的默认的 default operator=
        this->Base::operator=(a);
        attr1 = a.attr1;
        attr2 = a.attr2;
        cout << "A operator = done" << endl; 
        return *this;
    }
    ~A() {
        cout << "A destructor done" << endl;
    }
private:
    ATTR1 attr1;
    ATTR2 attr2;
};

int main() {
    A a; 
    cout << "======== default constructor ===========" << endl << endl;
    A b(a);
    cout << "======== copy constructor ============" << endl << endl;
    b = a;
    cout << "======== opeartor assign  ============" << endl << endl;
    return 0;
}

ENDS(test1)

int main() {
    test1::main();
    return 0;
}
