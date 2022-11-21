#include "../../CtUnits/CtUnits.hpp"
#include <iostream>
#include <type_traits>

int main()
{
    struct Meter
    {
    };
    struct Kilometer
    {
    };
    struct Second
    {
    };
    struct Minute
    {
    };
    struct Hour
    {
    };

    using value_type = double;
    using SpeedInKph = ctu::Quantity<
        value_type,
        ctu::UdMap<
            ctu::UnitDimension<Hour, -1>, ctu::UnitDimension<Kilometer, 1>>>;

    using SpeedInMps = ctu::Quantity<
        value_type,
        ctu::UdMap<
            ctu::UnitDimension<Meter, 1>, ctu::UnitDimension<Second, -1>>>;

    const auto second_to_minute = ctu::Quantity<
        value_type,
        ctu::UdMap<
            ctu::UnitDimension<Minute, -1>, ctu::UnitDimension<Second, 1>>>(
        60.0);

    const auto minute_to_hour = ctu::Quantity<
        value_type,
        ctu::UdMap<
            ctu::UnitDimension<Hour, -1>, ctu::UnitDimension<Minute, 1>>>(60.0);

    const auto meter_to_kilometer = ctu::Quantity<
        value_type,
        ctu::UdMap<
            ctu::UnitDimension<Kilometer, -1>, ctu::UnitDimension<Meter, 1>>>(
        1000.0);

    const auto speed_in_kph = SpeedInKph(140.0);
    const SpeedInMps speed_in_mps =
        speed_in_kph * meter_to_kilometer / (second_to_minute * minute_to_hour);

    std::cout << speed_in_kph.get_value() << " km/h is "
              << speed_in_mps.get_value() << " m/s\n";
    return 0;
}
