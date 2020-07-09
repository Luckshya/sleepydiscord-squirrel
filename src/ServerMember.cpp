#include "ServerMember.h"

#define SqVM DefaultVM::Get

// ------------------------------------------------------------------------------------------------
namespace SqDiscord {

// ------------------------------------------------------------------------------------------------
ServerMember::ServerMember(SleepyDiscord::ServerMember &member) {
	ID = member.ID;
	User = DUser(member.user);
	Nick = member.nick;
	JoinedAt = member.joinedAt;
	isDeaf = member.deaf;
	isMute = member.mute;

	UpdateRoles(member.roles);
}

// ------------------------------------------------------------------------------------------------
void ServerMember::UpdateRoles(std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>> &roles) {
	Roles.clear();
	for (auto &role : roles) {
		Roles.push_back(role.string());
	}
}

// ------------------------------------------------------------------------------------------------
std::string ServerMember::GetID() const {
	return ID;
}

// ------------------------------------------------------------------------------------------------
Object ServerMember::GetUser() {
	if (User.ID.empty()) {
		return Object{};
	}

	return Object(User, SqVM());
}

// ------------------------------------------------------------------------------------------------
std::string ServerMember::GetNick() const {
	return Nick;
}

// ------------------------------------------------------------------------------------------------
int ServerMember::GetRoleCount() const {
	return Roles.size();
}

// ------------------------------------------------------------------------------------------------
Array ServerMember::GetRoles() {
	if (Roles.empty()) {
		return Array();
	}

	Array arr(SqVM(), Roles.size());

	SQInteger idx = 0;

	for (auto &role : Roles) {
		arr.SetValue(idx, role);

		++idx;
	}

	return arr;
}

// ------------------------------------------------------------------------------------------------
std::string ServerMember::GetJoinedAt() const {
	return JoinedAt;
}

// ------------------------------------------------------------------------------------------------
bool ServerMember::IsDeaf() const {
	return isDeaf;
}

// ------------------------------------------------------------------------------------------------
bool ServerMember::IsMute() const {
	return isMute;
}

// ------------------------------------------------------------------------------------------------
void ServerMember::Register_ServerMember(Table &table) {
	table.Bind("ServerMember",
			   Class<ServerMember>(table.GetVM(), "ServerMember")

					   .Prop("ID", &ServerMember::GetID)
					   .Prop("User", &ServerMember::GetUser)
					   .Prop("Nick", &ServerMember::GetNick)
					   .Prop("RoleCount", &ServerMember::GetRoleCount)
					   .Prop("Roles", &ServerMember::GetRoles)
					   .Prop("JoinedAt", &ServerMember::GetJoinedAt)
					   .Prop("IsDeaf", &ServerMember::IsDeaf)
					   .Prop("IsMute", &ServerMember::IsMute)
	);
}
} //Namespace:: SqDiscord