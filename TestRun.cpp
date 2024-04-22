#include <iostream>
#include <string>

class TestRun
{
  public:
    TestRun() = default;
    TestRun(const TestRun &) = delete;
    TestRun(std::string name);
};