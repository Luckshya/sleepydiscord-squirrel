#pragma once

#if defined(_MSC_VER)
	#define EXPORT	extern "C" __declspec(dllexport)
#elif defined(__GNUC__)
	#define EXPORT	extern "C"
#endif

// ------------------------------------------------------------------------------------------------
#include <vcmp.h>
#include <squirrel.h>

// ------------------------------------------------------------------------------------------------
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

// A definition needed for Squirrel's print function
#ifdef SQUNICODE
	#define scvprintf vwprintf
#else
	#define scvprintf vprintf
#endif

// ------------------------------------------------------------------------------------------------
namespace SqDiscord
{
// ------------------------------------------------------------------------------------------------
void OutputDebug(const char * msg);

// ------------------------------------------------------------------------------------------------
void OutputMsg(const char * msg);

// ------------------------------------------------------------------------------------------------
void OutputErr(const char * msg);

// ------------------------------------------------------------------------------------------------
void OutputWarn(const char * msg);

// ------------------------------------------------------------------------------------------------
} // Namespace - SqDiscord
