/*************************************************************************
	> File Name: 5.final_template_test.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 09 Apr 2023 01:57:26 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(sum_test)

template <int N>
class sum {
public:
    static constexpr int r = sum<N - 1>::r + N;
};

template <>
class sum<1> {
public:
    static constexpr int r = 1;
};

int main() {
    cout << sum<5>::r << endl; // sum of 1 - 5
    cout << sum<7>::r << endl; // sum of 1 - 7 
    cout << sum<100>::r << endl; // sum of 1 - 100 
    return 0;
}

ENDS(sum_test)

BEGINS(even_test)

template <int N>
struct YES_OR_NO {
    static constexpr const char *r = (N ? "yes" : "no");
};

template <int N>
struct is_even {
    static constexpr const char *r = YES_OR_NO<!(N % 2)>::r;
};
/*
template <int N>
struct YES_OR_NO {
    static const char *r;
};

template <>
struct YES_OR_NO<0> {
    static const char *r;
};

template <int N> 
const char * YES_OR_NO<N>::r = "yes";
const char * YES_OR_NO<0>::r = "no";

template <int N>
struct is_even {
    static const char *r;
};

template <int N>
const char *is_even<N>::r = YES_OR_NO<!(N % 2)>::r;

*/

int main() {
    cout << is_even<5>::r << endl; // no 
    cout << is_even<6>::r << endl; // yes 
    return 0;
}

ENDS(even_test)

BEGINS(good_bad_test)

template <int N>
struct GOOD_OR_BAD {
    static const char *r;
};

template <>
struct GOOD_OR_BAD<0> {
    static const char *r;
};

template <int N>
const char *GOOD_OR_BAD<N>::r = "good";
const char *GOOD_OR_BAD<0>::r = "bad";

template <int M>
struct score_judge {
    static const char *r;
};

template <int N>
const char *score_judge<N>::r = GOOD_OR_BAD<(N >= 60)>::r;

int main() {
    cout << score_judge<60>::r << endl; // good 
    cout << score_judge<54>::r << endl; // bad 
    return 0;
}

ENDS(good_bad_test)

BEGINS(is_prime_test)

template <int i, int N>
struct getNext {
    static constexpr int r = (N % i ? i + 1 : 0);
};

template <int i, int N>
struct test {
    static constexpr const char *r = ((i * i > N) ? "yes" : test<getNext<i, N>::r, N>::r); 
};

template <int N>
struct test<0, N> {
    static constexpr const char *r = "no";
};

template <int N>
struct is_prime {
    static constexpr const char *r = test<2, N>::r;
};

int main() {
    cout << "2 : " << is_prime<2>::r << endl; // yes 
    cout << "3 : " << is_prime<3>::r << endl; // yes 
    cout << "5 : " << is_prime<5>::r << endl; // yes 
    cout << "8 : " << is_prime<8>::r << endl; // no 
    cout << "103: " << is_prime<103>::r << endl; // yes 
    return 0;
}

ENDS(is_prime_test)

int main() {
    sum_test::main();
    even_test::main();
    is_prime_test::main();
    good_bad_test::main();
    return 0;
}
