// lambda version

void lambda()
{
    auto l = []([[maybe_unused]] int value, int &value2) noexcept -> long {
        return ++value + value2++;
    };
    long (*fp)(int, int &) = l;
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

void equivalent()
{
    auto l = Lambda();
    long (*fp)(int, int &) = l;
}