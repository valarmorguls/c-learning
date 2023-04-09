/*************************************************************************
	> File Name: 11.friend.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Apr 2023 04:04:00 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

class Point {
public:
    Point(int x, int y) : x(x), y(y) {}
    void output() {
        cout << "inner : " << x << " " << y << endl;
        return ;
    }
    friend void output(Point &);
    friend ostream &operator<<(ostream &out, const Point &a);
private:
    int x, y;
};

void output(Point &a) {
    cout << "outter : " << a.x << " " << a.y << endl;
    return ;
}

ostream &operator<<(ostream &out, const Point &a) {
    out << a.x << " " << a.y << endl;
    return out;
}

int main() {
    //输出点类对象信息
    Point p(3, 4); 
    p.output();
    output(p);
    cout << p << endl;
    return 0;
}
