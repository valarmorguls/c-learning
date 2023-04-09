/* ************************************************************************
> File Name:     1.class.cpp
> Author:        xupeng
> About:         
> Description:   
 ************************************************************************/

#include <iostream>

using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(haizei)

class People {
public:
    string name;
    int age;
    double height;
    double weight;

   /* void say(string name) {
        cout << "my name is " << this->name << endl;
        cout << "my name is " << name << endl;
    }
   */ 
    void run();
};

ENDS(haizei)

void haizei::People::say(string name) {
    cout << "my name is " << this->name << endl;
    cout << "my name is " << name << endl;
}
 
int main() {
    haizei::People bug;
    haizei::People yubing;
    haizei::People xupeng;

    bug.name = "Captain Hu";
    yubing.name = "hello";
    xupeng.name = "xupeng";

    bug.say("xiaolan");
    yubing.say("xiaoyang");
    xupeng.say("xiaobing");
    
    return 0;
}
