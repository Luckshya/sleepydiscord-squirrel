#pragma once

// ------------------------------------------------------------------------------------------------
#include "sqrat.h"

// ------------------------------------------------------------------------------------------------
#define SqVM DefaultVM::Get

// ------------------------------------------------------------------------------------------------
using namespace Sqrat;

// ------------------------------------------------------------------------------------------------
class CDiscord;

namespace DiscordEvent {
template<class T>
struct EventType;

class EventHandler;
}

// ------------------------------------------------------------------------------------------------
namespace SqDiscord {
// ------------------------------------------------------------------------------------------------
typedef const char *CCStr;
typedef const SQChar *CSStr;

// ------------------------------------------------------------------------------------------------
class CSession;

/* ------------------------------------------------------------------------------------------------
 * SOFTWARE INFORMATION
*/
#define SQDISCORD_NAME "Squirrel Discord Module"
#define SQDISCORD_AUTHOR "Luckshya"
#define SQDISCORD_COPYRIGHT "Copyright (c) 2020 Luckshya"
#define SQDISCORD_HOST_NAME "SqModDiscordHost"
#define SQDISCORD_VERSION 001
#define SQDISCORD_VERSION_STR "0.0.1"
#define SQDISCORD_VERSION_MAJOR 0
#define SQDISCORD_VERSION_MINOR 0
#define SQDISCORD_VERSION_PATCH 1

/* ------------------------------------------------------------------------------------------------
 * Output a message only if the _DEBUG was defined.
*/
void OutputDebug(const SQChar *msg, ...);

/* ------------------------------------------------------------------------------------------------
 * Output a formatted user message to the console.
*/
void OutputMessage(const SQChar *msg, ...);

/* ------------------------------------------------------------------------------------------------
 * Output a formatted error message to the console.
*/
void OutputError(const SQChar *msg, ...);
} //Namespace:: SqDiscord
