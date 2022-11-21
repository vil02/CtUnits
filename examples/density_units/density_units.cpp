#include "../../CtUnits/CtUnits.hpp"
#include "parse_input.hpp"
#include <iostream>

template <typename... Uds> using Quantity = ctu::Quantity<double, Uds...>;

int main(int argc, char *argv[])
{
    struct Meter
    {
    };
    struct Kilogram
    {
    };

    struct Pound
    {
    };

    struct Foot
    {
    };

    using DensityInKgPerCubicMeter = Quantity<ctu::UdMap<
        ctu::UnitDimension<Kilogram, 1>, ctu::UnitDimension<Meter, -3>>>;

    using DensityInLbsPerCubicFoot = Quantity<
        ctu::UdMap<ctu::UnitDimension<Foot, -3>, ctu::UnitDimension<Pound, 1>>>;

    const auto lbs_to_kg = Quantity<ctu::UdMap<
        ctu::UnitDimension<Kilogram, -1>, ctu::UnitDimension<Pound, 1>>>(
        2.20462);

    const auto foot_to_meter = Quantity<
        ctu::UdMap<ctu::UnitDimension<Foot, 1>, ctu::UnitDimension<Meter, -1>>>(
        3.28084);

    const auto density_in_kg_per_cubic_m =
        DensityInKgPerCubicMeter(parse_input(argc, argv));
    const DensityInLbsPerCubicFoot density_lbs_un_cubis_ft =
        density_in_kg_per_cubic_m * lbs_to_kg /
        (foot_to_meter * foot_to_meter * foot_to_meter);

    std::cout << density_in_kg_per_cubic_m.get_value() << " kg/m^3 is "
              << density_lbs_un_cubis_ft.get_value() << " lbs/ft^3\n";
    return 0;
}
