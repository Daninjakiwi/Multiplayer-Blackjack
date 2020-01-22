#pragma once
#include <iostream>
#define LOG(x) std::cout << x << std::endl;
#define CORE_LOG(x) std::cout << x << std::endl;
#define COORD(x,y) std::cout << x << ", " << y << std::endl
constexpr auto INVALID_ARGUMENT_ERROR = "invalid arg";
constexpr auto HEAP_ALLOCATION_ERROR = "heap allocation error";