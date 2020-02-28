#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

#include <biztonsag/orderable.hpp>

namespace
{
    // We want to use templates here so that we can stamp out tags as needed,
    // included for future types.  This is one of the cases where the helper
    // macros wouldn't be as useful.
    template <typename T>
    struct SafeTag
    {
    };

    template <typename T>
    struct UnsafeTag
    {
    };

    // Now, type aliases with the appropriate tags.  Because SafeTag and
    // UnsafeTag are different types, implicit conversions between Safe<T> and
    // Unsafe<T> are compilation errors.
    template <typename T>
    using Safe = btshn::Orderable<T, SafeTag<T>>;

    template <typename T>
    using Unsafe = btshn::Orderable<T, UnsafeTag<T>>;

    // If we needed to operate with different "safe" environments (e.g.,
    // multiple databases, UI frameworks) we could make tag and type aliases for
    // each of those.  This keeps the idea UI<T>, MySQL<T>, and Postgres<T> as
    // separate types, since they likely need to be encoded differently.

    // We're only going to print things that are Safe.  Even though there's no
    // danger (in this example anyway) of printing Unsafe<int>, we want a
    // consistent interface to avoid developers having to remember which types
    // are safe to use direclty and which ones aren't.
    template <typename T>
    void print(Safe<T> const & s)
    {
        std::cout << (*s) << '\n';
    }

    // We'll stick with templates and declare a generic encode function to
    // convert Unsafe<T> values to Safe<T> ones.  We can specialize as needed.
    template <typename T>
    auto encode(Unsafe<T> const & us) -> Safe<T>;

    // While not in this example, it'd be reasonable to have specializations for
    // encode to operate on primatives and return the same value.  This way we
    // hae have the policy that everything needs to be encoded before it's
    // passed to the UI/database/whatever, even if the encoding is a no-op.

    template <>
    auto encode<std::string>(Unsafe<std::string> const & us)
        -> Safe<std::string>
    {
        // For the sake of simplicitly, we're going to assume that a
        // Safe<std::string> is one without any lowercase letters.
        auto raw = *us;
        static_assert(std::is_same_v<std::string, decltype(raw)>);

        std::transform(std::begin(raw), std::end(raw), std::begin(raw),
                       [](auto v) { return std::toupper(v); });
        return Safe<std::string>{std::move(raw)};
    }
} // namespace

int main(int argc, char ** argv) // NOLINT(modernize-use-trailing-return-type)
{
    for(auto i = 1; i < argc; ++i)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        Unsafe<std::string> us{argv[i]};
        auto ss = encode(us);
        // auto ss2 = encode(ss);
        // print(us);
        print(ss);
    }
    return 0;
}
