#include "parse_input.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    const double lbs_to_kg = 2.20462;

    const double foot_to_meter = 3.28084;

    const auto density_in_kg_per_cubic_m = parse_input(argc, argv);
    const auto density_lbs_un_cubis_ft =
        density_in_kg_per_cubic_m * lbs_to_kg /
        (foot_to_meter * foot_to_meter * foot_to_meter);

    std::cout << density_in_kg_per_cubic_m << " kg/m^3 is "
              << density_lbs_un_cubis_ft << " lbs/ft^3\n";
    return 0;
}
