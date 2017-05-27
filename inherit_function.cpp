#include <iostream>

using namespace std;
class Base
{
public:
    void foo()
    {
        cout << "Base::foo" << endl;
    };

    virtual void fuu()
    {
        cout << "Base::fuu" << endl;
    };
};

class Derived:public Base
{
public:
    void foo()
    {
        cout << "Derived::foo" << endl;
    };

    void fuu()
    {
        cout << "Derived::fuu" << endl;
    };
};

int main(int argc, char *argv[])
{
    Base b;
    Derived d;
    cout << "=================================" << endl;

    cout << "基类的普通调用:" << endl;
    cout << "本身就是基类的指针,指向的是基类的对象,调用的也是基类的函数" << endl;
    Base *pb = &b;
    cout << "pb->foo() --- " ; pb->foo();
    cout << "pb->fuu() --- " ; pb->fuu();
    cout << "=================================" << endl;

    cout << "向上转型:" << endl;
    cout << "基类指针指向子类对象,这正是体现多态的用法" << endl;
    pb = &d;
    cout << "pb->foo()由于指针是基类指针,指向的是固定偏移量的函数,此时指向的是基类的foo函数" << endl;
    cout << "pb->foo() --- " ; pb->foo();
    cout << "但pb->fuu()是基类指针,指向的是虚函数,此时指向的是虚函数,由于每个虚函数都有一个虚函数列表,"
            "因此pb调用fuu不是直接调用函数,而是通过虚函数表找到对于你的函数地址,因此指向的对象不同,函数地址也不同" << endl;
    cout << "pb->fuu() --- " ; pb->fuu();
    cout << "=================================" << endl;
   
    cout << "向下转型:" << endl;
    Derived *pd = (Derived *)&b;
    cout << "由于pd是子类指针，虽然被赋予了基类对象地址，但是pd->foo()在调用的时候，由于地址偏移量固定，"
            "偏移量是子类对象的偏移量，于是即使在指向了一个基类对象的情况下，还是调用到了子类的函数，虽然可能从始到终都没有子类对象的实例化出现" << endl;
    cout << "pd->foo() --- " ; pd->foo();
    cout << "而ptr->fuu()的调用，可能还是因为C++多态性的原因，由于指向的是一个基类对象，通过虚函数列表的引用，"
            "找到了基类中foo()函数的地址，因此调用了基类的函数。由此可见多态性的强大，可以适应各种变化，不论指针是基类的还是子类的，都能找到正确的实现方法" << endl;
    cout << "pd->fuu() --- " ; pd->fuu();
    cout << "=================================" << endl;

    cout << "派生类的普通调用:" << endl;
    cout << "本身就是子类的指针,指向的是子类的对象,调用的也是子类的函数" << endl;
    pd = &d;
    cout << "pd->foo() --- " ; pd->foo();
    cout << "pd->fuu() --- " ; pd->fuu();
    cout << "=================================" << endl;

    return 0;
}
