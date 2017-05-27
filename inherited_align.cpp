#include <iostream>
using namespace std;

// 内存对齐
// 内存对齐是编译器为便于cpu快速访问而使用的一项技术
//
// eg.
// class node
// {
//    char c;
//    int i;
//    short s;
// }no;
//
// sizeof(no) == 12  (内存对齐的结果)
//
//
// 内存对齐的原因:
// a, 平台原因(移植原因): 不是所有平台都能够访问不能地址的不同数据,某些硬件平台只能在特定的地址取特定的数据,否则会报硬件异常
// b, 性能原因: 数据结果(尤其是栈)应尽可能的自然边界对齐,原因在于,为了访问未自然边界对齐的内存,处理器需要两次访问,而对齐的内存只需要一次访问
//
// 编译器默认是按类中最大类型长度来对齐,也可以使用  
//  #program pack(i)  (i = 1,2,4,8,16)
// 来设置对齐字节数目
//
//  Basically the compiler unless otherwise directed will line up structure members on
//  2 byte or 4 byte boundaries - this makes it easier and faster for the processor to handle.
//  So the structure contains secret padding bytes to make this happen.
//
//  The pragma pack directive (in MS Compiler) allows you to change this alignment scheme.
//
//  Some things (particularly in relation to hardware) do not have the luxury to waste bytes like
//  this and they send their data in an exact fit.
//  This means that it is not wise to read data from a hardware device directly into a normal structure.
//
//  If you have want to read data that is an exact fit into a structure - you can tell the compiler
//  to make the structure an exact fit like this (microsoft compiler);
//  #pragma pack(push, 1) // exact fit - no padding
//  struct MyStruct
//  {
//      char b; 
//      int a; 
//      int array[2];
//  };
//  #pragma pack(pop) //back to whatever the previous packing mode was
//  Without the pragma directive, the size of the structure is 16 bytes - with the packing of 1 - the size is 13 bytes
//
//
// 对齐规则:
// a, 如果设置了内存对齐为 i 字节，类中最大成员对齐字节数为j，那么整体对齐字节n = min(i, j)  （某个成员的对齐字节数定义：
//    如果该成员是c++自带类型如int、char、double等，那么其对齐字节数=该类型在内存中所占的字节数；如果该成员是自定义类型
//    如某个class或者struct，那个它的对齐字节数 = 该类型内最大的成员对齐字节数《详见实例4》）
//
// b, 每个成员对齐规则：类中第一个数据成员放在offset为0的位置；对于其他的数据成员（假设该数据成员对齐字节数为k），
//    他们放置的起始位置offset应该是 min(k, n) 的整数倍
//
// c, 整体对齐规则：最后整个类的大小应该是n的整数倍
//
// d, 当设置的对齐字节数大于类中最大成员对齐字节数时，这个设置实际上不产生任何效果（实例2）；当设置对齐字节数为1时，类的大小就是简单的把所有成员大小相加
//
//


// eg:
//  没有指定对齐字节数,则n为最大成员(int )的大小4
// 
class node1
{
    char c;      //放在位置0，位置区间[0]
    int i;       //4 = n, 那么放置起始位置应该是4的倍数，即4，位置区间为[4~7]
    short s;     //2 < n，那么放置起始位置应该是2的倍数，即8，位置区间为[8~9]
};
// result: 此时成员共占用[0~9]10个字节，还要整体对齐，大小应该是4的倍数，即12

// eg2:
//  假设指定对齐字节为8，那么n = min(8,4) = 4）
#pragma pack(push, 8)
class node2
{
    int i;       //放在位置0，位置区间[0~3]
    char c;      //1 < n, 那么放置起始位置应该是1的倍数，即4，位置区间为[4]
    short s;     //2 < n，那么放置起始位置应该是2的倍数，即6，位置区间为[6~7]
};
#pragma pack(pop)
// 成员共占据[0~7]8个字节，刚好是4的倍数，因此大小是8

// eg3:
//  （假设指定对齐字节是2，则n = min(2,4) = 2）
#pragma pack(push, 2)
class node3
{
    char c; //放在位置0，位置区间[0]
    int i; //4 > n, 那么放置起始位置应该是2的倍数，即2，位置区间为[2~5]
    short s; //2 = n，那么放置起始位置应该是2的倍数，即6，位置区间为[6~7]
};
#pragma pack(pop)
// 此时成员共占用[0~7]8个字节，刚好是4的倍数，因此大小是8

//eg4:
//（按照默认设置）
class temp 
{ 
    char c; 
    int i; 
    short s1; 
};
// 由实例1可知，默认对齐情况下，temp的大小是12，temp的对齐字节数是：三个成员取最大的，即为4；
// 对于node，n = 其三个成员对齐字节数取最大，即等于t的对齐字节数，也就是 4。
class node4
{
    char c; //放在位置0，位置区间[0]
    temp t; //4（temp的对齐字节数） = n, 那么放置起始位置应该是4的倍数，即4，位置区间为[4~15]
    short s; //2 < n，那么放置起始位置应该是2的倍数，即16，位置区间为[16~17]
};
// 此时成员共占用[0~17]18个字节，还要整体对齐，大小应该是4的倍数，因此大小是20

// eg5:
//（默认设置）
// 对于node，n = 其三个成员对齐字节数取最大，即等于d的对齐字节数，也就是 8。
class node5
{
    temp t; //放在位置0，位置区间[0~11]
    double d; //8（temp的对齐字节数） = n, 那么放置起始位置应该是8的倍数，即16，位置区间为[16~23]
    short s; //2 < n，那么放置起始位置应该是2的倍数，即24，位置区间为[24~25]
};
// 此时成员共占用[0~25]26个字节，还要整体对齐，大小应该是8的倍数，因此大小是32.

// eg6:
// 类继承时的内存对齐
// 考虑如下类
class A
{
    int i;
    char c1;
};

class B:public A
{
    char c2;
};

class C:public B
{
    char c3;
};

//  sizeof(C)结果是多少呢，gcc和vs给出了不同的结果，分别是8、16
//  gcc中：C相当于把所有成员i、c1、c2、c3当作是在一个class内部，(先继承后对齐)
//  vs中：对于A，对齐后其大小是8；对于B，c2加上对齐后的A的大小是9，对齐后就是12；对于C，c3加上对齐后的B大小是13，再对齐就是16 (先对齐后继承)

int main()
{
    cout << "sizeof(node1) : " << sizeof(node1) << endl;
    cout << "sizeof(node2) : " << sizeof(node2) << endl;
    cout << "sizeof(node3) : " << sizeof(node3) << endl;
    cout << "sizeof(node4) : " << sizeof(node4) << endl;
    cout << "sizeof(node5) : " << sizeof(node5) << endl;
    cout << "sizeof(C) : " << sizeof(C) << endl;
    return 0;
}

