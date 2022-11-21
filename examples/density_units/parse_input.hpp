#ifndef PARSE_INPUT_HPP_INCLUDED
#define PARSE_INPUT_HPP_INCLUDED

#include <stdexcept>
#include <string>

double parse_input(int argc, char **argv)
{
    if (argc != 2)
    {
        throw std::invalid_argument("Wrong number of arguments.");
    }
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    return std::stod(std::string(argv[1]));
}

#endif // PARSE_INPUT_HPP_INCLUDED
