#include <cstdlib>
#include <iostream>
#include <random>
#include <type_traits>

#include <biztonsag/comparable.hpp>
#include <biztonsag/orderable.hpp>

namespace
{
    BTSHN_MAKE_COMPARABLE(Fahrenheit, double);
    BTSHN_MAKE_COMPARABLE(Celsius, double);

    BTSHN_MAKE_ORDERABLE(Kelvin, double);

    constexpr auto absolute_zero = -273.15;
    constexpr auto celsius_fahrenheit_const = 32;
    constexpr auto celsius_fahrenheit_ratio = 1.8;

    // All the conversions between the temperatures are here.  These are
    // straight algebra, but we need to be a bit verbose due to the explicit
    // constructors used by biztonsag.
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
        // NOLINTNEXTLINE(clang-diagnostic-unused-function)
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
        // clang-tidy picks this up as a false positive, so mask the warning
        if constexpr(
            std::is_same<TO, FROM>::
                value) // NOLINTNEXTLINE(hicpp-braces-around-statements)
        {
            return temp;
        }
        else
        {
            return detail::convert<TO, FROM>(temp);
        }
    }

    // This is some type that represents a temperature sensor.  We'll assume for
    // the sake of simplicity that all the sensors we have give their
    // temperature in Celsius.
    struct Sensor
    {
        Celsius m_current;
    };

    // Our thermostats are designed for America, so they deal with temperature
    // in terms of Fahrenheit.
    struct Thermostat
    {
        Fahrenheit m_desired;
    };

    void control(Sensor const & s, Thermostat const & t)
    {
        // The idea here is to simulate some kind of controller for the
        // heating/AC.  To add an extra example of type-safety, we'll assume the
        // controller operates in Kelvin.
        auto const sensor_temp = convert<Kelvin>(s.m_current);
        auto const desired_temp = convert<Kelvin>(t.m_desired);

        // Now that we have the proper types, we figure out whether to run the
        // heater or the air conditioning.  Note that becuase Fahrenheit and
        // Celsius are Comparable, the next line won't compile; Kelvin instances
        // work fine since Kelvin is an Orderable.
        std::cout << "Current = " << *sensor_temp
                  << "\nDesired = " << *desired_temp << '\n';

        auto const sensor_f = convert<Fahrenheit>(sensor_temp);
        auto const desired_f = convert<Fahrenheit>(desired_temp);
        if(sensor_temp < desired_temp)
        {
            std::cout << "Room is cold; heating " << *desired_f - *sensor_f
                      << "F\n";
        }
        else
        {
            std::cout << "Room is warm; cooling " << *sensor_f - *desired_f
                      << "F\n";
        }

        // We could expand this to be multithreaded or or whwatever and keep
        // changing the sensor by some random value until it's close enough to
        // the desired temperature that we halt everything; this is left as an
        // exercise for somebody else.
    }
} // namespace

int main(int argc, char ** argv) // NOLINT(modernize-use-trailing-return-type)
{
    Fahrenheit const desired{[argc, argv]() {
        constexpr auto default_temperature = 68.0;
        if(argc > 1)
        {
            return std::strtod(
                argv[1], // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                nullptr);
        }
        return default_temperature;
    }()};

    std::default_random_engine re{std::random_device{}()};
    std::normal_distribution<double> dist{
        *desired, 5.0}; // NOLINT(cppcoreguidelines-avoid-magic-numbers,
                        //        readability-magic-numbers)

    Sensor s{convert<Celsius>(Fahrenheit{dist(re)})};
    Thermostat t{desired};

    control(s, t);

    return 0;
}
