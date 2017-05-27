#include <iostream>
using namespace std;

// C++运算符重载讲解与经典实例
// 一、 运算符重载的规则 
// 运算符重载规则如下： 
// ①、 C++中的运算符除了少数几个之外，全部可以重载，而且只能重载C++中已有的运算符。 
// ②、 重载之后运算符的优先级和结合性都不会改变。 
// ③、 运算符重载是针对新类型数据的实际需要，对原有运算符进行适当的改造。
//     一般来说，重载的功能应当与原有功能相类似，不能改变原运算符的操作对象个数，同时至少要有一个操作对象是自定义类型。 
//
// 不能重载的运算符只有五个，
// 它们是：1, 成员运算符“.”、
//         2, 指针运算符“*”、
//         3, 作用域运算符“::”、
//         4, “sizeof”、
//         5, 条件运算符“？：”。 
//
// 运算符重载形式有两种:
//     1, 重载为类的成员函数和
//     2, 重载为类的友元函数。 
//
// 运算符重载为类的成员函数的一般语法形式为： 
// 函数类型 operator 运算符（形参表） 
// { 
//     函数体； 
// } 
//
// 运算符重载为类的友元函数的一般语法形式为： 
// friend 函数类型 operator 运算符（形参表） 
// { 
//     函数体； 
// } 
// 其中，函数类型就是运算结果类型；operator是定义运算符重载函数的关键字；运算符是重载的运算符名称。 
//     a,当运算符重载为类的成员函数时，函数的参数个数比原来的操作个数要少一个；
//     b,当重载为类的友元函数时，参数个数与原操作数个数相同。
//
// 原因是重载为类的成员函数时:
//     a, 如果某个对象使用重载了的成员函数，自身的数据可以直接访问，就不需要再放在参数表中进行传递,少了的操作数就是该对象本身。
//     b, 而重载为友元函数时，友元函数对某个对象的数据进行操作，就必须通过该对象的名称来进行，因此使用到的参数都要进行传递，操作数的个数就不会有变化。 
// 
// 运算符重载的主要优点就是允许改变使用于系统内部的运算符的操作方式，以适应用户自定义类型的类似运算。
//
//
// 二、 运算符重载为成员函数 
//     a, 对于双目运算符B，如果要重载B为类的成员函数，使之能够实现表达式oprd1 B oprd2,其中oprd1为类A的对象，则应当把B重载为A类的成员函数，
//        该函数只有一个形参，形参的类型是oprd2所属的类型。经过重载后，表达式oprd1 B oprd2 就相当于函数调用oprd1.operator B(oprd2). 
//     b, 对于前置单目运算符U，如“-”（负号）等，如果要重载U为类的成员函数，用来实现表达式U oprd，其中oprd为A类的对象，则U应当重载为A类的成员函数，
//        函数没有形参。经过重载之后，表达式U oprd相当于函数调用oprd.operator U(). 
//     c, 对于后置运算符“++”和“--”，如果要将它们重载为类的成员函数，用来实现表达式oprd++或oprd--，其中oprd为A类的对象，那么运算符就应当重载为A类的成员函数，
//        这时函数要带有一个整型形参。重载之后，表达式oprd++和oprd--就想当于函数调用oprd.operator++(0)和oprd.operator--(0); 
//
// 运算符重载就是赋予已有的运算符多重含义。
// 通过重新定义运算符，使它能够用于特定类的对象执行特定的功能，这便增强了C++语言的扩充能力。
//
//
//
// 可以用作重载的运算符:
//     a, 算术运算符  ：+, -, *, /, %, ++, --;
//     b, 位操作运算符：&, |, ~, ^, <<, >>
//     c, 逻辑运算符  ：!, &&, ||;
//     d, 比较运算符  ：<, >, >=, <=, ==, !=;
//     e, 赋值运算符  ：=, +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=;
//     f, 其他运算符  ：[], (), ->, ,(逗号运算符), new, delete, new[], delete[], ->*。
// 下列运算符不允许重载：
//     [.], [*], [::], [?:], [sizeof]
//
// 三、 运算符重载后，优先级和结合性:
//     a, 用户重载新定义运算符，不改变原运算符的优先级和结合性。这就是说，对运算符重载不改变运算符的优先级和结合性，并且运算符重载后，也不改变运算符的语法结构，
//        即单目运算符只能重载为单目运算符，双目运算符只能重载双目运算符。
//  
// 四、 编译程序如何选用哪一个运算符函数:
//     a, 运算符重载实际是一个函数，所以运算符的重载实际上是函数的重载。编译程序对运算符重载的选择，遵循着函数重载的选择原则。当遇到不很明显的运算时，编译程序将去寻找参数相匹配的运算符函数。
//   
// 五、重载运算符有哪些限制:
//   (1) 不可臆造新的运算符。必须把重载运算符限制在C++语言中已有的运算符范围内的允许重载的运算符之中。
//   (2) 重载运算符坚持4个“不能改变”。
//       a, 不能改变运算符操作数的个数；
//       b, 不能改变运算符原有的优先级；
//       c, 不能改变运算符原有的结合性；
//       d, 不能改变运算符原有的语法结构。
//    
// 六、运算符重载时必须遵循哪些原则:
//    运算符重载可以使程序更加简洁，使表达式更加直观，增加可读性。但是，运算符重载使用不宜过多，否则会带来一定的麻烦。
//    (1) 重载运算符含义必须清楚。
//    (2) 重载运算符不能有二义性。
//    运算符重载函数的两种形式
//    运算符重载的函数一般地采用如下两种形式：
//       a, 成员函数形式和
//       b, 友元函数形式。
//    这两种形式都可访问类中的私有成员。
//

//
//  1. 重载为类的成员函数
//  这里先举一个关于给复数运算重载复数的四则运算符的例子。复数由实部和虚部构造，可以定义一个复数类，然后再在类中重载复数四则运算的运算符。
//  先看以下源代码：
#if __FUNCTION_MEMBER__
class complex
{
public:
    complex() 
    { 
       real = imag = 0; 
    }

    complex(double r, double i)
    {
       real = r, imag = i;
    }

    complex operator+(const complex &c);
    complex operator-(const complex &c);
    complex operator*(const complex &c);
    complex operator/(const complex &c);
    friend void print(const complex &c);

private:
    double real, imag;
};
 
inline complex complex::operator+(const complex &c)
{
    return complex(real + c.real, imag + c.imag);
}
 
inline complex complex::operator-(const complex &c)
{
    return complex(real - c.real, imag - c.imag);
}
 
inline complex complex::operator*(const complex &c)
{
    return complex(real * c.real - imag * c.imag, real * c.imag + imag * c.real);
}
 
inline complex complex::operator/(const complex &c)
{
    return complex((real * c.real + imag + c.imag) / (c.real * c.real + c.imag * c.imag),
                   (imag * c.real - real * c.imag) / (c.real * c.real + c.imag * c.imag));
}
 
void print(const complex &c)
{
    if( c.imag < 0 )
        cout << c.real << c.imag << 'i';
    else
        cout << c.real << ' + ' << c.imag << 'i';
}
 
int main(int argc, char *argv[])
{
    complex c1(2.0, 3.0), c2(4.0, -2.0), c3;
    c3 = c1 + c2;
    cout << " c1 + c2 = "; 
    print(c3) ;
    cout << endl;
    c3 = c1 - c2;
    cout << " c1 - c2 = ";
    print(c3) ;
    cout << endl;
    c3 = c1 * c2;
    cout << " c1 * c2 = " ;
    print(c3) ;
    cout << endl;
    c3 = c1 / c2;
    cout << " c1 / c2 = " ;
    print(c3) ;
    cout << endl;
    c3 = ( c1 + c2 ) * ( c1 - c2 ) * c2 / c1;
    cout << " ( c1 + c2 ) * ( c1 - c2 ) * c2 / c1 = ";
    print(c3) ;
    cout << endl;

    return 0;
}
#endif

// 该程序的运行结果为：
//  c1 + c2 = 6 + 1i
//  c1 - c2 = -2 + 5i
//  c1 * c2 = 14 + 8i
//  c1 / c2 = 0.45 + 0.8i
//  ( c1 + c2 ) * ( c1 - c2 ) * c2 / c1 = 9.61538 + 25.2308i
// 在程序中，类complex定义了4个成员函数作为运算符重载函数。将运算符重载函数说明为类的成员函数格式如下：
// <类名＞ operator <运算符＞(<参数表＞)
// 其中，operator是定义运算符重载函数的关键字。
// 程序中出现的表达式：
//     c1 + c2
// 编译程序将给解释为：
//     c1.operator+(c2)
// 其中，c1和c2是complex类的对象。operator+()是运算+的重载函数。
// 该运算符重载函数仅有一个参数c2。可见，当重载为成员函数时，双目运算符仅有一个参数。
//     对单目运算符，重载为成员函数时，不能再显式说明参数。重载为成员函数时，总时隐含了一个参数，该参数是this指针。this指针是指向调用该成员函数对象的指针。
//
//



// 2. 重载为友元函数:
//    运算符重载函数还可以为友元函数。
//    当重载友元函数时，将没有隐含的参数this指针。
//    a, 这样，对双目运算符，友元函数有2个参数，
//    b, 对单目运算符，友元函数有一个参数。
//
//    但是，有些运行符不能重载为友元函数，
//    它们是：
//        1, =,
//        2, (), 
//        3, []和 
//        4, ->。
//
//    重载为友元函数的运算符重载函数的定义格式如下：
//  
//    friend <类型说明符＞ operator <运算符＞(<参数表＞)
//    {……}
//
//    下面用友元函数代码成员函数，重载编写上述的例子，程序如下：
//
//
#if __OVERLOAD_FRIEND_FUN__
class complex
{
public:
    complex() 
    { 
        real=imag=0; 
    }
    complex(double r, double i)
    {
        real = r, imag = i;
    }
    friend complex operator+(const complex &c1, const complex &c2);
    friend complex operator-(const complex &c1, const complex &c2);
    friend complex operator*(const complex &c1, const complex &c2);
    friend complex operator/(const complex &c1, const complex &c2);
    friend void print(const complex &c);
private:
    double real, imag;
};
 
complex operator+(const complex &c1, const complex &c2)
{
    return complex(c1.real + c2.real, c1.imag + c2.imag);
}
 
complex operator-(const complex &c1, const complex &c2)
{
    return complex(c1.real - c2.real, c1.imag - c2.imag);
}
 
complex operator*(const complex &c1, const complex &c2)
{
    return complex(c1.real * c2.real - c1.imag * c2.imag, c1.real * c2.imag + c1.imag * c2.real);
}
 
complex operator/(const complex &c1, const complex &c2)
{
    return complex((c1.real * c2.real + c1.imag * c2.imag) / (c2.real * c2.real + c2.imag * c2.imag),
                   (c1.imag * c2.real - c1.real * c2.imag) / (c2.real * c2.real + c2.imag * c2.imag));
}
 
void print(const complex &c)
{
    if(c.imag<0)
        cout << c.real << c.imag << 'i';
    else
        cout << c.real << '+' << c.imag << 'i';
}
 
int main(int argc, char *argv[])
{
    complex c1(2.0, 3.0), c2(4.0, -2.0), c3;
    c3 = c1 + c2;
    cout<<" c1+c2= ";
    print(c3);
    cout << endl;
    c3 = c1 - c2;
    cout<<" c1-c2= ";
    print(c3);
    cout << endl;
    c3 = c1 * c2;
    cout<<" c1*c2= ";
    print(c3);
    cout << endl;
    c3 = c1 / c2;
    cout<<" c1/c2= ";
    print(c3);
    cout << endl;
    c3 = (c1+c2) * (c1-c2) * c2/c1;
    cout<<" (c1+c2)*(c1-c2)*c2/c1=";
    print(c3);
    cout << endl;
}
#endif

//  该程序的运行结果与上例相同。
//   1, 前面已讲过，对又目运算符，重载为成员函数时，仅一个参数，
//   2, 另一个被隐含；重载为友元函数时，有两个参数，没有隐含参数。
//
// 因此，程序中出现的 c1 + c2 编译程序解释为：
//     operator+(c1, c2)
// 调用如下函数，进行求值，
//     complex operator +(const coplex &c1, const complex &c2)
//
//
//  3. 两种重载形式的比较
//  一般说来，
//      a, 单目运算符最好被重载为成员；
//      b, 对双目运算符最好被重载为友元函数，双目运算符重载为友元函数比重载为成员函数更方便此，
//  但是，有的双目运算符还是重载为成员函数为好，例如，赋值运算符。因为，它如果被重载为友元函数，将会出现与赋值语义不一致的地方。 其他运算符的重载举例
//
//
//
//  1).下标运算符重载
//  由于C语言的数组中并没有保存其大小，因此，不能对数组元素进行存取范围的检查，无法保证给数组动态赋值不会越界。i
//  利用C++的类可以定义一种更安全、功能强的数组类型。为此，为该类定义重载运算符[]。
//  下面一个例子：
//   
#if __HAS_LENGTH_ARRAY__
class CharArray
{
public:
    CharArray(int l)
    {
        Length = l;
        Buff = new char[Length];
    }

    ~CharArray() 
    {
        delete Buff; 
    }

    int GetLength() 
    {
        return Length; 
    }

    char& operator[](int i);

private:
    int Length;
    char * Buff;
};
 
char& CharArray::operator[](int i)
{
    static char ch = 0;
    if( i < Length && i >= 0 )
        return Buff[i];
    else
    {
        cout << "Index out of range." << endl;
        return ch;
    }
}
 
int main(int argc, char *argv[])
{
    int cnt;
    CharArray string1(6);
    const char* string2 = "string";
    for( cnt = 0; cnt < 8; cnt++ )
        string1[cnt] = string2[cnt];
    for( cnt = 0; cnt < 8; cnt++ )
         cout << string1[cnt] << endl;
    cout << endl;
    cout << string1.GetLength() << endl;
    return 0;
}
#endif

// 该数组类的优点如下：
// (1) 其大小不一定是一个常量。
// (2) 运行时动态指定大小可以不用运算符new和delete。
// (3) 当使用该类数组作函数参数时，不心分别传递数组变量本身及其大小，因为该对象中已经保存大小。
//
//
// 在重载下标运算符函数时应该注意：
// (1) 该函数只能带一个参数，不可带多个参数。
// (2) 不得重载为友元函数，必须是非static类的成员函数。 2). 重载增1减1运算符.
// 增1减1运算符是单目运算符。它们又有前缀和后缀运算两种。为了区分这两种运算，将后缀运算视为又目运算符。表达式
//     obj++或obj--
// 被看作为：
//     obj++0或obj--0
// 下面举一例子说明重载增1减1运算符的应用。
//  
//
#if __OVERLOAD_PLUSPLUS__
class counter
{
public:
    counter() 
    {
       v = 0; 
    }

    counter operator++();
    counter operator++(int);
    void print() 
    {
        cout << v << endl; 
    }
private:
    unsigned v;
};
 
counter counter::operator++()
{
    v++;
    return *this;
}
 
counter counter::operator++(int)
{
    counter t;
    t.v = v++;
    return t;
}
 
int  main(int argc, char *argv[])
{
    counter c;
    for( int i = 0; i < 8; i++ )
        c++;
    c.print();
    for( int i = 0; i < 8; i++ )
        ++c;
    c.print();
    return 0;
}
#endif 
// 3). 重载函数调用运算符
// 可以将函数调用运算符()看成是下标运算[]的扩展。函数调用运算符可以带0个至多个参数。下面通过一个实例来熟悉函数调用运算符的重载。
class F
{
public:
    double operator()(double x, double y) const;
};
 
double F::operator()(double x, double y) const
{
    return ( x + 5 ) * y;
}
 
int  main(int argc, char *argv[])
{
    F f;
    cout << f(1.5, 2.2) << endl;
    return 0;
}
