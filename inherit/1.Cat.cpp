/*************************************************************************
	> File Name: 1.Cat.cpp
	> Author: 
	> Mail: 
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x { // begin of x
#define ENDS(x) } // end of namespace

BEGINS(test1)

class Base {
public:
    int x;
protected:
    int y;
private:
    int z;
};

class public_Base : public Base {
public:
    void main() {
        x = 2;    // ok, x public
        y = 3;    // ok, y protected
        // z = 4; // no, z private
    } 
};

class protected_base : protected Base {
public:
    void main() {
        x = 2; // ok, x public
        y = 3; // ok, x protected
      //z = 4; // no, z private
    }
};

class private_base : private Base {
public:
    void main() {
        x = 2; //
        y = 3; 
        //z = 4; // no, z private
    }
};

int main() {
    public_Base a;
    a.x = 3;   // yes, public + public    = public;
    //a.y = 4; // no,  public + protected = protected;
    //a.z = 4; // no,  public + private   = private;
    //
    protected_base b;
    //b.x = 3;   // no, protected + public    = protected;
    //b.y = 4;   // no, protected + protected = protected;
    //b.z = 4;   // no, protected + private   = private;

    private_base c;
    //c.x = 3; //no , private + public    = private;   
    //c.y = 4; //no,  private + protected = protected;
    //c.z = 5; //no,  private + private   = private;
    return 0;
}

ENDS(test1)

BEGINS(test2)

class Base {
public:
    Base(string name) : class_name(name) {}
    int x;
    string class_name;
private:
    int y;
};

class A : public Base {
public:
    A() : Base("class_A") {}
};

class B : public Base {
public:
    B() : Base("class_b") {}
}; 

class C : public Base {
public:
    C() : Base("class_c") {}
};

void func(Base &b) {
    cout << "input class : " << b.class_name << endl; 
    return ;
}

int main() {
    A a;
    B b;
    C c;
    func(a);
    func(b);
    func(c);
    cout << "sizeof(Base) = " << sizeof(Base) << endl;   
    cout << "sizeof(A)    = " << sizeof(A) << endl;
    return 0;
}

ENDS(test2)

BEGINS(test3)

class Base {
public:
    Base(string name) : class_name(name) {}
    int x;
    string class_name;
private:
    int y;
};

class A : public Base {
public:
    A() : Base("class_A") {}
};

class B : public Base {
public:
    B() : Base("class_b") {}
}; 

class C : public Base {
public:
    C() : Base("class_c") {}
};

void func(Base *b) {
    cout << "input class : " << b->class_name << endl; 
    return ;
}

int main() {
    //隐式类型转换
    A a;
    B b;
    C c;
    func(&a);
    func(&b);
    func(&c);
    cout << "sizeof(Base) = " << sizeof(Base) << endl;   
    cout << "sizeof(A)    = " << sizeof(A) << endl;
    return 0;
}

ENDS(test3)

BEGINS(test4)

class ATTR_BASE {
public:
    ATTR_BASE(string name) : name(name) {
        cout << " construct : " << name << endl;
    }
    ~ATTR_BASE() {
        cout << "destructor :" << name << endl;
    }
    string name;
};

class ATTR1 : public ATTR_BASE {
public:
    ATTR1(string name) : ATTR_BASE(name) {}
};

class ATTR2 : public ATTR_BASE {
public:
    ATTR2(string name) : ATTR_BASE(name) {}
};

class Base {
public:
    Base() : attr1("attr1 in Base"), attr2("attr2 in Base") {
        cout << "Base constructor done" << endl;
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
    ~A() {
        cout << "A destructor done" << endl;
    }
private:
    ATTR1 attr1;
    ATTR2 attr2;
};

int main() {
    A a; 
    return 0;
}

ENDS(test4)

int main() {
    test1::main();
    //test2::main();
    test4::main();
    return 0;
}
