#include "Channel.h"

// ------------------------------------------------------------------------------------------------
namespace SqDiscord {

// ------------------------------------------------------------------------------------------------
Channel::Channel(SleepyDiscord::Channel &channel) {
	ID = channel.ID;
	Type = static_cast<ChannelType>(channel.type);
	ServerID = channel.serverID;
	Position = channel.position;
	Name = channel.name;
	Topic = channel.topic;
	isNSFW = channel.isNSFW;
	OwnerID = channel.ownerID;
	ParentID = channel.parentID;

	UpdateRecipients(channel.recipients);
}

// ------------------------------------------------------------------------------------------------
void Channel::UpdateRecipients(std::vector<SleepyDiscord::User> &recipients) {
	Recipients.clear();
	for (auto &recipient : recipients) {
		Recipients[recipient.ID.string()] = recipient;
	}
}

// ------------------------------------------------------------------------------------------------
std::string Channel::GetID() const {
	return ID;
}

int Channel::GetType() const {
	return Type;
}

// ------------------------------------------------------------------------------------------------
CSStr Channel::GetServerID() const {
	if (!ServerID.empty()) {
		return ServerID.c_str();
	}
	return nullptr;
}

// ------------------------------------------------------------------------------------------------
int Channel::GetPosition() const {
	return Position;
}

// ------------------------------------------------------------------------------------------------
std::string Channel::GetName() const {
	return Name;
}

// ------------------------------------------------------------------------------------------------
std::string Channel::GetTopic() const {
	return Topic;
}

// ------------------------------------------------------------------------------------------------
bool Channel::IsNsfw() const {
	return isNSFW;
}

// ------------------------------------------------------------------------------------------------
int Channel::GetRecipientCount() const {
	return Recipients.size();
}

// ------------------------------------------------------------------------------------------------
Array Channel::GetRecipientsArray() {
	if (Recipients.empty()) {
		return Array();
	}

	Array arr(SqVM(), Recipients.size());

	SQInteger idx = 0;

	for (auto &recipient : Recipients) {
		arr.SetValue(idx, recipient.second);

		++idx;
	}

	return arr;
}

Table Channel::GetRecipientsTable() {
	if (Recipients.empty()) {
		return Table();
	}

	Table tbl;

	for (auto &recipient : Recipients) {
		tbl.SetValue(recipient.first.c_str(), recipient.second);
	}

	return tbl;
}

// ------------------------------------------------------------------------------------------------
std::string Channel::GetOwnerId() const {
	return OwnerID;
}

// ------------------------------------------------------------------------------------------------
std::string Channel::GetParentId() const {
	return ParentID;
}

// ------------------------------------------------------------------------------------------------
void Channel::Register_Channel(Table &table) {
	table.Bind("Channel",
			   Class<Channel>(table.GetVM(), "Channel")

					   .Prop("ID", &Channel::GetID)
					   .Prop("Type", &Channel::GetType)
					   .Prop("ServerID", &Channel::GetServerID)
					   .Prop("Position", &Channel::GetPosition)
					   .Prop("Name", &Channel::GetName)
					   .Prop("Topic", &Channel::GetTopic)
					   .Prop("IsNSFW", &Channel::IsNsfw)
					   .Prop("RecipientCount", &Channel::GetRecipientCount)
					   .Prop("RecipientsArray", &Channel::GetRecipientsArray)
					   .Prop("RecipientsTable", &Channel::GetRecipientsTable)
					   .Prop("OwnerID", &Channel::GetOwnerId)
					   .Prop("ParentID", &Channel::GetParentId)
	);
}
} // Namespace:: SqDiscord