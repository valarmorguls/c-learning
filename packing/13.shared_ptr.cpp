/*************************************************************************
	> File Name: 13.shared_ptr.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Apr 2023 10:02:11 AM CST
 ************************************************************************/

#include <iostream>
#include <memory>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(test1)

class A {
public:
    A() {
        cout << "default constructor" << endl;
    }
    ~A() {
        cout << "destructor" << endl;
    }

};

int main() {
    //A *p = new A();
    //delete p;
    shared_ptr<A> p = make_shared<A>();
    cout << "p.use_count = " << p.use_count() << endl;
    shared_ptr<A> q = p;
    cout << "p.use_count = " << p.use_count() << endl;
    cout << "q.use_count = " << q.use_count() << endl;
    p = nullptr;
    cout << "q.use_count = " << q.use_count() << endl;
    q = nullptr;
    cout << "q.use_count = " << q.use_count() << endl;
    cout << "end main" << endl;
    return 0;
}

ENDS(test1)

BEGINS(test2)

class A {
public:
    A() {
        cout << "default constructor" << endl;
    }
    ~A() {
        cout << "destructor" << endl;
    }
    shared_ptr<A> p;
};

int main() {
    shared_ptr<A> p = make_shared<A>();
    shared_ptr<A> q = make_shared<A>();
    p->p = q;
    q->p = p;
    cout << "p.use_count = " << p.use_count() << endl;
    cout << "q.use_count = " << q.use_count() << endl;
    p = nullptr;
    q = nullptr;
    cout << "p.use_count = " << p.use_count() << endl;
    cout << "q.use_count = " << q.use_count() << endl;
    cout << "end main" << endl;
    return 0;
}

ENDS(test2)

BEGINS(test3)

class A {
public:
    A() {
        cout << "default constructor" << endl;
    }
    int x, y;
    ~A() {
        cout << "destructor" << endl;
    }
    shared_ptr<A> p;
};

class ptr_data {
public:
    ptr_data(A *ptr, int *cnt = nullptr) 
    : ptr(ptr), cnt(cnt) {
        if (this->cnt == nullptr) this->cnt = new int(1);
    }
    void increase_one() {
        *cnt += 1;
        return ;
    }
    void decrease_one() const {
        *cnt -= 1;
        if (*cnt == 0) delete ptr;
        return ;
    }

    bool operator==(const ptr_data &p) const {
        return p.ptr == ptr && p.cnt == cnt;
    }
    ~ptr_data() {
        decrease_one();
        if (*cnt == 0) delete cnt;
    }

    A *ptr;
    int *cnt;
};

class shared_ptr {
public:
    shared_ptr(A *ptr) : p(ptr) {}
    shared_ptr(const shared_ptr &p) : p(p.p) {
        this->p.increase_one();
    }
    shared_ptr &operator=(const shared_ptr &obj) {
        if (obj.p == p) return *this;
        p.decrease_one();
        p = obj.p;
        p.increase_one();
        return *this;
    }
    A *operator->() {
        return p.ptr; 
    }
    A &operator*() {
        return *(p.ptr);
    }
    int use_count() { return *(p.cnt); }
    ~shared_ptr() {
        p.decrease_one();
    }
private:
    ptr_data p; 
};

shared_ptr make_shared() {
    return shared_ptr(new A()); 
}

ostream &operator<<(ostream &out, const A &a) {
    out << "class A : " << a.x << "," << a.y << endl;
    return out;
}

int main() {
    //A *p = new A();
    //delete p;
    shared_ptr p = make_shared();
    p->x = 3, p->y = 4;
    cout << *p << endl;
    cout << "p.use_count = " << p.use_count() << endl;
    shared_ptr q = p;
    cout << "p.use_count = " << p.use_count() << endl;
    cout << "q.use_count = " << q.use_count() << endl;
    p = nullptr;
    cout << "q.use_count = " << q.use_count() << endl;
    q = nullptr;
    cout << "q.use_count = " << q.use_count() << endl;
    cout << "end main" << endl;
    return 0;
}

ENDS(test3)

int main() {
    //test1::main(); 
    //test2::main();
    test3::main();
    return 0;
}
