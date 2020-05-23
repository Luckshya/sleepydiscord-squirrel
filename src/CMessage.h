#pragma once

// ------------------------------------------------------------------------------------------------
#include <mutex>
#include <vector>

// ------------------------------------------------------------------------------------------------
#include "sleepy_discord/websocketpp_websocket.h"

// ------------------------------------------------------------------------------------------------
namespace SqDiscord {
class CMessage {
public :
	std::string author;
	std::string channelID;
	std::string authorNick;
	std::string authorID;
	std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>> roles;
	std::string message;

	CMessage(std::string channelID, std::string author, std::string authorNick, std::string authorID,
			 std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>> &roles, std::string message) {
		this->channelID = std::move(channelID);
		this->author = std::move(author);
		this->authorNick = std::move(authorNick);
		this->authorID = std::move(authorID);
		this->message = std::move(message);
		this->roles = roles;
	}
};
} // Namespace - SqDiscord