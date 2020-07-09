// ------------------------------------------------------------------------------------------------
#include "Common.hpp"
// ------------------------------------------------------------------------------------------------
#if defined(WIN32) || defined(_WIN32)
#define SQ_OS_WINDOWS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#endif

// ------------------------------------------------------------------------------------------------
#include <cstdarg>

// ------------------------------------------------------------------------------------------------
namespace SqDiscord {
/* ------------------------------------------------------------------------------------------------
 * Common buffers to reduce memory allocations. To be immediately copied upon return!
*/
static SQChar g_Buffer[4096];

// ------------------------------------------------------------------------------------------------
void SqThrowF(const SQChar *str, ...) {
	// Initialize the argument list
	va_list args;
			va_start (args, str);
	// Write the requested contents
	if (std::vsnprintf(g_Buffer, sizeof(g_Buffer), str, args) < 0) {
		// Write a generic message at least
		strcpy(g_Buffer, "Unknown error has occurred");
	}
	// Finalize the argument list
			va_end(args);
	// Throw the exception with the resulted message
	throw Sqrat::Exception(g_Buffer); // NOLINT(hicpp-exception-baseclass,cert-err60-cpp)
}

/* ------------------------------------------------------------------------------------------------
 * Raw console message output.
*/
static inline void OutputMessageImpl(const SQChar *msg, va_list args) {
#ifdef SQ_OS_WINDOWS
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csb_before;
	GetConsoleScreenBufferInfo(hstdout, &csb_before);
	SetConsoleTextAttribute(hstdout, FOREGROUND_GREEN);
	std::printf("[SQMOD] ");

	SetConsoleTextAttribute(hstdout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED |
									 FOREGROUND_INTENSITY); // NOLINT(hicpp-signed-bitwise)
	std::vprintf(msg, args);
	std::puts("");

	SetConsoleTextAttribute(hstdout, csb_before.wAttributes);
#else
	std::printf("\033[21;32m[SQMOD]\033[0m");
	std::vprintf(msg, args);
	std::puts("");
#endif // SQ_OS_WINDOWS
}

/* ------------------------------------------------------------------------------------------------
 * Raw console error output.
*/
static inline void OutputErrorImpl(const SQChar *msg, va_list args) {
#ifdef SQ_OS_WINDOWS
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csb_before;
	GetConsoleScreenBufferInfo(hstdout, &csb_before);
	SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_INTENSITY); // NOLINT(hicpp-signed-bitwise)
	std::printf("[MODULE] ");

	SetConsoleTextAttribute(hstdout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED |
									 FOREGROUND_INTENSITY); // NOLINT(hicpp-signed-bitwise)
	std::vprintf(msg, args);
	std::puts("");

	SetConsoleTextAttribute(hstdout, csb_before.wAttributes);
#else
	std::printf("\033[21;91m[MODULE]\033[0m");
	std::vprintf(msg, args);
	std::puts("");
#endif // SQ_OS_WINDOWS
}

// ------------------------------------------------------------------------------------------------
void OutputDebug(const SQChar *msg, ...) {
#ifdef _DEBUG
	// Initialize the arguments list
	va_list args;
	va_start(args, msg);
	// Call the output function
	OutputMessageImpl(msg, args);
	// Finalize the arguments list
	va_end(args);
#else

#endif
}

// ------------------------------------------------------------------------------------------------
void OutputMessage(const SQChar *msg, ...) {
	// Initialize the arguments list
	va_list args;
			va_start(args, msg);
	// Call the output function
	OutputMessageImpl(msg, args);
	// Finalize the arguments list
			va_end(args);
}

// ------------------------------------------------------------------------------------------------
void OutputError(const SQChar *msg, ...) {
	// Initialize the arguments list
	va_list args;
			va_start(args, msg);
	// Call the output function
	OutputErrorImpl(msg, args);
	// Finalize the arguments list
			va_end(args);
}
} // Namespace:: SqDiscord
