/*************************************************************************
	> File Name: 10.reload.cpp
	> Author: 
	> Mail: 
 ************************************************************************/

#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

/*int func(int x) {
    return 2 * x;
}
*/

//func(int)
//func(int, int)
int func(int x, int y = 2) {
    return x * y;
}

double func(double x) {
    return x + 1000;
}

int ABS(int x) {
    return abs(x);
}

double ABS(double x) {
    return fabs(x);
}

void output_permutation(int ind, int n, int *buff, int *num) {
    if (ind == n) {
        for (int i = 0; i < n ; i++) {
            cout << buff[i] << " ";
        }
        cout << endl;
        return ;
    }
    for (int i = 1; i <= n; i++) {
        if (num[i]) continue;
        buff[ind] = i;
        num[i] = 1;
        output_permutation(ind + 1, n, buff, num);
        num[i] = 0;
    }
    return ;
}

void output_permutation(int n) {
    int num[n + 1], buff[n];
    memset(num, 0, sizeof(num));
    memset(buff, 0, sizeof(buff));
    output_permutation(0, n, buff, num);
    return ;
}

int main() {
    cout << func(2) << endl;
    cout << func(2.0) << endl;
    cout << ABS(-2.3) << endl;
    cout << ABS(-2) << endl;
    output_permutation(4);
    return 0;
}
