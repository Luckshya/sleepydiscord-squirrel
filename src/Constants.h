#pragma once

// ------------------------------------------------------------------------------------------------
#include "Common.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqDiscord {
// ------------------------------------------------------------------------------------------------
enum SessEvents {
	ON_READY = 0,
	ON_MESSAGE,
	ON_ERROR,
	ON_DISCONNECT,
	ON_QUIT,
	ON_SERVER,
	ON_SERVER_EDIT,
	ON_SERVER_DELETE,
	ON_MEMBER,
	ON_MEMBER_EDIT,
	ON_MEMBER_REMOVE,
	ON_CHANNEL,
	ON_CHANNEL_EDIT,
	ON_CHANNEL_DELETE,
	ON_ROLE,
	ON_ROLE_EDIT,
	ON_ROLE_DELETE,
	ON_USER_EDIT
};

// ------------------------------------------------------------------------------------------------
enum ChannelType {
	CHANNEL_TYPE_NONE = -1,
	SERVER_TEXT = 0,
	DM = 1,
	SERVER_VOICE = 2,
	GROUP_DM = 3,
	SERVER_CATEGORY = 4,
	GUILD_NEWS = 5,
	GUILD_STORE = 6
};

// ------------------------------------------------------------------------------------------------
enum MessageType {
	DEFAULT = 0,
	RECIPIENT_ADD = 1,
	RECIPIENT_REMOVE = 2,
	CALL = 3,
	CHANNEL_NAME_CHANGE = 4,
	CHANNEL_ICON_CHANGE = 5,
	CHANNEL_PINNED_MESSAGE = 6,
	GUILD_MEMBER_JOIN = 7
};

// ------------------------------------------------------------------------------------------------
void DRegister_Constants(Sqrat::Table &);

// ------------------------------------------------------------------------------------------------
void DRegister_Enums();

// ------------------------------------------------------------------------------------------------
SQInteger Regex_Match(HSQUIRRELVM vm);
} //Namespace:: SqDiscord