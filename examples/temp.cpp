#include <cstdlib>
#include <iostream>
#include <type_traits>

#include <biztonsag/comparable.hpp>

namespace
{
    BTSHN_MAKE_COMPARABLE(double, Fahrenheit);
    BTSHN_MAKE_COMPARABLE(double, Celsius);
    BTSHN_MAKE_COMPARABLE(double, Kelvin);

    constexpr auto absolute_zero = -273.15;
    constexpr auto celsius_fahrenheit_const = 32;
    constexpr auto celsius_fahrenheit_ratio = 1.8;

    namespace detail
    {
        template <typename TO, typename FROM>
        auto convert(FROM temp) noexcept -> TO;

        template <>
        auto convert<Kelvin, Celsius>(Celsius temp) noexcept -> Kelvin
        {
            return Kelvin{(*temp) - absolute_zero};
        }

        template <>
        auto convert<Celsius, Kelvin>(Kelvin temp) noexcept -> Celsius
        {
            return Celsius{(*temp) + absolute_zero};
        }

        template <>
        auto convert<Celsius, Fahrenheit>(Fahrenheit temp) noexcept -> Celsius
        {
            return Celsius{((*temp) - celsius_fahrenheit_const) /
                           celsius_fahrenheit_ratio};
        }

        template <>
        auto convert<Fahrenheit, Celsius>(Celsius temp) noexcept -> Fahrenheit
        {
            return Fahrenheit{(*temp) * celsius_fahrenheit_ratio +
                              celsius_fahrenheit_const};
        }

        template <>
        auto convert<Fahrenheit, Kelvin>(Kelvin temp) noexcept -> Fahrenheit
        {
            return convert<Fahrenheit>(convert<Celsius>(temp));
        }

        template <>
        auto convert<Kelvin, Fahrenheit>(Fahrenheit temp) noexcept -> Kelvin
        {
            return convert<Kelvin>(convert<Celsius>(temp));
        }
    } // namespace detail

    template <typename TO, typename FROM>
    auto convert(FROM temp) noexcept -> TO
    {
        if constexpr(std::is_same<TO, FROM>::value)
        {
            return temp;
        }
        else
        {
            return detail::convert<TO>(temp);
        }
    }

    template <typename TEMP>
    void print(char const * num)
    {
        TEMP const input{std::atof(num)};

        std::cout << *(convert<Kelvin>(input)) << "K\t"
                  << *(convert<Celsius>(input)) << "C\t"
                  << *(convert<Fahrenheit>(input)) << "F\n";
    }
} // namespace

int main(int argc, char ** argv) // NOLINT(modernize-use-trailing-return-type)
{
    for(auto i = 1; i < argc; ++i)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        auto num = argv[i] + 1;
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        switch(argv[i][0])
        {
        case 'c':
        case 'C':
            print<Celsius>(num);
            break;

        case 'f':
        case 'F':
            print<Fahrenheit>(num);
            break;

        case 'k':
        case 'K':
            print<Kelvin>(num);
            break;
        }
    }

    return 0;
}
