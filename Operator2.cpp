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
    const Point operator+(const Point &arg) const
    {
        Point pt;
        pt.x = this->x + arg.x;
        pt.y = this->y + arg.y;
        return pt;
    }
};

int main()
{
    return 0;
}