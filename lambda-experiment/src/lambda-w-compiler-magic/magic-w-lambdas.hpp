#ifndef MAGIC_W_LAMBDAS_HPP
#define MAGIC_W_LAMBDAS_HPP

#include <concepts>
#include <tuple>
#include <utility>

class Lambda
{
  template <typename T>
  using pointer_type = long (*)(T, int &) noexcept;

  template <typename T>
  constexpr static auto func([[maybe_unused]] T value, int &value2) noexcept
    -> long
  {
    return ++value + value2++;
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

#endif // MAGIC_W_LAMBDAS_HPP