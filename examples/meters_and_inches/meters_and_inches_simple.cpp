#include <iostream>

int main()
{
    using value_type = double;
    const value_type meter_to_inch = 0.0254;

    const value_type distance_in_meters = 123.0;
    const value_type distance_in_inches = distance_in_meters / meter_to_inch;
    std::cout << distance_in_meters << " meters is " << distance_in_inches
              << " inches\n";
    return 0;
}
