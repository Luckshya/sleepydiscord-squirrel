#pragma once

// ------------------------------------------------------------------------------------------------
#include "CSession.h"
#include "sqrat.h"
#include "sleepy_discord/websocketpp_websocket.h"

// ------------------------------------------------------------------------------------------------
#include <vector>

// ------------------------------------------------------------------------------------------------
namespace SqDiscord
{
void Event_onReady(CSession * session);
void Event_onMessage(CSession * session, CCStr channelID, CCStr author, CCStr authorNick, CCStr authorID, const std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>>& roles, CCStr message);
} // Namespace - SqDiscord