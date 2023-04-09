/*************************************************************************
	> File Name: 12.operator.cpp
	> Author: 
	> Mail: 
 ************************************************************************/

#include <iostream>
#include <functional>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(haizei)

class Point;

ENDS(haizei)


BEGINS(array_object)

class Array {
public:
    Array(int n = 100) : n(n), data(new int[n]){}
    int &operator[](int ind) { return data[ind]; }
    int &operator[](const char *s) {
        int ind = atoi(s);
        return data[ind];
    }
    int &operator[](const haizei::Point &a);
    const int &operator[](int ind) const { return data[ind]; }
private:
    int n;
    int *data;
};

ENDS(array_object)


BEGINS(haizei)

class Point {
public:
    Point(int x, int y) : x(x), y(y) {
        z1 = rand() % 100;
        z2 = z1 + 1;
        z3 = z2 + 1;
        cout << this << " rand value : " << z1 << endl;
    }
    void output() {
        cout << "inner : " << x << " " << y << endl;
    }
    Point operator+(int x) const  {
        return Point(this->x + x, this->y + x);
    }
    Point &operator+=(int x) {
        this->x += x;
        this->y += x;
        return *this;
    }
    Point operator++(int) {
        Point ret(*this);
        this->x += 1;
        this->y += 1;
        return ret;
    }
    Point &operator++() {
        this->x += 1;
        this->y += 1;
        return *this;
    }
    friend void output(Point &a);
    friend ostream &operator<<(ostream &out, const Point &p);
    friend Point operator+(const Point &, const Point &);
    friend int &array_object::Array::operator[](const Point &);
    int z1, z2, z3;
private:
    int x, y;
};

void output(Point &a) {
    cout << "outer : " << a.x << " " << a.y << endl;
    return ;
}

ostream &operator<<(ostream &out, const Point &p) {
    out << "Point(" << p.x << ", " << p.y << ")";
    return out;
}

Point operator+(const Point &a, const Point &b) {
    return Point (a.x + b.x, a.y + b.y);
}

ENDS(haizei)

BEGINS(test1)
using namespace haizei;

int main() {
    srand(time(0));
    Point p(3, 4), q(5, 6), *pp = &p; 
    p.output();
    output(p);
    cout << p << endl;
    cout << (p + q) << endl;
    cout << (p + (p + q)) << endl;
    //加上const的原因， 兼容所有的对象
    cout << (p + 5) << endl; // p + t => p.operator+(5)
    cout << p << endl;
    const Point z(100, 1000);
    cout << (z + 6)  << endl;

    int Point::* px = &Point::z1; //逻辑地址
    cout << pp->*px << endl;
    px = &Point::z2;
    cout << pp->*px << endl;
    px = &Point::z3;
    cout << pp->*px << endl;
    return 0;
}

ENDS(test1)

BEGINS(test2)

using namespace haizei;

int main() {
    //+=
    Point p(3, 4);
    cout << ((p += 5) += 6) << endl;
    //++
    cout << "p++ = " << (p++) << endl;;
    cout << "p = " << p << endl;
    //++p;
    cout << "++p =" << (++p) << endl;;
    cout << "p = " << p << endl;
    int n = 45;
    (++n)++;
    cout << n << endl;
    (++p)++;
    cout << "p = " << p << endl;
    return 0;
}

ENDS(test2)

BEGINS(array_object)

using namespace haizei;

int &Array::operator[](const haizei::Point &a) {
    return data[a.x + a.y];
}

int main() {
    Array arr;
    Point p(3, 4);
    //访问的是具体的对象
    for (int i = 0; i < 10; i++) arr[i] = i;
    cout << arr["0"] << arr["1"] << arr["2"] << endl;
    cout << arr[p] << endl;
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    const Array arr2;
    for (int i = 0; i < 10; i++) {
        cout << &arr[i] << " ";
    }
    for (int i = 0; i < 10; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    return 0;
}

ENDS(array_object)

BEGINS(function_object)

class Function {
public:
    int operator()(int a, int b) {
        cout << "inner class : ";
        return a + b;
    }
private:

};

int func1(int a, int b) {
    cout << "inner func1 : ";
    return a + b;
}

int main() {
    Function func;
    cout << func(3, 4) << endl;
    int (*p)(int, int) = func1;
    cout << p(3, 4) << endl;
    function<int(int, int)> q;
    q = func1;
    cout << "q pointer : " << q(3, 4) << endl;
    q = func;
    cout << "q pointer : " << q(3, 4) << endl;
    cout << greater<int>()(3, 4) << endl;
    cout << greater<int>()(4, 3) << endl;
    return 0;
}

ENDS(function_object)

BEGINS(pointer_object)

struct A {
    A() : x(0), y(0) {}
    int x, y;
};

class Pointer {
public:
    Pointer(A *p = nullptr) : p(p) {}
    A *operator->() { return p; }
    A *operator->() const { return p; }
    A &operator*() { return *p; }
    A &operator*() const { return *p; }
    A *operator+(int n) { return p + n; }
    A *operator+(int n) const { return p + n; }
    A *operator-(int n) { return p - n; }
    A *operator-(int n) const { return p - n; }
    int operator-(const Pointer &a) { return this->p - a.p; }  
    int operator-(const Pointer &a) const { return this->p - a.p; }  
    A &operator[](int ind) { return *(p + ind); }
    A &operator[](int ind) const { return *(p + ind); }
    friend ostream &operator<<(ostream &out, const Pointer &p);

private:
    A *p;
};

ostream &operator<<(ostream &out, const A &a) {
    out << a.x << " " << a.y;
    return out;
}


ostream &operator<<(ostream &out, const Pointer &p) {
    out << p.p;
    return out;
}

int main() {
    A a, b;   
    Pointer p = &a, q = &b;
    cout << a << endl;
    p->x = 3;
    p->y = 4;
    cout << a << endl;
    cout << *p << endl;
    cout << p << endl;
    cout << (p + 1) << endl;
    cout << (p - 1) << endl;
    cout << (p - q) << endl; //TODO
    cout << p[0] << endl; //TODO

    const Pointer cp = &a;
    cout << *cp << endl; //TODO
    cout << (cp + 1) << endl;
    cout << (cp - 1) << endl; //TODO
    cout << cp[0] << endl;
    return 0;
}

ENDS(pointer_object)

int main() {
    //test1::main(); 
    //test2::main();
    //array_object::main();
    //function_object::main();
    pointer_object::main();
    return 0;
}
