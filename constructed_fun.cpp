#include <iostream>
#include <string.h>

//
//http://www.cnblogs.com/Winston/archive/2008/06/03/1212700.html
//
using namespace std;

class Point
{
public:
    /////////////////////////////////////////////
    // 构造函数的作用:
    // 1,给创建的对象建立一个标识符
    // 2,为对象数据成员开辟内存空间
    // 3,完成对象数据成员的初始化
    // 默认构造函数:
    // 1,默认构造函数不能完成对象数据成员的初始化, 只能给对象创建一标识符, 并为对象中的数据成员开辟一定的内存空间。
    // 构造函数的特点:
    // 1,在对象被创建时自动执行
    // 2,构造函数的函数名与类名相同
    // 3,没有返回值类型、也没有返回值
    // 4,构造函数不能被显式调用
    /////////////////////////////////////////////
    
    // 无参构造函数
#if NO_ARGMENT
    Point()
    {
        cout<<"调用初始化表对数据成员进行初始化!\n";
    };

    ~Point()
    {

    };

#elif TWO_DEFAULT_ARGMENT 
    // 对象中的一些数据成员除了在构造函数体中进行初始化外还可以通过调用初始化表来进行完成, 
    // 要使用初始化表来对数据成员进行初始化时使用 : 号进行调出,在 Point 构造函数头的后面, 
    // 通过单个冒号 : 引出的就是初始化表, 初始化的内容为 Point 类中int型的 xPos 成员和 
    // yPos成员, 其效果和 xPos = x; yPos = y; 是相同的与在构造函数体内进行初始化不同的是, 
    // 使用初始化表进行初始化是在构造函数被调用以前就完成的。每个成员在初始化表中只能出现一次, 
    // 并且初始化的顺序不是取决于数据成员在初始化表中出现的顺序, 而是取决于在类中声明的顺序
    // 此外, 一些通过构造函数无法进行初始化的数据类型可以使用初始化表进行初始化, 如: 常量成员和引用成员
    Point(int x = 0, int y = 0):xPos(x),yPos(y)
    {
        cout<<"调用初始化表对数据成员进行初始化!\n";
    }

    ~Point()
    {

    };

    Point(const Point& org)
    {
        xPos = org.xPos;
        yPos = org.yPos;
    };

    Point& operator=(const Point& org)
    {
        xPos = org.xPos;
        yPos = org.yPos;
        return *this;
    };

    void PrintPoint()
    {
        cout<<"xPos = " << xPos <<endl;
        cout<<"yPos = " << yPos <<endl;
    };
#else 

    Point(int x = 0, int y = 0, const char *name = ""):xPos(x),yPos(y),m_pName(NULL)
    {
        m_pName = new char[strlen(name) + 1];
        strcpy(m_pName, name);
        cout<<"调用初始化表对数据成员进行初始化!\n";
        count++;
    } 

    ~Point()
    {
        delete [] m_pName;
        cout<<"析构函数!\n";
        count--;
    };

    Point(const Point& org)
    {
        xPos = org.xPos;
        yPos = org.yPos;
        
        m_pName = new char[strlen(org.m_pName) + 1];

        if ( m_pName != NULL )
            strcpy(m_pName, org.m_pName);
        count++;

    };

    //  如果赋值函数返回的是void ，我们知道，其唯一一点需要注意的是，其不支持链式赋值运算，即a=b=c这样是不允许的
    //   对于返回的是类对象本身，还是类对象的引用，其有着本质的区别
    Point& operator=(const Point& org)
    {
        //  问：什么需要判断这个条件？（不是必须，只是优化而已）。答案：提示：考虑a=a这样的操作
        if ( this == &org )
            return *this;

        xPos = org.xPos;
        yPos = org.yPos;
        
        if ( m_pName != NULL )
            delete m_pName;

        m_pName = new char[strlen(org.m_pName) + 1];
        if ( m_pName != NULL )
            strcpy(m_pName, org.m_pName);

        return *this;
    };

    void PrintPoint()
    {
        cout<<"xPos = " << xPos <<endl;
        cout<<"yPos = " << yPos <<endl;
        cout<<"m_pName = " << m_pName <<endl;
    };

    void SetPointX(int x)
    {
        xPos = x;
    };

    void SetPointY(int y)
    {
        yPos = y;
    };

    void SetPointName(const char *name)
    {
        if ( m_pName != NULL )
            strcpy(m_pName, name);
    };

    static int GetCount()
    {
        return count;
    };
#endif
    

private:
    int xPos;
    int yPos;
    char *m_pName;
    static int count;
};


int Point::count = 0;

int main(int argc, char *argv[])
{
#if NO_ARGMENT
    Point m_Point;
#endif

#if TWO_DEFAULT_ARGMENT 
    Point m_Point;
    m_Point.PrintPoint();

    Point m_Point1(1);
    m_Point1.PrintPoint();

    Point m_Point2(1,2);
    m_Point2.PrintPoint();


    Point m_Point3(m_Point2);
    m_Point3.PrintPoint();

    Point m_Point4;
    m_Point4 = m_Point1;
    m_Point4.PrintPoint();
#endif
    
    cout << "count 0:" << Point::GetCount() << endl;
    {
        Point m_Point(1, 2, "qzm");
        m_Point.PrintPoint();

        Point m_Point1(m_Point);
        m_Point1.PrintPoint();

        Point m_Point2(3,4,"name");
        Point m_Point3;
        m_Point3 = m_Point2;
        m_Point3.PrintPoint();


        cout << "------------------------------------" << endl;

        cout << "count 1:" << Point::GetCount() << endl;
        Point *m_P1 = new Point(5, 5, "P1");
        Point *m_P2 = m_P1;
        m_P1->PrintPoint();
        m_P2->PrintPoint();
        m_P2->SetPointX(6);
        m_P2->SetPointY(6);
        m_P2->SetPointName("ttt");
        m_P1->PrintPoint();
        m_P2->PrintPoint();
        cout << "count 2:" << Point::GetCount() << endl;
        delete m_P1;
        cout << "count 3:" << Point::GetCount() << endl;
        delete m_P2;
        cout << "count 4:" << Point::GetCount() << endl;
        m_P2->SetPointX(7);
        m_P2->SetPointY(7);
        m_P2->SetPointName("ddd");
        m_P1->PrintPoint();
        m_P2->PrintPoint();
        
        cout << "count 5:" << Point::GetCount() << endl;
        cout << "------------------------------------" << endl;
    }
    cout << "count 6:" << Point::GetCount() << endl;
    return 0;
}
