/** @file
 * @brief this example shows how to find the side length of a cube with a volume
 * of one imperial pint
 */

#include "../../CtUnits/CtUnits.hpp"
#include <iostream>
#include <ratio>

struct Pint
{
};
struct Milliliter
{
};
struct Decimeter
{
};
struct Inch
{
};

template <typename... UnitsDimensions>
using Quantity = ctu::Quantity<long double, ctu::UdMap<UnitsDimensions...>>;

using VolumePt = Quantity<ctu::UnitDimension<Pint, 1>>;
using LengthInches = Quantity<ctu::UnitDimension<Inch, 1>>;

int main()
{
    const auto ml_to_pint = Quantity<
        ctu::UnitDimension<Milliliter, 1>, ctu::UnitDimension<Pint, -1>>(
        568.26125L);
    const auto cubic_dm_to_ml = Quantity<
        ctu::UnitDimension<Decimeter, 3>, ctu::UnitDimension<Milliliter, -1>>(
        0.001L);
    const auto dm_to_inch = Quantity<
        ctu::UnitDimension<Decimeter, 1>, ctu::UnitDimension<Inch, -1>>(0.254L);
    const LengthInches side_length =
        (VolumePt(1.0L) * ml_to_pint * cubic_dm_to_ml).pow<std::ratio<1, 3>>() /
        dm_to_inch;
    std::cout << "A cube with side length of " << side_length.get_value()
              << " inches has a volume of one pint.\n";
    return 0;
}
