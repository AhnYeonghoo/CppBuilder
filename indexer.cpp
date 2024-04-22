#include <iostream>
using namespace std;

class Point
{
    int x;
    int y;

  public:
    Point(int x = 0, int y = 0) : x(x), y(y)
    {
    }
    void Print() const
    {
        cout << x << "," << y << endl;
    }

    int operator[](int idx) const
    {
        if (idx == 0)
            return x;
        else if (idx == 1)
            return y;
        else
            throw "이럴 수는 없어!";
    }
};