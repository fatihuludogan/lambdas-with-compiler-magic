#include "magic-w-lambdas.hpp"

void lambda()
{
  auto l = []([[maybe_unused]] int value, int &value2) noexcept -> long {
    return ++value + value2++;
  };
  long (*fp)(int, int &) = l;
}

void lambda1()
{
  auto l1 =
    [] [[nodiscard]] (std::floating_point auto... value) noexcept -> long {
    return (value + ...);
  };

  auto result = l1(1.0, 2.1, 3.2, 4.3, 5.4);
}

void lambda2()
{
  auto l2 = []<std::size_t... Idx>(std::index_sequence<Idx...>) noexcept->long
  {
    return (Idx + ...);
  };

  auto result = l2(std::make_index_sequence<10>());
}

void lambda3()
{
  auto sum_tuple = []<typename... T>(const std::tuple<T...> &input) {
    return
      []<std::size_t... Idx>(std::index_sequence<Idx...>, const auto &tuple)
    {
      return (std::get<Idx>(tuple) + ...);
    }
    (std::make_index_sequence<sizeof...(T)>(), input);
  };
  auto result = sum_tuple(std::make_tuple(1, 2ll, 3l, 4.5));
}

auto lambda4()
{
  int i = 42;
  int j = 24;
  auto l = [i, &j]() mutable {
    ++j;
    return ++i;
  };
  l();
  auto l2 = l;
  l();
}

auto lambda5()
{
  auto l = [a = 1, b = true, c = 2, d = false]() {};
}

auto lambda6()
{
  const auto data = [](int i) { return std::vector<int>{1, 2, 3, 4, i}; }(42);
}

/* This is C++23 feature most of the compilers didn't have the C++ 23 support
auto lambda7()
{
  const auto data = [](this auto self, int i) {
    if (i > 0)
    {
      return i + self(i - 1);
    }
    else
    {
      return i;
    }
  }(10);
}
*/

// adding ref causes undefined behaviour because value is function parameter (dangling reference)
auto lambda7(int value)
{ // using copy instead of reference
  return [/*&*/ value](int x) { return x + value; };
}

auto lambda8()
{
  auto overload_set = overloaded{[](int x) { return x + 42; },
                                 [](int x, int y) { return x + y; }};

  return overload_set(12);
}

std::vector<int> get_data();
auto lambda9()
{
  auto l = [i = 0](int value) mutable {
    std::cout << value << ": " << i++ << '\n';
  };

  std::ranges::for_each(get_data(), l);
  std::ranges::for_each(get_data(), std::ref(l));
  std::ranges::for_each(get_data(), l);
}

auto lambda10()
{
  std::function f = [i = 12](int j, bool b) mutable {
    if (b)
    {
      return i++;
    }
    else
    {
      return j;
    }
  };

  auto f2 = f;
}

// ---------------------------------------------------------------------------- //

auto equivalent()
{
  auto l = Lambda();
  long (*fp)(int, int &) = l;

  auto l1 = Lambda1{};
  auto result = l1(1.0, 2.1, 3.2, 4.3, 5.4);

  auto l2 = Lambda2{};
  auto result2 = l2(std::make_index_sequence<10>());

  auto l3 = Lambda3{};
  auto result3 = l3(std::make_tuple(1, 2ll, 3l, 4.5));

  {
    int i = 42;
    int j = 24;
    auto l4_ = Lambda4{i, j};
    l4_();
    auto l4 = l4_;
    l4_();
    l4_();
    return l2;
  }

  auto l5 = Lambda5{1, true, 2, false};

  auto l7 = Lambda7{5};

  auto l10 = Lambda10{34, true};
}