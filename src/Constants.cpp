#include "Constants.h"

// ------------------------------------------------------------------------------------------------
#include <regex>

// ------------------------------------------------------------------------------------------------
#define ENUM_SIZE(x) sizeof(x)/sizeof(myEnum)

namespace SqDiscord {
// ------------------------------------------------------------------------------------------------
struct myEnum {
	const char *identifier;
	int value;
};

// ------------------------------------------------------------------------------------------------
static const myEnum discord_Events[] = {
		{"Ready",         ON_READY},
		{"Message",       ON_MESSAGE},
		{"Error",         ON_ERROR},
		{"Disconnect",    ON_DISCONNECT},
		{"Quit",          ON_QUIT},
		{"Guild",         ON_SERVER},
		{"GuildEdit",     ON_SERVER_EDIT},
		{"GuildDelete",   ON_SERVER_DELETE},
		{"Member",        ON_MEMBER},
		{"MemberEdit",    ON_MEMBER_EDIT},
		{"MemberRemove",  ON_MEMBER_REMOVE},
		{"Channel",       ON_CHANNEL},
		{"ChannelEdit",   ON_CHANNEL_EDIT},
		{"ChannelDelete", ON_CHANNEL_DELETE},
		{"Role",          ON_ROLE},
		{"RoleEdit",      ON_ROLE_EDIT},
		{"RoleDelete",    ON_ROLE_DELETE},
		{"UserEdit",      ON_USER_EDIT}
};

// ------------------------------------------------------------------------------------------------
static const myEnum discord_ChannelTypes[] = {
		{"None",           CHANNEL_TYPE_NONE},
		{"ServerText",     SERVER_TEXT},
		{"DM",             DM},
		{"ServerVoice",    SERVER_VOICE},
		{"GroupDM",        GROUP_DM},
		{"ServerCategory", SERVER_CATEGORY},
		{"GuildNews",      GUILD_NEWS},
		{"GuildStore",     GUILD_STORE}
};

// ------------------------------------------------------------------------------------------------
static const myEnum discord_MessageTypes[] = {
		{"Default",         DEFAULT},
		{"RecipientAdd",    RECIPIENT_ADD},
		{"RecipientRemove", RECIPIENT_REMOVE},
		{"Call",            CALL},
		{"ChanNameChange",  CHANNEL_NAME_CHANGE},
		{"ChanIconChange",  CHANNEL_ICON_CHANGE},
		{"ChanPinnedMsg",   CHANNEL_PINNED_MESSAGE},
		{"GuildMemberJoin", GUILD_MEMBER_JOIN}
};

// ------------------------------------------------------------------------------------------------
void DRegisterEnum(HSQUIRRELVM vm, const char *name, const myEnum *data, int count) {
	using namespace Sqrat;

	Enumeration e(vm);

	for (int n = 0; n < count; ++n, ++data) {
		e.Const(data->identifier, data->value);
	}

	ConstTable(vm).Enum(name, e);
}

// ------------------------------------------------------------------------------------------------
void DRegister_Constants(Sqrat::Table &discordcn) {
	DRegisterEnum(discordcn.GetVM(), "SqDiscordEvent", discord_Events, ENUM_SIZE(discord_Events));
	DRegisterEnum(discordcn.GetVM(), "SqDiscordChanType", discord_ChannelTypes, ENUM_SIZE(discord_ChannelTypes));
	DRegisterEnum(discordcn.GetVM(), "SqDiscordMsgType", discord_MessageTypes, ENUM_SIZE(discord_MessageTypes));
}

// ------------------------------------------------------------------------------------------------
SQInteger Regex_Match(HSQUIRRELVM vm) {
	const SQChar *regex_string;
	const SQChar *value_string;

	if (SQ_FAILED(sq_getstring(vm, 2, &regex_string))) {
		return sq_throwerror(vm, "Unable to retrieve argument 1 as string");
	} else if (SQ_FAILED(sq_getstring(vm, 3, &value_string))) {
		return sq_throwerror(vm, "Unable to retrieve argument 2 as string");
	}

	try {
		std::regex r(regex_string);
		std::string s(value_string);

		std::smatch string_flag;

		bool matches = std::regex_match(s, r);

		sq_pushbool(vm, matches);
	}
	catch (std::regex_error &e) {
		return sq_throwerror(vm, e.what());
	}
	catch (...) {
		return sq_throwerror(vm, "An Error has occured at [Global] function => [Regex_Match]");
	}

	return 1;
}
} //Namespace:: SqDiscord