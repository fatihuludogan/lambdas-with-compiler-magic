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

// ---------------------------------------------------------------------------- //

void equivalent()
{
  auto l = Lambda();
  long (*fp)(int, int &) = l;

  auto l1 = Lambda1{};
  auto result = l1(1.0, 2.1, 3.2, 4.3, 5.4);

  auto l2 = Lambda2{};
  auto result2 = l2(std::make_index_sequence<10>());

  auto l3 = Lambda3{};
  auto result3 = l3(std::make_tuple(1, 2ll, 3l, 4.5));
}