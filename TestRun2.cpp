#include <iostream>
#include <string>

class TestRun
{
  public:
    TestRun() = default;
    TestRun(const TestRun &) = delete;
    TestRun(std::string name);
    void DoSomething();
    int Calculate(int a, double d);
    virtual ~TestRun();
    enum class State
    {
        Active,
        Suspended
    };

  protected:
    virtual void Initialize();
    virtual void Suspend();
    State GetState();

  private:
    State _state{State::Suspended};
    std::string _testName{""};
    int _index{0};
    static int _instances;
};

int TestRun::_instances{0};

class CanInit
{
  public:
    long num{7};
    int k = 9;
    static int i = 9;

    CanInit()
    {
    }
    CanInit(int val) : num(val)
    {
    }
};