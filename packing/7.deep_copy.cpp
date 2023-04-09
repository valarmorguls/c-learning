/*************************************************************************
	> File Name: 7.deep_copy.cpp
	> Author: 
	> Mail: 
 ************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namesapce x

BEGINS(haizei)

class A {
public:
    int x, y;
};

ostream &operator<<(ostream &out, const A &a) {
    out << "(" << a.x << ", " << a.y << ") ";
    return out;
}

template <typename T>
class Vector {
public:
    Vector(int n = 100) : n(n), /*data(new T[n])*/data((T *)calloc(sizeof(T), n)) {}  
    Vector(const Vector &a) : n(a.n) {
        //data = new T[n]; //有bug，如果对象没有默认构造，这里出错
        //memcpy(data, a.data, sizeof(T) * n);
        data = (T *)malloc(sizeof(T) * n);
        for (int i = 0; i < n; i++) {
            //调用深拷贝
            new (data + i) T(a.data[i]);
        }
        return ;
    }
    T &at(int ind) { return data[ind]; }
    T &operator[](int ind) { return data[ind]; }
    void output(int m = -1) {
        if (data == nullptr) return ;
        if (m == -1) m = n;
        cout << "arr " << this << " : ";
        for (int i = 0; i < m; i++) {
            cout << data[i] << " "; 
        }
        cout << endl;
        return ;
    }

private:
    int n;
    T *data;
};

ENDS(haizei)

BEGINS(test1)

int main() {
    haizei::Vector<int> arr1; 
    for (int i = 0; i < 10; i++) arr1.at(i) = i;
    arr1.output(10);
    //浅拷贝
    haizei::Vector<int> arr2(arr1);
    arr2.output(10);
    arr2[3] = 1000;
    arr1.output(10);
    arr2.output(10);
    return 0;
}

ENDS(test1)


BEGINS(test2)

using namespace haizei; 


int main() {
    haizei::Vector<A> arr1;
    for (int i = 0; i < 10; i++) {
        arr1[i].x = i;
        arr1[i].y = 2 * i;
    }
    arr1.output(10);
    Vector<A> arr2(arr1);
    arr2[3] = (A){4, 1000};
    arr1.output(10);
    arr2.output(10);
    return 0;
}

ENDS(test2)

BEGINS(test3)

using namespace haizei;

int main() {
    Vector<Vector<int>> arr1; 
    Vector<Vector<int>> arr2(arr1);
    arr2[2][2] = 1000;
    for (int i = 0; i < 3; i++) {
        arr1[i].output(3);
    }
    for (int i = 0; i < 3; i++) {
        arr2[i].output(3);
    }
    return 0;
}


ENDS(test3)

int main() {
    test1::main(); 
    test2::main();
    test3::main();
    return 0;
}
