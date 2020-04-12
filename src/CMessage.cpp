#include "CMessage.h"

#include <utility>

// ------------------------------------------------------------------------------------------------
namespace SqDiscord
{
// ------------------------------------------------------------------------------------------------
CMessage::CMessage(std::string channelID, std::string author, std::string authorNick, std::string authorID, std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>>& roles, std::string message) {
	this->channelID		= std::move(channelID);
	this->author		= std::move(author);
	this->authorNick	= std::move(authorNick);
	this->authorID		= std::move(authorID);
	this->message		= std::move(message);
	this->roles			= roles;
}
} // Namespace - SqDiscord