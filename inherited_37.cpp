#include <iostream>

using namespace std;

// 绝对不要重新定义一个继承而来的缺省参数值,因为缺省的参数值都是静态绑定的
// 而virtual函数----你唯一应该覆写的东西却是动态绑定
//
// 缺省参数静态绑定的原因是: 为了程序的执行速度和编译器实现上的简易度.
//

class Shape
{
public:
    enum ShapeColor {Red, Green, Blue};
    void draw(ShapeColor color = Red ) const  //如今他是non-virtual调用一个virtual
    {
        doDraw(color);
    }

private:
    virtual void doDraw(ShapeColor color) const = 0;  //真正的工作在此完成
};

class Rectangle : public Shape
{
public:
private:
    virtual void doDraw(ShapeColor color) const
    {
        cout << "Rectangle: " << color << endl;
    }
   
};

class Circle: public Shape
{
public:
private:
    virtual void doDraw(ShapeColor color) const
    {
        cout << "Circle: " << color << endl;
    }
   
};

int main(int argc, char *argv[])
{
    Shape *ps;
    // 动态绑定指向Circle*
    Shape *pc = new Circle;
    // 动态绑定执行Rectangle*
    Shape *pr = new Rectangle;

    ps = pc;               //ps 动态绑定指向Circle*
    ps = pr;               //ps 动态绑定指向Rectangle*


    pc->draw(Shape::Red);   // 调用Circle::draw(Shape::Red)
    pr->draw(Shape::Green);   // 调用Rectangle::draw(Shape::Green)

    pc->draw();    //默认的参数调用的是基类的参数 
    pr->draw();  
    
    return 0;
}
