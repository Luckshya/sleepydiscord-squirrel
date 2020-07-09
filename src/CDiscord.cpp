// ------------------------------------------------------------------------------------------------
#include "Common.hpp"
#include "CDiscord.h"
#include "EventHandler.h"

// ------------------------------------------------------------------------------------------------
#include <list>
#include <mutex>

// ------------------------------------------------------------------------------------------------
using namespace SqDiscord;
using namespace DiscordEvent;

template<class T, class ...A>
void CDiscord::AddEventObject(EventType<T> t, bool imp, A &&... a) {
	if (!session->s_EventHandler) return;
	if (!imp && session->internalCacheEnabled) return;

	session->s_EventHandler->AddObject(t, std::forward<A>(a)...);
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onMessage(SleepyDiscord::Message message) {
	try {
		std::lock_guard<std::mutex> lock(session->m_Guard);

		AddEventObject(EventType<CMessage>{}, true, message);
	}
	catch (...) {
		OutputError("An Error has occured at [CDiscord] function => [onMessage]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onReady(SleepyDiscord::Ready readyData) {
	try {
		session->isConnected = true;
		session->isConnecting = false;

		std::lock_guard<std::mutex> lock(session->m_Guard);

		AddEventObject(EventType<CReady>{}, true);
	}
	catch (...) {
		OutputError("An Error has occured at [CDiscord] function => [onReady]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onError(SleepyDiscord::ErrorCode errorCode, std::string errorMessage) {
	if (!session->errorEventEnabled) {
		if (errorCode != 0)
			std::cout << "Error " << errorCode << ": " + errorMessage + '\n';
		else
			std::cout << "Error: " + errorMessage + '\n';
	} else {
		try {
			std::lock_guard<std::mutex> lock(session->m_Guard);

			AddEventObject(EventType<CError>{}, true, errorCode, errorMessage);
		}
		catch (...) {
			OutputError("An Error has occured at [CDiscord] function => [onError]");
		}
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onDisconnect() {
	try {
		AddEventObject(EventType<CDisconnect>{}, true);
	}
	catch (...) {
		OutputError("An Error has occured at [CDiscord] function => [onDisconnect]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onQuit() {
	try {
		AddEventObject(EventType<CQuit>{}, true);
	}
	catch (...) {
		OutputError("An Error has occured at [CDiscord] function => [onQuit]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onServer(SleepyDiscord::Server server) {
	try {
		std::lock_guard<std::mutex> lock(session->m_Guard);

		s_Servers[server.ID.string()] = Guild(server);
		session->Servers_Queue.enqueue(s_Servers);

		AddEventObject(EventType<CGuild>{}, false, server);
	}
	catch (...) {
		OutputError("An Error has occured at [CDiscord] function => [onServer]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onEditServer(SleepyDiscord::Server server) {
	try {
		std::lock_guard<std::mutex> lock(session->m_Guard);

		s_Servers[server.ID.string()] = Guild(server);
		session->Servers_Queue.enqueue(s_Servers);

		AddEventObject(EventType<CGuildEdit>{}, false, server);
	}
	catch (...) {
		OutputError("An Error has occured at [CDiscord] function => [onEditServer]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onDeleteServer(SleepyDiscord::UnavailableServer server) {
	try {
		std::lock_guard<std::mutex> lock(session->m_Guard);

		s_Servers.erase(server.ID.string());
		session->Servers_Queue.enqueue(s_Servers);

		AddEventObject(EventType<CGuildDelete>{}, false, server);
	}
	catch (...) {
		OutputError("An Error has occured at [CDiscord] function => [onDeleteServer]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onMember(SleepyDiscord::Snowflake<SleepyDiscord::Server> _serverID, SleepyDiscord::ServerMember member) {
	try {
		std::lock_guard<std::mutex> lock(session->m_Guard);

		auto &serverID = _serverID.string();
		auto index = s_Servers.find(serverID);

		if (index != s_Servers.end()) {
			index->second.Members[member.ID.string()] = member;
		}
		session->Servers_Queue.enqueue(s_Servers);

		AddEventObject(EventType<CMember>{}, false, _serverID.string(), member);
	}
	catch (...) {
		OutputError("An Error has occured at [CDiscord] function => [onMember]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onEditMember(SleepyDiscord::Snowflake<SleepyDiscord::Server> serverID, SleepyDiscord::User user,
							std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>> roles, std::string nick) {
	try {
		std::lock_guard<std::mutex> lock(session->m_Guard);
		auto serverIndex = s_Servers.find(serverID.string());
		if (serverIndex == s_Servers.end()) return;

		auto &members = serverIndex->second.Members;
		auto index = members.find(user.ID.string());

		if (index != members.end()) {
			auto &member = index->second;

			member.User = user;
			member.Nick = nick;
			member.UpdateRoles(roles);
		}
		session->Servers_Queue.enqueue(s_Servers);

		AddEventObject(EventType<CMemberEdit>{}, false, serverID.string(), user, roles, nick);
	}
	catch (...) {
		OutputError("An Error has occured at [CDiscord] function => [onEditMember]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onRemoveMember(SleepyDiscord::Snowflake<SleepyDiscord::Server> _serverID, SleepyDiscord::User user) {
	try {
		std::lock_guard<std::mutex> lock(session->m_Guard);
		auto &serverID = _serverID.string();
		auto serverIndex = s_Servers.find(serverID);

		if (serverIndex != s_Servers.end()) {
			auto &members = serverIndex->second.Members;
			members.erase(user.ID.string());
		}
		session->Servers_Queue.enqueue(s_Servers);

		AddEventObject(EventType<CMemberRemove>{}, false, _serverID.string(), user);
	}
	catch (...) {
		OutputError("An Error has occured at [CDiscord] function => [onRemoveMember]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onChannel(SleepyDiscord::Channel channel) {
	try {
		std::lock_guard<std::mutex> lock(session->m_Guard);

		auto &serverID = channel.serverID.string();
		auto index = s_Servers.find(serverID);

		if (index != s_Servers.end()) {
			index->second.Channels[channel.ID.string()] = channel;
			return;
		}
		session->Servers_Queue.enqueue(s_Servers);

		s_OtherChannels[channel.ID.string()] = channel;
		session->OtherChannels_Queue.enqueue(s_OtherChannels);

		AddEventObject(EventType<CChannel>{}, false, channel);
	}
	catch (...) {
		OutputError("An Error has occured at [CDiscord] function => [onChannel]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onEditChannel(SleepyDiscord::Channel channel) {
	try {
		std::lock_guard<std::mutex> lock(session->m_Guard);

		auto &serverID = channel.serverID.string();
		auto index = s_Servers.find(serverID);

		if (index != s_Servers.end()) {
			auto &server = index->second;
			server.Channels[channel.ID.string()] = channel;
			return;
		}
		session->Servers_Queue.enqueue(s_Servers);

		s_OtherChannels[channel.ID.string()] = channel;
		session->OtherChannels_Queue.enqueue(s_OtherChannels);

		AddEventObject(EventType<CChannelEdit>{}, false, channel);
	}
	catch (...) {
		OutputError("An Error has occured at [CDiscord] function => [onEditChannel]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onDeleteChannel(SleepyDiscord::Channel channel) {
	try {
		std::lock_guard<std::mutex> lock(session->m_Guard);

		auto &serverID = channel.serverID.string();

		auto serverIndex = s_Servers.find(serverID);

		if (serverIndex != s_Servers.end()) {
			auto &channels = serverIndex->second.Channels;
			channels.erase(channel.ID.string());
			return;
		}
		session->Servers_Queue.enqueue(s_Servers);

		s_OtherChannels.erase(channel.ID.string());
		session->OtherChannels_Queue.enqueue(s_OtherChannels);

		AddEventObject(EventType<CChannelDelete>{}, false, channel);
	}
	catch (...) {
		OutputError("An Error has occured at [CDiscord] function => [onDeleteChannel]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onRole(SleepyDiscord::Snowflake<SleepyDiscord::Server> _serverID, SleepyDiscord::Role role) {
	try {
		std::lock_guard<std::mutex> lock(session->m_Guard);

		auto &serverID = _serverID.string();
		auto index = s_Servers.find(serverID);

		if (index != s_Servers.end()) {
			index->second.Roles[role.ID.string()] = role;
		}
		session->Servers_Queue.enqueue(s_Servers);

		AddEventObject(EventType<CRole>{}, false, _serverID.string(), role);
	}
	catch (...) {
		OutputError("An Error has occured at [CDiscord] function => [onRole]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onEditRole(SleepyDiscord::Snowflake<SleepyDiscord::Server> _serverID, SleepyDiscord::Role role) {
	try {
		std::lock_guard<std::mutex> lock(session->m_Guard);

		auto &serverID = _serverID.string();
		auto index = s_Servers.find(serverID);

		if (index != s_Servers.end()) {
			auto &server = index->second;
			server.Roles[role.ID.string()] = role;
		}
		session->Servers_Queue.enqueue(s_Servers);

		AddEventObject(EventType<CRoleEdit>{}, false, _serverID.string(), role);
	}
	catch (...) {
		OutputError("An Error has occured at [CDiscord] function => [onEditRole]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onDeleteRole(SleepyDiscord::Snowflake<SleepyDiscord::Server> _serverID,
							SleepyDiscord::Snowflake<SleepyDiscord::Role> roleID) {
	try {
		std::lock_guard<std::mutex> lock(session->m_Guard);

		auto &serverID = _serverID.string();
		auto serverIndex = s_Servers.find(serverID);

		if (serverIndex != s_Servers.end()) {
			auto &roles = serverIndex->second.Roles;
			roles.erase(roleID.string());
		}
		session->Servers_Queue.enqueue(s_Servers);

		AddEventObject(EventType<CRoleDelete>{}, false, _serverID.string(), roleID.string());
	}
	catch (...) {
		OutputError("An Error has occured at [CDiscord] function => [onDeleteRole]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onEditUser(SleepyDiscord::User user) {
	try {
		std::lock_guard<std::mutex> lock(session->m_Guard);

		auto &userID = user.ID.string();

		for (auto &server : s_Servers) {
			auto memberIndex = server.second.Members.find(userID);

			if (memberIndex != server.second.Members.end()) {
				memberIndex->second.User = user;
			}
		}
		session->Servers_Queue.enqueue(s_Servers);

		for (auto &channel : s_OtherChannels) {
			auto userIndex = channel.second.Recipients.find(userID);

			if (userIndex != channel.second.Recipients.end()) {
				userIndex->second = user;
			}
		}
		session->OtherChannels_Queue.enqueue(s_OtherChannels);

		AddEventObject(EventType<CUserEdit>{}, false, user);
	}
	catch (...) {
		OutputError("An Error has occured at [CDiscord] function => [onEditUser]");
	}
}
