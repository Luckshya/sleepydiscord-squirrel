#pragma once

#if defined(_MSC_VER)
#define EXPORT    extern "C" __declspec(dllexport)
#elif defined(__GNUC__)
#define EXPORT	extern "C"
#endif

// ------------------------------------------------------------------------------------------------
#include <vcmp.h>
#include <squirrel.h>

// ------------------------------------------------------------------------------------------------
#include <cstdio>
#include <cstdlib>

// A definition needed for Squirrel's print function
#ifdef SQUNICODE
#define scvprintf vwprintf
#else
#define scvprintf vprintf
#endif