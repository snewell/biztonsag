#include <cstdlib>
#include <iostream>

#include <biztonsag/comparable.hpp>

namespace
{
    struct FahrenheitTag
    {
    };
    struct CelsiusTag
    {
    };

    using Fahrenheit = btshn::Comparable<double, FahrenheitTag>;
    using Celsius = btshn::Comparable<double, CelsiusTag>;

    Fahrenheit convert(Celsius temp) noexcept
    {
        return Fahrenheit{static_cast<double const &>(temp) * 1.8 + 32};
    }

    Celsius convert(Fahrenheit temp) noexcept
    {
        return Celsius{(static_cast<double const &>(temp) - 32) / 1.8};
    }

    template <typename TEMP>
    void print(char first, char second, char const * num)
    {
        std::cout << num << first << " = "
                  << static_cast<double const &>(convert(TEMP{std::atof(num)}))
                  << second << '\n';
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
            print<Celsius>('C', 'F', num);
            break;

        case 'f':
        case 'F':
            print<Fahrenheit>('F', 'C', num);
            break;
        }
    }

    return 0;
}
