#include <cstdlib>
#include <iostream>
#include <type_traits>

#include <biztonsag/comparable.hpp>

namespace
{
    struct FahrenheitTag
    {
    };

    struct CelsiusTag
    {
    };

    struct KelvinTag
    {
    };

    using Fahrenheit = btshn::Comparable<double, FahrenheitTag>;
    using Celsius = btshn::Comparable<double, CelsiusTag>;
    using Kelvin = btshn::Comparable<double, KelvinTag>;

    namespace detail
    {
        template <typename TO, typename FROM>
        TO convert(FROM temp) noexcept;

        template <>
        Kelvin convert<Kelvin, Celsius>(Celsius temp) noexcept
        {
            return Kelvin{(*temp) + 273.15};
        }

        template <>
        Celsius convert<Celsius, Kelvin>(Kelvin temp) noexcept
        {
            return Celsius{(*temp) - 273.15};
        }

        template <>
        Celsius convert<Celsius, Fahrenheit>(Fahrenheit temp) noexcept
        {
            return Celsius{((*temp) - 32) / 1.8};
        }

        template <>
        Fahrenheit convert<Fahrenheit, Celsius>(Celsius temp) noexcept
        {
            return Fahrenheit{(*temp) * 1.8 + 32};
        }

        template <>
        Fahrenheit convert<Fahrenheit, Kelvin>(Kelvin temp) noexcept
        {
            return convert<Fahrenheit>(convert<Celsius>(temp));
        }

        template <>
        Kelvin convert<Kelvin, Fahrenheit>(Fahrenheit temp) noexcept
        {
            return convert<Kelvin>(convert<Celsius>(temp));
        }
    } // namespace detail

    template <typename TO, typename FROM>
    TO convert(FROM temp) noexcept
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

int main(int argc, char ** argv)
{
    for(auto i = 1; i < argc; ++i)
    {
        auto num = argv[i] + 1;
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
