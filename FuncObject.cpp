#include <iostream>

using namespace std;

struct FuncObject
{
  public:
    void operator()(int arg) const
    {
        cout << "정쉬: " << arg << endl;
    }
};

void Print1(int arg)
{
    cout << "정수: " << arg << endl;
}