#include <iostream>

using namespace std;
class Base
{
public:
    Base()
    {
        cout << "Base" << endl;
    };

    virtual ~Base()
    {
        cout << "~Base" << endl;
    };
};

class Derived:public Base
{
public:
    Derived()
    {
        cout << "Derived" << endl;
    };

    ~Derived()
    {
        cout << "~Derived" << endl;
    };
};

int main(int argc, char *argv[])
{
    Base b;
    Derived d;
    cout << "=================================" << endl;

    return 0;
}
