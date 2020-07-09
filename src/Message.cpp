#include "Message.h"

// ------------------------------------------------------------------------------------------------
namespace SqDiscord {

// ------------------------------------------------------------------------------------------------
Message::Message(SleepyDiscord::Message &message) {
	ID = message.ID;
	Type = static_cast<MessageType>(message.type);
	ChannelID = message.channelID;
	ServerID = message.serverID;
	Author = message.author;
	Member = message.member;
	Member.ID = message.author.ID;
	Member.User = message.author;
	Content = message.content;
	Timestamp = message.timestamp;
	isTTS = message.tts;
	MentionEveryone = message.mentionEveryone;
	UpdateUserMentions(message.mentions);
	UpdateRoleMentions(message.mentionRoles);
}


// ------------------------------------------------------------------------------------------------
void Message::UpdateUserMentions(std::vector<SleepyDiscord::User> &mentions) {
	Mentions.clear();
	for (auto &user : mentions) {
		Mentions.emplace_back(user);
	}
}

// ------------------------------------------------------------------------------------------------
void Message::UpdateRoleMentions(std::vector<SleepyDiscord::Snowflake<SleepyDiscord::User>> &mentions) {
	MentionRoles.clear();
	for (auto &roleID : mentions) {
		MentionRoles.emplace_back(roleID.string());
	}
}

// ------------------------------------------------------------------------------------------------
std::string Message::GetID() const {
	return ID;
}

// ------------------------------------------------------------------------------------------------
int Message::GetType() const {
	return Type;
}

// ------------------------------------------------------------------------------------------------
std::string Message::GetChannelID() const {
	return ChannelID;
}

// ------------------------------------------------------------------------------------------------
CSStr Message::GetServerID() const {
	if (!ServerID.empty()) {
		return ServerID.c_str();
	}
	return nullptr;
}

// ------------------------------------------------------------------------------------------------
Object Message::GetAuthor() {
	if (Author.ID.empty()) {
		return Object{};
	}

	return Object(Author, SqVM());
}

// ------------------------------------------------------------------------------------------------
Object Message::GetMember() {
	if (Member.JoinedAt.empty()) {
		return Object{};
	}

	return Object(Member, SqVM());
}

// ------------------------------------------------------------------------------------------------
std::string Message::GetContent() const {
	return Content;
}

// ------------------------------------------------------------------------------------------------
std::string Message::GetTimestamp() const {
	return Timestamp;
}

// ------------------------------------------------------------------------------------------------
bool Message::IsTTS() const {
	return isTTS;
}

// ------------------------------------------------------------------------------------------------
bool Message::IsMentionEveryone() const {
	return MentionEveryone;
}

// ------------------------------------------------------------------------------------------------
int Message::GetUserMentionCount() const {
	return Mentions.size();
}

// ------------------------------------------------------------------------------------------------
Array Message::GetUserMentions() {
	SQInteger count = Mentions.size();

	if (count == 0) {
		return Array(SqVM(), 0);
	}

	Array arr(SqVM(), count);

	SQInteger idx = 0;

	for (auto &user : Mentions) {
		arr.SetValue(idx, user);

		++idx;
	}

	return arr;
}

// ------------------------------------------------------------------------------------------------
int Message::GetRoleMentionCount() const {
	return MentionRoles.size();
}

// ------------------------------------------------------------------------------------------------
Array Message::GetRoleMentions() {
	SQInteger count = MentionRoles.size();

	if (count == 0) {
		return Array(SqVM(), 0);
	}

	Array arr(SqVM(), count);

	SQInteger idx = 0;

	for (auto &role : MentionRoles) {
		arr.SetValue(idx, role);

		++idx;
	}

	return arr;
}

// ------------------------------------------------------------------------------------------------
void Message::Register_Message(Table &table) {
	table.Bind("Message",
			   Class<Message>(table.GetVM(), "Message")

					   .Prop("ID", &Message::GetID)
					   .Prop("Type", &Message::GetType)
					   .Prop("ChannelID", &Message::GetChannelID)
					   .Prop("ServerID", &Message::GetServerID)
					   .Prop("Author", &Message::GetAuthor)
					   .Prop("Member", &Message::GetMember)
					   .Prop("Content", &Message::GetContent)
					   .Prop("Timestamp", &Message::GetTimestamp)
					   .Prop("IsTTS", &Message::IsTTS)
					   .Prop("MentionEveryone", &Message::IsMentionEveryone)
					   .Prop("UserMentionCount", &Message::GetUserMentionCount)
					   .Prop("UserMentions", &Message::GetUserMentions)
					   .Prop("RoleMentionCount", &Message::GetRoleMentionCount)
					   .Prop("RoleMentions", &Message::GetRoleMentions)
	);
}
}
