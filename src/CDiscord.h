#pragma once

// ------------------------------------------------------------------------------------------------
#include "sleepy_discord/websocketpp_websocket.h"
#include "CSession.h"
#include "Guild.h"

// ------------------------------------------------------------------------------------------------
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>

using namespace DiscordEvent;

// ------------------------------------------------------------------------------------------------
class CDiscord : public SleepyDiscord::DiscordClient {

public:
	using SleepyDiscord::DiscordClient::DiscordClient;

	std::unordered_map<std::string, SqDiscord::Channel> s_OtherChannels;
	std::unordered_map<std::string, SqDiscord::Guild> s_Servers;
	SqDiscord::CSession *session;

	void onMessage(SleepyDiscord::Message message) override;

	void onReady(SleepyDiscord::Ready readyData) override;

	void onServer(SleepyDiscord::Server server) override;

	void onEditServer(SleepyDiscord::Server server) override;

	void onDeleteServer(SleepyDiscord::UnavailableServer server) override;

	void
	onMember(SleepyDiscord::Snowflake<SleepyDiscord::Server> serverID, SleepyDiscord::ServerMember member) override;

	void onRemoveMember(SleepyDiscord::Snowflake<SleepyDiscord::Server> serverID, SleepyDiscord::User user) override;

	void onEditMember(SleepyDiscord::Snowflake<SleepyDiscord::Server> serverID, SleepyDiscord::User user,
					  std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>> roles, std::string nick) override;

	void onChannel(SleepyDiscord::Channel channel) override;

	void onEditChannel(SleepyDiscord::Channel channel) override;

	void onDeleteChannel(SleepyDiscord::Channel channel) override;

	void onRole(SleepyDiscord::Snowflake<SleepyDiscord::Server> serverID, SleepyDiscord::Role role) override;

	void onDeleteRole(SleepyDiscord::Snowflake<SleepyDiscord::Server> serverID,
					  SleepyDiscord::Snowflake<SleepyDiscord::Role> roleID) override;

	void onEditRole(SleepyDiscord::Snowflake<SleepyDiscord::Server> serverID, SleepyDiscord::Role role) override;

	void onEditUser(SleepyDiscord::User user) override;

	void onError(SleepyDiscord::ErrorCode errorCode, std::string errorMessage) override;

	void onDisconnect() override;

	void onQuit() override;

	template<class T, class ...A>
	void AddEventObject(EventType<T> t, bool imp, A &&... a);
};