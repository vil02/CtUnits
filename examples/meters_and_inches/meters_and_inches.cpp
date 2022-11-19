#include "../../CtUnits/CtUnits.hpp"
#include <iostream>
#include <type_traits>

int main()
{
    struct Meter
    {
    };
    struct Inch
    {
    };

    using value_type = double;
    using DistanceInMeters =
        ctu::Quantity<value_type, ctu::UdList<ctu::UnitDimension<Meter, 1>>>;

    using DistanceInInches =
        ctu::Quantity<value_type, ctu::UdList<ctu::UnitDimension<Inch, 1>>>;

    const auto meter_to_inch = ctu::Quantity<
        value_type,
        ctu::UdList<
            ctu::UnitDimension<Inch, -1>, ctu::UnitDimension<Meter, 1>>>(
        0.0254);

    const auto distance_in_meters = DistanceInMeters(123.0);
    const DistanceInInches distance_in_inches =
        distance_in_meters / meter_to_inch;
    // note that
    static_assert(
        !std::is_same_v<
            DistanceInInches, decltype(distance_in_meters * meter_to_inch)>);
    // therefore
    // const DistanceInInches distance_in_inches =
    // distance_in_meters*meter_to_inch; would lead to a compile-time error
    std::cout << distance_in_meters.get_value() << " meters is "
              << distance_in_inches.get_value() << " inches\n";
    return 0;
}
