/*************************************************************************
	> File Name: 2.rvalue_move.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 08 Apr 2023 03:19:05 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(test1)

void judge(int &x) {
    cout << "left value" << endl;
    return ;
}

void judge(int &&x) {
    cout << "right value" << endl;
    return ;
}

#define TEST(a) { \
    cout << "judge " << #a << " : "; \
    judge(a); \
}

int main() {
    int n = 123;
    (n += 2) = 1000;
    cout << n << endl;
    TEST(n)
    TEST(n + 1)
    TEST(n++)
    TEST(++n)
    TEST(1 + 2)
    TEST(n += 2)
    return 0;
}

ENDS(test1)

BEGINS(test2)

void judge2(int &x) {
    cout << "(left value - 2) ";
    return ;
}

void judge2(int &&x) {
    cout << "(right value - 2) ";
    return ;
}

void judge(int &x) {
    judge2(x);
    cout << "left value" << endl;
    return ;
}

void judge(int &&x) {
    //judge2(move(x));
    judge2(forward<int &&>(x));
    cout << "right value" << endl;
    return ;
}

#define TEST(a) { \
    cout << "judge " << #a << " : "; \
    judge(a); \
}

int main() {
    int n = 123;
    (n += 2) = 1000;
    cout << n << endl;
    TEST(n)
    TEST(n + 1)
    TEST(n++)
    TEST(++n)
    TEST(1 + 2)
    TEST(n += 2)
    return 0;
}

ENDS(test2)

BEGINS(test3)

class Point;

void judge(Point &x) {
    cout << "left value" << endl;
    return ;
}

void judge(Point &&x) {
    cout << "right value" << endl;
    return ;
}

class Point {
public:
    Point(int x = 0, int y = 0) : __x(x), __y(y) {}
    int x() { return __x; }
    int y() { return __y; }
    Point &operator+=(int d) {
        __x += d;
        __y += d;
        return *this;
    }
    Point operator+(int d) {
        Point p(__x + d, __y + d);
        return p;
    }
private:
    int __x, __y;
};

#define TEST(a) { \
    cout << "judge " << #a << " : "; \
    judge(a); \
}

int main() {
    Point p(3, 4);
    TEST(p);
    TEST(p += 1);
    TEST(p + 1);
    return 0;
}

ENDS(test3)

BEGINS(test4)

class Array {
public:
    Array(int n = 5) : __size(n), data(new int[n]) {
        cout << this << "default constructor" << endl;
    } 
    Array(const Array &a) 
    : __size(a.__size), data(new int[__size]) {
        for (int i = 0; i < __size; i++) {
            data[i] = a[i];
        }
        cout << this << "deep copy constructor " << endl;
        return ;
    }
    //右值才可能绑定右值
    Array(Array &&a) : __size(a.__size), data(a.data) { 
        // move constructor
        a.data = nullptr;
        a.__size = 0;
        cout << "move constructor" << endl;
        return ;
    }
    int size() { return __size; }
    int &operator[](int ind) {
        return data[ind];
    }
    int &operator[](int ind) const {
        return data[ind];
    }
    Array operator+(Array &a) {
        Array ret(__size + a.__size);
        for (int i = 0; i < __size; i++) {
            ret[i] = data[i];
        }
        for (int i = __size; i < ret.size(); i++) {
            ret[i] = a[i - __size]; 
        }
        return ret;
    }
    ~Array() {
        cout << this << " destructr " << endl; 
    }
private:
    int __size, *data;
};

int main() {
    Array a, b;
    Array c = a + b; 
    Array d(move(a));
    return 0;
}

ENDS(test4)

int main() {
    //test1::main(); 
    //test2::main(); 
    //test3::main();
    test4::main();
    return 0;
}
