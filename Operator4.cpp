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
        cout << x << " , " << y << endl;
    }
    int GetX() const
    {
        return x;
    }
    int GetY() const
    {
        return y;
    }
};

const Point operator-(const Point &argL, const Point &argR)
{
    return Point(argL.GetX() - argR.GetX(), argL.GetY() - argR.GetY());
}