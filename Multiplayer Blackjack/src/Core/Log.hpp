#pragma once
#include <iostream>
#include <ctime>
#include <string>
#ifdef _DEBUG
#include <Windows.h>
#endif

constexpr auto INVALID_ARGUMENT_ERROR = "invalid argument.";
constexpr auto HEAP_ALLOCATION_ERROR = "heap allocation error.";

inline std::string currentTime() {
	std::time_t result = time(NULL);
	char str[26];
	ctime_s(str, sizeof(str), &result);

	return "[" + std::string(str).substr(11, 8) + "]";
}

#define CORETRACE(x) CORELOG("[TRACE] " << x, 8)
#define COREINFO(x)  CORELOG("[INFO] " << x, 3)
#define COREWARN(x)  CORELOG("[WARNING] " << x, 6)
#define COREERROR(x) CORELOG("[ERROR] " << x, 12)
#define COREFATAL(x) CORELOG("[FATAL] " << x, 64)

#ifdef _DEBUG
#define CORELOG(message, colour) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);std::cout << currentTime() << message << std::endl
#else
#define CORELOG(message, colour)
#endif