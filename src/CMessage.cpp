#include "CMessage.h"

// ------------------------------------------------------------------------------------------------
namespace SqDiscord
{
// ------------------------------------------------------------------------------------------------
CMessage::CMessage(std::string channelID, std::string author, std::string authorNick, std::string authorID, std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>>& roles, std::string message) {
	this->channelID		= channelID;
	this->author		= author;
	this->authorNick	= authorNick;
	this->authorID		= authorID;
	this->message		= message;
	this->roles			= roles;
}
} // Namespace - SqDiscord