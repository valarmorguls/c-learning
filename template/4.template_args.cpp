/*************************************************************************
	> File Name: 4.template_args.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 09 Apr 2023 11:05:49 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;


#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(test1)

class A {
public:
    A(int x, int y) : x(x), y(y) {}
    int x, y;
};

ostream &operator<<(ostream &out, const A &a) {
    out << "Class A : " << a.x << ", " << a.y;
    return out;
}

//模板函数没有偏特化，模板类有偏特化，类似重载
template<typename T>
void Print(T a) {
    cout << a << endl;
    return ;
}

template <typename T, typename ...ARGS>
void Print(T a, ARGS... args) {
    cout << a << " | "; 
    Print(args...);
    return ;
}

int main() {
    A a(5, 6);
    Print("hello world");
    Print("hello world", 3, 3.4, a);
    Print(3, a, 6.7, "hello");
    return 0;
}

ENDS(test1)

BEGINS(test2)

template <typename T, typename ...ARGS>
class ARG {
public:
    typedef T type;
    typedef ARG<ARGS...> rest;
};

template <typename T>
class ARG<T> {
public:
    typedef T type;
};

//ARG<ARGS> 工具模板类： 作用：获取ARGS中的类型
//AEGS<ARGS>::type 第一个类型
//ARG<ARGS>::rest::type 剩余部分
template <typename T, typename ...ARGS>
class Test {
public:
    T operator()(typename ARG<ARGS...>::type a, typename ARG<ARGS...>::rest::type b) {
        return a + b;
    }
};

int main() {
    Test<int, int, int> t1;
    Test<double, double, int> t2;
    cout << t1(3, 4) << endl;
    cout << t2(3.4, 3) << endl;
    return 0;
}

ENDS(test2)

BEGINS(test3)

template <typename T, typename ...ARGS>
class ARG {
public:
    typedef T type;
    typedef ARG<ARGS...> rest; 
};

template <typename T>
class ARG<T> {
public:
    typedef T type;
    typedef T ftype; 
};

template <typename T, typename ...ARGS>
class Test {
public:
    T operator()(
        typename ARG<ARGS...>::type a, 
        typename ARG<ARGS...>::rest::ftype b) {
        return a + b;
    }
};

int main() {
    Test<int, int, int> t1;
    Test<double, double, int> t2;
    //Test<double, int, int, int> t3;
    cout << t1(3, 4) << endl;
    cout << t2(3.4, 3) << endl;
    return 0;
}

ENDS(test3)

BEGINS(test4)

template <typename T, typename ...ARGS>
class ARG {
public:
    typedef T type;
    typedef ARG<ARGS...> rest;
};

template <typename T>
class ARG<T> {
public:
    typedef T type;
    typedef T ftype;
};

template <typename T, typename ...ARGS> class Test;
template <typename T, typename ...ARGS>
class Test<T(ARGS...)> {
public:
    T operator()(
        typename ARG<ARGS...>::type a,
        typename ARG<ARGS...>::rest::ftype b
    ) {
       return a + b; 
    }
};

int main() {
    Test<int(int, int)> t1;
    Test<double(double, int)> t2;
    //Test<double, int, int, int> t3;
    cout << t1(3, 4) << endl;
    cout << t2(3.4, 3) << endl;
    return 0;
}

ENDS(test4)

BEGINS(test5)

template <int M>
void Print() {
    cout << M << " ";
    Print<M - 1>();
    return ;
}

template <>
void Print<1>() {
    cout << 1 << endl;
    return ;
}

int main() {
    Print<10>();
    Print<5>();
    Print<6>();
    return 0;
}

ENDS(test5)

BEGINS(test6)

template <int N, typename T, typename ...ARGS>
class ARG {
public:
    typedef typename ARG<N - 1, ARGS...>::type type;
};

template<typename T, typename ...ARGS>
class ARG<1, T, ARGS...> {
public:
    typedef T type;
};

template <typename T>
class ARG<1, T> {
public:
    typedef T type;
};

template <typename T, typename ...ARGS>
class NUM_ARGS {
public:
    static constexpr int r = NUM_ARGS<ARGS...>::r + 1;
};

template <typename T>
class NUM_ARGS<T> {
public:
    static constexpr int r = 1;
};

template <int N>
struct Zero {
    typedef int no;
};

template <>
struct Zero<0> {
    typedef int yes;
};

template <typename T, typename ...ARGS> class Test;
template <typename T, typename ...ARGS>
class Test<T(ARGS...)> {
public:
    //typedef ARG<2, ARGS...>::ftype TYPE_NUM_2;
    typedef typename Zero<2 - NUM_ARGS<ARGS...>::r>::yes TYPE_NUM_2;
    T operator()(
        typename ARG<1, ARGS...>::type a,
        typename ARG<2, ARGS...>::type b
    ) {
        return a + b;
    }
};

int main() {
    /*
    Test<int(int, int)> t1;
    Test<double(double, int)> t2;
    //Test<double, int, int, int> t3;
    cout << t1(3, 4) << endl;
    cout << t2(3.4, 3) << endl;
    cout << NUM_ARGS<int, int, int, int>::r << endl;
    cout << NUM_ARGS<int, int, int>::r << endl;
    cout << NUM_ARGS<int, int>::r << endl;
    */
    Test<bool(int, int)> t1;
    cout << t1(3, 4) << endl;
    return 0;
}

ENDS(test6)

int main() {
    //test1::main(); 
    //test2::main(); 
    //test4::main();
    //test5::main();
    test6::main();
    return 0;
}
