#include <concepts>
// lambda version

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

// equivalent code from compiler

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

void equivalent()
{
    auto l = Lambda();
    long (*fp)(int, int &) = l;

    auto l1 = Lambda1{};
    auto result = l1(1.0, 2.1, 3.2, 4.3, 5.4);
}