#ifndef MAGIC_W_LAMBDAS_HPP
#define MAGIC_W_LAMBDAS_HPP

#include <algorithm>
#include <concepts>
#include <functional>
#include <iostream>
#include <ranges>
#include <tuple>
#include <utility>
#include <vector>

class Lambda
{
  template <typename T>
  using pointer_type = long (*)(T, int &) noexcept;

  template <typename T>
  constexpr static auto func([[maybe_unused]] T value, int &value2) noexcept
    -> long
  {
    return static_cast<long>(++value + value2++);
  }

  constexpr static auto func_int(int value, int &value2) noexcept -> long
  {
    return ++value + value2++;
  }

public:
  template <typename T>
  constexpr auto operator()([[maybe_unused]] T value,
                            int &value2) const noexcept -> long
  {
    return ++value + value2++;
  }

  template <typename T>
  constexpr operator pointer_type<T>() const
  {
    return func;
  }

  constexpr operator pointer_type<int>() const
  {
    return func_int;
  }
};

class Lambda1
{
public:
  template <std::floating_point... T>
  [[nodiscard]] constexpr auto operator()(T... value) const noexcept -> long
  {
    return (value + ...);
  }
};

class Lambda2
{
public:
  template <std::size_t... Idx>
  constexpr auto operator()(std::index_sequence<Idx...>) const noexcept -> long
  {
    return (Idx + ...);
  }
};

class Lambda3
{
  struct Lambda_
  {
    template <std::size_t... Idx, typename Tuple>
    constexpr auto operator()(std::index_sequence<Idx...>, const Tuple &tuple)
    {
      return (std::get<Idx>(tuple) + ...);
    }
  };

public:
  template <typename... T>
  constexpr auto operator()(const std::tuple<T...> &input) const noexcept
  {
    return Lambda_{}(std::make_index_sequence<sizeof...(T)>(), input);
  }
};

struct Lambda4
{
  constexpr auto operator()()
  {
    ++j;
    return ++i;
  }
  int i;
  int &j;
};

struct Lambda5
{
  constexpr auto operator()()
  {
  }
  int a;
  bool b;
  int c;
  bool d;
};

class Lambda7
{
public:
  Lambda7(int value) : value(value)
  {
  }

  constexpr auto operator()(int x) const
  {
    return x + value;
  }

private:
  int value;
};

template <typename... Ts>
struct overloaded : Ts...
{
  using Ts::operator()...;
};

template <typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

class Lambda8
{
public:
  constexpr auto operator()(int x) const
  {
    return x + 42;
  }
  constexpr auto operator()(int x, int y) const noexcept
  {
    return x + y;
  }
};

std::vector<int, std::allocator<int>> get_data();
class Lambda9
{
public:
  constexpr auto operator()(int value)
  {
    std::operator<<(
      std::operator<<(std::cout.operator<<(value), ":").operator<<(i++),
      '\n');
  }


private:
  int i;
};

class Lambda10
{
public:
  Lambda10(int j, bool b) : i(12)
  {
  }

  constexpr auto operator()(int j, bool b)
  {
    if (b)
    {
      return i++;
    }
    else
    {
      return j;
    }
  }

private:
  int i, j;
  bool b;
};

#endif // MAGIC_W_LAMBDAS_HPP
