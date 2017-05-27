#include <iostream>

///////////////////////////
//  避免遮掩继承而来的名称
//  C++的名称遮掩规则所做的唯一事情就是遮掩名称: 至于名称是否应和相同或者不通的类型并不重要
//  在继承导入的过程中,派生类成员函数内指涉(refer to)基类内的某物时,编译器可以找到我们指涉的东西
//  因为派生类继承了声明于基类的所有东西.实际的运作方式是:派生类的作用域被嵌套在基类的作用域中
//                    ------------------------------------
//                    | Base的作用域                     |
//                    | x (成员函数)    -----------------|
//                    | mf1(2个函数)    | Derived作用域 ||
//                    | mf2(1个函数)    | mf1(1个函数)  ||
//                    | mf3(2个函数)    | mf3(1个函数)  ||
//                    |                 | mf4(1个函数)  ||
//                    |                 ---------------- |
//                    -----------------------------------
//
//  编译器查找各作用域的顺序是:
//  1,查找local作用域
//  2,如果没有,查找外围域,也就是派生类的覆盖的作用域
//  3,如果没有,再往外围域查找,也就是基类
//  4,如果没有,再往基类的namespace作用域查找
//  5,如果没有,再往global作用域查找
//////////////////////////

///////////////////////////////////
//  接口继承和实现继承不通
//  1,在public继承之下,派生类总是继承基类的接口
//  2,纯虚函数只是具体指定接口的继承
//  3,非纯虚继承具体指定接口及缺省实现继承
//  4,非虚函数具体指定接口继承及强制性实现继承
using namespace std;

#if HIDING_NAME 
class Base 
{
private:
    int x;
public:
    /////////////////////////////////////////////////////
    //  纯虚函数(pure virtual)做突出的特征是:
    //  1, 他们必须被任何"继承了他们"的具体class重新声明,而且他们在抽象class中通常没有定义
    //  2, 声明一个纯虚函数的目的是为了让派生类只继承函数接口.
    virtual void mf1() = 0;

    ////////////////////////////////////////////////////
    // 非纯虚(impure virtual)函数会提供一份实现的代码,派生类可能覆盖他
    // 非纯虚函数的目的是让派生类继承该函数的接口和缺省的实现
    virtual void mf1(int)
    {
        cout << "Base::mf1(int)" << endl;
    };

    virtual void mf2()
    {
        cout << "Base::mf2(int)" << endl;
    };

    ///////////////////////////////////////////////////////////
    //  非虚函数(non-virtual) 意味着他并不打算在派生类中有不同的行为.实际上非虚函数所表现
    //  的不变性凌驾于特异性,因此无论派生类多么特异化,他的行为都是不可以改变的
    //  非虚函数的目的是为了令派生继承的函数的接口及一份强制实现
    void mf3()
    {
        cout << "Base::mf3()" << endl;
    };

    void mf3(double)
    {
        cout << "Base::mf3(double)" << endl;
    };
};

class Derived : public Base
{
public:
    virtual void mf1()
    {
        cout << "Derived::mf1()" << endl;
    };

    void mf3()
    {
        cout << "Derived::mf3()" << endl;
    };

    void mf4()
    {
        cout << "Derived::mf4()" << endl;
    };
};


int main(int argc, char *argv[])
{
    Derived d;
    int x;

    x = 3;
    d.mf1();        // 没问题,调用 Derived::mf1
    //d.mf1(x);       // 错误, 因为Derived::mf1遮掩了Base::mf1
    d.mf2();        // 没问题,调用了Derived::mf2
    d.mf3();        // 没问题,调用了Derived::mf3
    //d.mf3(x);       // 错误,因为Derived::mf3遮掩了Base::mf3
    return 0;
}

#endif

//////////////////////////////////////////////////////////////
// 1, 使用using声明式 解决遮掩问题
// ///////////////////////////////////////////////////////////
#if USE_USING_DECLARE 
class Base 
{
private:
    int x;
public:
    virtual void mf1() = 0;

    virtual void mf1(int)
    {
        cout << "Base::mf1(int)" << endl;
    };

    virtual void mf2()
    {
        cout << "Base::mf2(int)" << endl;
    };

    void mf3()
    {
        cout << "Base::mf3()" << endl;
    };

    void mf3(double)
    {
        cout << "Base::mf3(double)" << endl;
    };
};

class Derived : public Base
{
public:
    using Base::mf1;                 //让Base class内名为mf1 和mf3 的所有东西在Derived作用域内都可见
    using Base::mf3;

    virtual void mf1()
    {
        cout << "Derived::mf1()" << endl;
    };

    void mf3()
    {
        cout << "Derived::mf3()" << endl;
    };

    void mf4()
    {
        cout << "Derived::mf4()" << endl;
    };
};


int main(int argc, char *argv[])
{
    Derived d;
    int x;

    x = 3;
    d.mf1();        // 没问题,调用Derived::mf1
    d.mf1(x);       // 没问题,调用Base::mf1
    d.mf2();        // 没问题,调用Base::mf2
    d.mf3();        // 没问题,调用Derived::mf3
    d.mf3(x);       // 没问题,调用Base::mf3
    return 0;
}
#endif



//////////////////////////////////////////////////////////////
// 2,转交函数实现(私有继承)
// 转交函数另一个用途是为那些不支持using声明式的老旧编译器另辟一条新的道路
// 将继承而来的名称汇入到derived作用域 
// ///////////////////////////////////////////////////////////
class Base 
{
private:
    int x;
public:
    virtual void mf1() = 0;

    virtual void mf1(int)
    {
        cout << "Base::mf1(int)" << endl;
    };

    virtual void mf2()
    {
        cout << "Base::mf2(int)" << endl;
    };

    void mf3()
    {
        cout << "Base::mf3()" << endl;
    };

    void mf3(double)
    {
        cout << "Base::mf3(double)" << endl;
    };
};

class Derived : private Base        // 私有继承
{
public:
    virtual void mf1()               // 转交函数
    {
        //Base::mf1();                 // 暗自成为inline
        cout << "Derived::mf1()" << endl;
    };

    void mf3()
    {
        Base::mf3();
        cout << "Derived::mf3()" << endl;
    };

    void mf4()
    {
        cout << "Derived::mf4()" << endl;
    };
};


int main(int argc, char *argv[])
{
    Derived d;
    int x;

    x = 3;
    d.mf1();        // 没问题,调用Derived::mf1
//    d.mf1(x);       // 没问题,调用Base::mf1
//    d.mf2();        // 没问题,调用Base::mf2
    d.mf3();        // 没问题,调用Derived::mf3
//    d.mf3(x);       // 没问题,调用Base::mf3
    return 0;
}
