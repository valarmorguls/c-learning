/* ************************************************************************
> File Name:     2.cout.cpp
> Author:        xupeng
> About:         
> Description:   
 ************************************************************************/

#include <iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x)}

BEGINS(haizei)
class ostream {
public:
    ostream &operator<<(int x);
    ostream &operator<<(char ch);
};

ostream &ostream::operator<<(int x) {
    printf("%d\n", x);
    return *this;
}

ostream &ostream::operator<<(char x) {
    printf("%c\n", x);
    return *this;
}

ostream cout;
const char endl = '\n';

ENDS(haizei)

int main() {
    int n = 123;
    std::cout << n << std::endl;
    haizei::cout << n << haizei::endl;
    return 0;
}
