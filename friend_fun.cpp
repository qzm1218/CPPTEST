#include "math.h"
#include<iostream> 
using namespace std; 

// 友元函数
// 1.1为什么要使用友元函数
// 在实现类之间数据共享时，减少系统开销，提高效率。
// 如果类A中的函数要访问类B中的成员（例如：智能指针类的实现），那么类A中该函数要是类B的友元函数。
// 具体来说：为了使其他类的成员函数直接访问该类的私有变量。即：允许外面的类或函数去访问类的私有变量和保护变量，从而使两个类共享同一函数。
// 实际上具体大概有下面两种情况需要使用友元函数：
// （1）运算符重载的某些场合需要使用友元。
// （2）两个类要共享数据的时候。
//
// 优点：能够提高效率，表达简单、清晰。
// 缺点：友元函数破环了封装机制，尽量不使用成员函数，除非不得已的情况下才使用友元函数。
//
// 2.友元函数的参数：
// 因为友元函数没有this指针，则参数要有三种情况：
// 1 要访问非static成员时，需要对象做参数；
// 2 要访问static成员或全局变量时，则不需要对象做参数；
// 3 如果做参数的对象是全局对象，则不需要对象做参数；
// 2.2友元函数的位置
// 因为友元函数是类外的函数，所以它的声明可以放在类的私有段或公有段且没有区别。
// 2.3友元函数的调用
// 可以直接调用友元函数，不需要通过对象或指针
// 2.4友元函数的分类：
// 根据这个函数的来源不同，可以分为三种方法：
//
//
// 4.友元函数和类的成员函数的区别
// 1 成员函数有this指针，而友元函数没有this指针。
// 2 友元函数是不能被继承的，就像父亲的朋友未必是儿子的朋友
//

class Point 
{ 
public: 
    Point(double xx, double yy) 
    {
        x=xx; 
        y=yy; 
    }
    void Getxy(); 
    friend double Distance(Point &a, Point &b);        //类Point的友元函数
    friend class Yao;                                  //类Point的友元类
private: 
    double x, y; 
}; 


class Yao
{
public:
    double Multi(Point &a)
    {
        return a.x * a.y + 1;
    }
};

void Point::Getxy() 
{ 
    cout<<"("<<x<<","<<y<<")"<<endl; 
} 

double Distance(Point &a, Point &b)                   //类Point的友元函数
{ 
    double dx = a.x - b.x; 
    double dy = a.y - b.y; 
    return sqrt(dx*dx+dy*dy); 
} 

int main(void) 
{ 
    Point p1(3.0, 4.0), p2(6.0, 8.0); 
    p1.Getxy(); 
    p2.Getxy(); 
    double d = Distance(p1, p2);            //Distance是类Point的友元函数，不是成员函数
    cout<<"Distance is "<<d<<endl; 
    Yao yao;
    d = yao.Multi(p1);
    cout<<"Math.Multi is "<<d<<endl;
    return true;
}
