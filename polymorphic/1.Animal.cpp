/*************************************************************************
	> File Name: 1.Animal.cpp
	> Author: 
	> Mail: 
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(test1)

class Animal {
public:
    void run() {
        cout << "I don't know how to run!" << endl;
        return ;
    }
};

class Cat : public Animal {
public:
    void run() {
        cout << "I can run with with four legs" << endl;
        return ;
    }
};

int main() {
    Cat a;
    Animal &b = a;
    Animal *c = &b;
    a.run(); // let this cat go
    b.run(); // let this animal go
    c->run(); // let this animal go
    return 0;
}

ENDS(test1)

BEGINS(test2)

class Animal {
public:
    virtual void run() {
        cout << "I don't know how to run!" << endl;
        return ;
    }
    virtual void foo() {
        cout << "foo function" << endl;
        return ;
    }
};

class Cat : public Animal {
public:
    void run() override {
        cout << "I can run with with four legs" << endl;
        return ;
    }
    void foo() override {
        cout << "f00 function" << endl;
        return ;
    }
};


int main() {
    Cat a;
    Animal &b = a;
    Animal *c = &b;
    a.run(); // let this cat go
    b.run(); // let this animal go
    c->run(); // let this animal go
    return 0;
}

ENDS(test2)

BEGINS(test3)

class Animal {
public:
    virtual void run() {
        cout << "I don't know how to run!" << endl;
        return ;
    }
    virtual void foo() {
        cout << "foo function" << endl;
        return ;
    }
};

class Cat : public Animal {
public:
    void run() override {
        cout << "I can run with with four legs" << endl;
        return ;
    }
    void foo() override {
        cout << "f00 function" << endl;
        return ;
    }
};

class Human : public Animal {
public:
    void run() override {
        cout << "I can run with four legs" << endl;
        return ;
    }
};

class Bird : public Animal {
public:
    void run() override {
        cout << "i can fly" << endl;
    }
};

int main() {
    srand(time(0));
    Animal *arr[10];
    for (int i = 0; i < 10; i++) {
        switch (rand() % 3) {
            case 0: arr[i] = new Cat(); break;
            case 1: arr[i] = new Human(); break;
            case 2: arr[i] = new Bird(); break;
        }
    }
    for (int i = 0; i < 10; i++) {
        arr[i]->run();
    }
    return 0;
}

ENDS(test3)

BEGINS(test4)

class Animal {
public:
    virtual void run() {
        cout << "I don't know how to run!" << endl;
        return ;
    }
    virtual void foo() {
        cout << "foo function" << endl;
        return ;
    }
    virtual ~Animal() {
        cout << "Animal destructor" << endl;
    }
};

class Cat : public Animal {
public:
    void run() override {
        cout << "I can run with with four legs" << endl;
        return ;
    }
    void foo() override {
        cout << "f00 function" << endl;
        return ;
    }
    ~Cat() {
        cout << "Cat destructor" << endl;
    }
};

class Human : public Animal {
public:
    void run() override {
        cout << "I can run with four legs" << endl;
        return ;
    }
    ~Human() {
        cout << "human destructor" << endl;
    }
};

class Bird : public Animal {
public:
    void run() override {
        cout << "i can fly" << endl;
    }
    ~Bird() {
        cout << "bird destructor" << endl;
    }
};

int main() {
    srand(time(0));
    Animal *p;
    switch (rand() % 3) {
        case 0: p = new Cat(); break;
        case 1: p = new Human(); break;
        case 2: p = new Bird(); break;
    }
    p->run();
    delete p;
    return 0;
}

ENDS(test4)

BEGINS(test5)

class Animal {
public:
    virtual void run() = 0;
};

class Cat : public Animal {
public:
    void run() override {
        cout << "I can run with four legs" << endl;
        return ;
    }
};

int main() {
    
    return 0;
}

ENDS(test5)

int main() {
    //test1::main();
    //test2::main();
    //test3::main();
    test4::main();

    return 0;
}
