#include <iostream>

using namespace std;
// 明智而审慎的使用private继承
//
//
// 私有继承的行为:
// a, 如果classes之间的继承是私有的private,编译器不会自动将一个derived class对象转换为base class对象
// b, 有private继承而来的所有成员,在derived class中都会变成private属性,纵使他们在base class中原本是protected或是public属性
//
//  private继承意味着只有实现部分被继承,接口部分应略去
//  如果D以private形式继承B,意思是D对象根据B对象的实现而得,而没有其他意涵了.
//
//
//  由于复合的意义和private相同,在两者间选择尽量选择复合,必要时选择private继承,
//  必要时主要是在当protected成员和/或virtual函数牵扯进来的时候使用private继承.
//
//

//class Timer
//{
//public:
//    explicit Timer(int tickFrequency);
//    virtual void onTick() const;                     // 定时器每滴答一次,此函数就自动调用一次
//
//};
//
//class Widge : private Timer
//{
//private:
//    // 在派生类中私有继承而来的成员都会变为私有,此函数放进public会误导客户端调用此函数
//    virtual void onTick() const;                     // 查看Widget的数据...等等
//};

//// 使用public 继承加复合实现方式实现
//class Widget 
//{
//public:
//    class WidgetTimer:public Timer
//    {
//    public:
//        virtual void onTick() const;
//
//    };
//
//    WidgetTimer timer;
//};


// private继承主要用于"当一个意欲成为derived class者想访问一个意欲成为base class者的protected成分
// 或为了重新定义一个或多个virtual函数."
class Empty {};                   // 没有数据,所以其对象应该不使用任何内存(实际编译器会默默的安插一个char)
class HoldsAnInt                  // 应该需要一个int空间
{
private:
    int x;
    Empty e;                      // 应该不需要任何空间(实际编译器会默默安插一个char)
};
//  但是,sizeof(HoldsAnInt) > sizeof(int)
//  在大多数编译器中sizeof(Empty)获得1,因为面对"大小为0之独立(非附属)对象".通常C++
//  官方勒令默默安插一个char到空对象内,然而对齐位要求,可能造成编译器为类似HoldsAnInt这样的类
//  加些蹭点,实际上sizeof(Empty)为一个int 4
//
//  派生类中的private继承的Empty并非独立(非附属) 的 
class HoldsAnInt2: private Empty
{
private:
    int x;
};
// 几乎可以确定上面代码的sizeof(HoldsAnInt) == sizeof(int)
// 这是所谓的EBO(empty base optization;空白基类最优化),如果对空间很在意的话那么值得注意EBO
// EBO只有在单一继承(而非多继承)下才可行


int main(int argc, char *argv[])
{
    Empty mEmpty;          // 默认安插一个char到空间
    HoldsAnInt mInt;       // 对齐
    HoldsAnInt2 mInt2;     // EBO
    cout << sizeof(mEmpty) << endl;
    cout << sizeof(mInt)  << endl;
    cout << sizeof(mInt2)  << endl;
    return 0;
}
