#include <iostream>

using namespace std;


// 多继承比单一继承复杂.他可能导致新的歧义性,以及对virtual继承的需要
// virtual 继承会增加大小,速度,初始化(及赋值)复杂度等等成本,如果virtual base classes不带任何数据,将是最实用的情况
//
// 多继承的确有他的正当性,其中一个情节涉及"public继承某个Interface class"和"private 继承某个协助实现的class"的两相结合
//

class IPerson                                      // 这个类指出需实现的接口
{
public:
    virtual ~IPerson();
    virtual std::string name() const = 0;
    virtual std::string birthDate() const = 0;
};

class DatabaseID
{
};

class PersonInfo
{
public:
    explicit PersonInfo(DatabaseID pid);

    virtual ~PersonInfo();

    virtual const char* theName() const
    {
        cout << "PersonInfo : theName" << endl;
        return "";
    };

    virtual const char* theBirthDate() const
    {
        cout << "PersonInfo : theBirthDate" << endl;
        return "";
    };

    virtual const char* valueDelimOpen() const
    {
        cout << "PersonInfo : valueDelimOpen" << endl;
        return "";
    };

    virtual const char* valueDelimClose() const
    {
        cout << "PersonInfo : valueDelimClose" << endl;
        return "";
    };

};

class CPerson: public IPerson, private PersonInfo            // 多重继承
{
public:
    explicit CPerson(DatabaseID pid): PersonInfo(pid) {};
    virtual std::string name() const                         // 实现必要的IPerson成员函数
    {
        cout << "CPerson : name " << endl;
        return PersonInfo::theName();
    };

    virtual std::string birthDate() const                    // 实现必要的IPerson成员函数
    {
        cout << "CPerson : birthDate " << endl;
        return PersonInfo::theBirthDate();
    };

private:
    const char * valueDelimOpen() const                       // 重新定义继承而来的virtual "界限函数"
    { 
        cout << "CPerson : valueDelimOpen " << endl;
        return "";
    }

    const char * valueDelimClose() const                      // 重新定义继承而来的virtual "界限函数"
    {
        cout << "CPerson : valueDelimClose " << endl;
        return "";
    }
};

int main(int argc, char *argv[])
{
    DatabaseID pid;
    CPerson mPerson(pid);
    //mPerson.name();
    //mPerson.birthDate();
    return 0;
}
