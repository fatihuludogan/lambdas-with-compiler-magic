#include <functional>
#include <memory>

template <typename T>
class function;

template <typename Ret, typename... Param>
class function<Ret(Param...)>
{
public:
  /* function interface (no longer need)
  function(Ret (*fp)(Param...))
    : callable{std::make_unique<callable_impl<Ret (*)(Param...)>>(fp)} {};
  */
  template <typename FunctionObject>
  function(FunctionObject fo)
    : callable{
        std::make_unique<callable_impl<FunctionObject>>(std::move(fo))} {};

  //? forwarding and unwrapping of std::reference_wrapper
  Ret operator()(Param... param)
  {
    return callable->call(param...);
  };
  //? copy constructor

private:
  struct callable_interface
  {
    virtual Ret call(Param...) = 0;
    virtual ~callable_interface() = default; // unpack the parameters
    //TODO: finish Rule Of 5
    //? virtual clone()
  };

  template <typename Callable>
  struct callable_impl : callable_interface
  {
    callable_impl(Callable callable_) : callable{std::move(callable_)} {};
    Ret call(Param... param)
    {
      return std::invoke(callable, param...);
    }
    Callable callable;
  };

  std::unique_ptr<callable_interface> callable;
};

int fp(int x, int y)
{
  return x + y;
}

int main()
{

  function<int(int, int)> func{[z = 42](int x, int y) { return x + y + z; }};
  function<int(int, int)> func2{fp};
  return func(1, 2) + func2(3, 4);
}