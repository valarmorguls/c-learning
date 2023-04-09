/*************************************************************************
	> File Name: 3.specialization.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 08 Apr 2023 05:53:12 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(test1)

template <typename T>
T add(T a, T b) {
    return a + b;
}

template <>
int add(int a, int b) {
    cout << "int template" << endl;
    return a + b;
}

int main() {
    cout << add(3, 4) << endl; // add<int>
    cout << add(3.1, 4.2) << endl; // add<double>
    return 0;
}

ENDS(test1)

BEGINS(test2)

template <typename T, typename U>
class Test {
public:
    Test() {
        cout << "normal template<T, U>" << endl;
    }
};

template<>
class Test<int, double> {
public:
    Test() {
        cout << "specialization  template<int, double>" << endl;
    }
};

template<typename T>
class Test<int, T> {
public:
    Test() {
        cout << "partial specialization template<int, T>" << endl;
    }
};

int main() {
    Test<string, int> t1;
    Test<int, double> t2; // 
    Test<int, string> t3;
    return 0;
}

ENDS(test2)

BEGINS(test3)

class A {};
class B {};

template <typename T>
class type_trais {
public:
    static const char *has_constructor;
};

template<typename T>
const char *type_trais<T>::has_constructor = "yes";

template <typename T>
class type_trais<T *> {
public:
    static const char *has_constructor;
};

template<typename T>
const char *type_trais<T *>::has_constructor = "no";

template<>
class type_trais<int> {
public:
    static const char *has_constructor;
};

const char *type_trais<int>::has_constructor = "no";

template<>
class type_trais<double> {
public:
    static const char *has_constructor;
};

const char *type_trais<double>::has_constructor = "no";

template<>
class type_trais<string> {
public:
    static const char *has_constructor;
};

const char *type_trais<string>::has_constructor = "yes";

#define TEST(type)  cout << #type << " : " << type_trais<type>::has_constructor << endl; 


int main() {
    TEST(int);
    TEST(A);
    TEST(double);
    TEST(B);
    TEST(string);
    TEST(string *);
    /*
    cout << type_trais<int>::has_constructor << endl; //no
    cout << type_trais<A>::has_constructor << endl; //yes
    cout << type_trais<double>::has_constructor << endl; //no
    cout << type_trais<B>::has_constructor << endl; //yes
    cout << type_trais<string>::has_constructor << endl; //yes
    cout << type_trais<string *>::has_constructor << endl; //yes
    */
    return 0;
}

ENDS(test3)

BEGINS(test4)


class A {};
class B {};

class yes_constructor {
public:
    static const char *has_constructor;
};

const char *yes_constructor::has_constructor = "yes";

class no_constructor {
public:
    static const char *has_constructor;
};

const char *no_constructor::has_constructor = "no";

template <typename T>
class type_trais : public yes_constructor {};

template <typename T>
class type_trais<T *> : public no_constructor {};

template <>
class type_trais<int> : public no_constructor {};

template <>
class type_trais<double> : public no_constructor {};

#define TEST(type)  cout << #type << " : " << type_trais<type>::has_constructor << endl; 


int main() {
    TEST(int);
    TEST(A);
    TEST(double);
    TEST(B);
    TEST(string);
    TEST(string *);
    return 0;
}

#undef TEST
ENDS(test4)

BEGINS(test5)

class A {};
class B {};

class yes_constructor {};
class no_constructor {};

template <typename T>
class type_trais {
public:
    typedef yes_constructor has_constructor;
};

template <typename T>
class type_trais<T *> {
public:
    typedef no_constructor has_constructor;
};

template <>
class type_trais<int> {
public:
    typedef no_constructor has_constructor;   
};

template <>
class type_trais<double> {
public:
    typedef no_constructor has_constructor;   
};

ostream &operator<<(ostream &out, const yes_constructor &) {
    out << "yes";
    return out;
}

ostream &operator<<(ostream &out, const no_constructor &) {
    out << "no";
    return out;
}

#define TEST(type)  cout << #type << " : " << type_trais<type>::has_constructor()<< endl; 


int main() {
    TEST(int);
    TEST(A);
    TEST(double);
    TEST(B);
    TEST(string);
    TEST(string *);
    return 0;
}

#undef TEST

ENDS(test5)

int main() {
    //test1::main();
    //test2::main();
    test3::main();
    test4::main();
    test5::main();
    return 0;
}
