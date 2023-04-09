/*************************************************************************
	> File Name: 6.function.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 09 Apr 2023 03:46:51 PM CST
 ************************************************************************/

#include <iostream>
#include <functional>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(reference_param)

template <typename T>
struct remove_reference {
    typedef T type;
};

template <typename T>
struct remove_reference<T &> {
    typedef T type;
};

template <typename T>
struct remove_reference<T &&> {
    typedef T type;
};

template <typename T>
struct add_const {
    typedef const T type;   
};

template <typename T>
struct add_const<const T> {
    typedef const T type;   
};

template <typename T>
struct add_lvalue_reference {
    typedef T & type;
};

template <typename T>
struct add_lvalue_reference<T &> {
    typedef T & type;
};

template <typename T>
struct add_lvalue_reference<T &&> {
    typedef T & type;
};

template <typename T>
struct remove_pointer {
public:
    typedef T type;
};

template <typename T> 
struct remove_pointer<T *> {
    typedef typename remove_pointer<T>::type type;
};

//&&两个&&表示接受引用
template <typename T>
void func(T &&a) {
    remove_reference<T> c;
    //把类型T中的引用去掉
    cout << "function T& a = " << a << endl;
    return ;
}

int main() {
    int n = 123;
    func(n);
    func(123);
    typename remove_reference<int &&>::type a;
    typename remove_reference<int &>::type b;
    typename remove_reference<int>::type c;
    cout << sizeof(typename remove_pointer<int>::type) << endl;
    cout << sizeof(typename remove_pointer<int *>::type) << endl;
    cout << sizeof(typename remove_pointer<int **>::type) << endl;
    cout << sizeof(typename remove_pointer<int **>::type) << endl;
    return 0;
}

ENDS(reference_param)

//函数 + 参数 打包绑定
BEGINS(bind_usage)

int add(int a, int b) {
    cout << "add(a, b) = ";
    return a + b;
}

void add_one(int &n) {
    n += 1;
    return ;
}

void func(int n, const char *msg) {
    cout << n << " " << msg << endl; 
}

int main() {
    auto t1 = bind(add, 3, 4); 
    cout << t1() << endl;
    cout << t1() << endl;
    cout << t1() << endl;
    int n = 1;
    //ref 绑定引用
    cout << "n = " << n << endl; 
    auto t2 = bind(add_one, ref(n));
    t2(); t2(); t2();
    cout << "after three times t2 function call, n = " << n << endl;
    func(3, "hello world");
    auto t3 = bind(func, std::placeholders::_2, std::placeholders::_1);
    t3("helloworld", 3);
    auto t4 = bind(func, std::placeholders::_4, std::placeholders::_1);
    t4("helloworld", 3, 2, 1);
    return 0;
}

ENDS(bind_usage)

BEGINS(function_impl)

template <typename T, typename ...ARGS>
class Base {
public:
    virtual T run(ARGS...) = 0;
    virtual Base<T, ARGS...> *getCopy() = 0;
    virtual ~Base() {}
};

template <typename T, typename ...ARGS>
class normal_function : public Base<T, ARGS...> {
public:
    normal_function(T (*ptr)(ARGS...)) : func(ptr) {} 
    T run(ARGS ...args) override {
        return func(forward<ARGS>(args)...); 
    }
    Base<T, ARGS...> *getCopy() override {
        return new normal_function(*this);
    }

private:
    T (*func)(ARGS...);
};

template <typename CLASS_T, typename T, typename ...ARGS>
class functor: public Base<T, ARGS...> {
public:
    functor(CLASS_T obj) : obj(obj) {}
    T run(ARGS ...args) override {
        return obj(forward<ARGS>(args)...); 
    }
    Base<T, ARGS...> *getCopy() override {
        return new functor(*this);
    }

private:
    CLASS_T obj;
};

template <typename T, typename ...ARGS> class function;
template <typename T, typename ...ARGS> 
class function<T(ARGS...)> {
public:
    function(T (*ptr)(ARGS...)) 
    : ptr(new normal_function<T, ARGS...>(ptr)) {}
    template <typename CLASS_T>
    function(CLASS_T obj) 
    : ptr(new functor<CLASS_T, T, ARGS...>(obj)) {}

    T operator()(ARGS... args) {
        return ptr->run(forward<ARGS>(args)...); 
    }

    function &operator=(const function<T(ARGS...)> &func) {
        delete this->ptr;
        this->ptr = func.ptr->getCopy();
        return *this;
    }
    ~function() {
        delete this->ptr;
    }

private:
    Base<T, ARGS...> *ptr; 
};


int add(int a, int b) {
    cout << "normal function : "; 
    return a + b;
}

class ADD_MULT {
public:
    ADD_MULT(int x) : x(x) {}
    int operator()(int a, int b) {
        cout << "functor : ";
        return (a + b) * 2;
    }
private:
    int x;
};

int main() {
    ADD_MULT add_mult(2); 
    function<int(int, int)> f1 = add;
    function<int(int, int)> f2 = add_mult;
    cout << f1(3, 4) << endl;
    cout << f2(3, 4) << endl;
    f1 = f2;
    cout << f1(3, 4) << endl;
    return 0;
}

ENDS(function_impl)


int main() {
    //reference_param::main();    
    //bind_usage::main();
    function_impl::main();
    return 0;
}

