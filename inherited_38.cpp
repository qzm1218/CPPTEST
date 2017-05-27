#include <iostream>
#include <algorithm>   // std::find
#include <list>

using namespace std;


// 
// 通过复合塑模出has-a 或 根据某物实现出
// 复合是类型之间的一种关系,当某种类型的对象内含他中类型的对象
//
// a, 在应用域,复合意味着 has-a(有一个).
// b, 在实现域,复合意味着is-implemented-in-terms-of (根据某物实现出)


// a, 通过复合实现has-a
// class Address{};                               // 某人的住址
// class PhoneNumber{};                           // 某人的电话
// class Person
// {
// public:
//     
// private:
//     std::string name;                          // 合成成分物
//     Address address;                           // 同上
//     PhoneNumber voiceNumber;                   // 同上
//     PhoneNumber faxNuber;                      // 同上
// }

// 将list应用于set
// b, 根据list实现出set
template <class T>
class Set
{
public:
    bool member(const T& item) const;
    void insert(const T& item);
    void remove(const T& item);
    std::size_t size() const;

private:
    std::list<T> rep;      // 用于表述set的数据
};

// template<class T> class Widget;    // 使用"class"
// template<typename T> class Widget;  // 使用"typename"
// 在声明template类型参数时,class和typename的意义完全相同.
//
//
// 条款42: 
// 1, 声明template参数时,前缀关键字class和typename可互换
// 2, 请使用关键字typename表示嵌套从属类型名称;但不得在base class lists(基类列)
// 或 member initialization list(成员初始列)内以他作为base class修饰符
//
// eg:
//    template<typename C>               // 允许使用"typename"(或"class")
//    void f(const C& container,         // 不允许使用"typename"
//           typename C::iterator iter); // 一定要使用"typename"(嵌套从属类型名称) 
//
// eg:
//    template<typename T>                            
//    class Derived: public Base<T>::Nested {         // base class list 中,不允许使用"typename"
//    public:
//        explicit Derived(int x)
//        : Base<T>::Nested(x)                        // mem.init.list 中,不允许使用"typename"
//        {
//            typename Base<T>::Nested temp;          // 嵌套从属类型名称.即不在base class list也不在mem init list中,作为base class修饰符必须加上typename
//
/////////////////////////////////////////////////////////
//            typedef typename Base<T>::Nested nestd;  //通过typedef 重新定义一个类型,可以少打写代码.
//            nestd temp;
//        }
//
template <typename T>
bool Set<T>::member(const T& item) const
{
    return std::find(rep.begin(), rep.end(), item) != rep.end();
}

template <typename T>
void Set<T>::insert(const T& item)
{
    if ( !member(item) )  rep.push_back(item);
}

template <typename T>
void Set<T>::remove(const T& item)
{
    // 属于嵌套从属类型,必须加上typename
    typename std::list<T>::iterator it = std::find(rep.begin(), rep.end(), item);

    if ( it != rep.end() )  rep.erase(it);
}


template <typename T>
std::size_t Set<T>::size() const
{
    return rep.size();
}

int main(int argc, char *argv[])
{
    Set<int> mSet;
    mSet.insert(1);
    mSet.insert(2);
    mSet.insert(3);
    std::cout << mSet.member(1) << endl; 
    std::cout << mSet.member(2) << endl; 
    std::cout << mSet.member(3) << endl; 
    mSet.remove(2);
    std::cout << mSet.member(1) << endl; 
    std::cout << mSet.member(2) << endl; 
    std::cout << mSet.member(3) << endl; 
  
    return 0;
}
