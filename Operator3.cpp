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

    const Point &operator--()
    {
        --x;
        --y;
        return *this;
    }

    const Point operator--(int)
    {
        Point pt(x, y);
        --x;
        --y;
        return pt;
    }
    const Point &operator++()
    {
        ++x;
        ++y;
        return *this;
    }

    const Point operator++(int)
    {
        Point pt(x, y);
        ++x;
        ++y;
        return pt;
    }

    bool operator==(const Point &arg) const
    {
        return x == arg.x && y == arg.y ? true : false;
    }

    bool operator!=(const Point &arg) const
    {
        return !(*this == arg);
    }
};

class Point2
{
    int x;
    int y;

  public:
    Point2(int x = 0, int y = 0) : x(x), y(y)
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

    const Point operator-(const Point2 &arg) const
    {
        return Point(x - arg.x, y - arg.y);
    }
};