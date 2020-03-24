#pragma once

// ------------------------------------------------------------------------------------------------
#include <mutex>
#include <vector>

// ------------------------------------------------------------------------------------------------
#include "sleepy_discord/websocketpp_websocket.h"

// ------------------------------------------------------------------------------------------------
namespace SqDiscord
{
class CMessage
{
public :
	std::string author;
	std::string channelID;
	std::string authorNick;
	std::string authorID;
	std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>> roles;
	std::string message;

	CMessage(std::string, std::string, std::string, std::string, std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>>&, std::string);
};
} // Namespace - SqDiscord