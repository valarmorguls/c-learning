# 普通的成员方法跟着类走
# 虚函数跟着对象走
# override 不做功能性保证，
没有加override，可能造成误差
# 虚函数，是运行时状态， 
派生类对象，实现了所有的纯虚函数

#virtual
不能用来修饰类方法-static
#虚函数是运行时状态，

#为什么虚函数可以跟着对象走？
对象占用存储区，头八个字节不一样，头八个字节指向虚函数表的地方（vtable），虚函数表装着
每一个虚函数。
拥有虚函数的对象和没有拥有虚函数对象的大小不一样

#每一个类有一个虚函数表
相同类型的对象指向 相同的虚函数表
虚函数表是存储函数地址的数组
ZZ
#dynamic_cast
父类指针指向子类ZZ
就是通过虚函数表来确定信息的
##dynamic_cast就是通过判断vtable的-1位置来判断存储的信息