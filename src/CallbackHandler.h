#pragma once

// ------------------------------------------------------------------------------------------------
#include "CSession.h"
#include "sqrat.h"
#include "sleepy_discord/websocketpp_websocket.h"

// ------------------------------------------------------------------------------------------------
#include <vector>

// ------------------------------------------------------------------------------------------------
typedef const std::string &CString;
typedef const std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>> &s_Roles;

// ------------------------------------------------------------------------------------------------
namespace SqDiscord {
// ------------------------------------------------------------------------------------------------
void Event_onReady(CSession *session);

// ------------------------------------------------------------------------------------------------
void Event_onMessage(CSession *session, CString channelID, CString author, CString authorNick, CString authorID,
					 s_Roles roles, CString message);

// ------------------------------------------------------------------------------------------------
void Event_onError(CSession *session, int errorCode, CString errorMessage);

// ------------------------------------------------------------------------------------------------
void Event_onDisconnect(CSession *session);

// ------------------------------------------------------------------------------------------------
void Event_onQuit(CSession *session);
} // Namespace - SqDiscord