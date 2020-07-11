#pragma once

// ------------------------------------------------------------------------------------------------
#include <vector>
#include <string>
#include <tuple>
#include <typeinfo>

// ------------------------------------------------------------------------------------------------
#include "CSession.h"

// ------------------------------------------------------------------------------------------------
typedef std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>> sleepyRoles;

// ------------------------------------------------------------------------------------------------
namespace DiscordEvent {
// ------------------------------------------------------------------------------------------------
// Forward declarations
class CError;

class CReady;

class CDisconnect;

class CQuit;

class CMessage;

class CGuild;

class CGuildEdit;

class CGuildDelete;

class CChannel;

class CChannelEdit;

class CChannelDelete;

class CRole;

class CRoleEdit;

class CRoleDelete;

class CMember;

class CMemberEdit;

class CMemberRemove;

class CUserEdit;

// ------------------------------------------------------------------------------------------------
using namespace SqDiscord;
using namespace moodycamel;

// ------------------------------------------------------------------------------------------------
template<class T>
struct EventType {
};

// ------------------------------------------------------------------------------------------------
class SqEvent {
public:
	virtual ~SqEvent() = default;

	virtual void PushObject(CSession *session) = 0;

	template<class ...A>
	void ForwardEvent(CSession *session, int eventType, const std::string &name, A &&... args) {
		HSQUIRRELVM vm = DefaultVM::Get();

		Function listener = RootTable(vm).GetFunction("onDiscordUpdate");

		if (listener.IsNull()) {
			return;
		}

		try {
			listener.Execute(session->connID, eventType, std::forward<A>(args)...);
		}
		catch (Sqrat::Exception &e) {
			OutputError("Discord event [%s] => Squirrel error [%s]", name.c_str(), e.what());
		}
		catch (const std::exception &e) {
			OutputError("Discord event [%s] => Program error [%s]", name.c_str(), e.what());
		}
		catch (...) {
			OutputError("Discord event [%s] => Unknown error", name.c_str());
		}
	}
};

// ------------------------------------------------------------------------------------------------
class EventHandler {
private :
	ReaderWriterQueue<SqEvent *> m_GenericQueue;
	ReaderWriterQueue<SqEvent *> m_ErrorQueue;
	ReaderWriterQueue<SqEvent *> m_MsgQueue;
public :
	EventHandler() = default;

	template<class T, class ...A>
	void AddObject(EventType<T>, A &&... a) {
		if (typeid(CError) == typeid(T)) {
			m_ErrorQueue.enqueue(new T(std::forward<A>(a)...));
		} else if (typeid(CMessage) == typeid(T)) {
			m_MsgQueue.enqueue(new T(std::forward<A>(a)...));
		} else {
			m_GenericQueue.enqueue(new T(std::forward<A>(a)...));
		}
	}

	void PushEvents(CSession *session) {
		SqEvent *data;

		while (m_GenericQueue.try_dequeue(data)) {
			data->PushObject(session);
			delete data;
			data = nullptr;
		}

		while (m_MsgQueue.try_dequeue(data)) {
			data->PushObject(session);
			delete data;
			data = nullptr;
		}

		while (m_ErrorQueue.try_dequeue(data)) {
			data->PushObject(session);
			delete data;
			data = nullptr;
		}
	}
};

// ------------------------------------------------------------------------------------------------
class CError : public SqEvent {
private:
	std::tuple<int, std::string> m_Data;
public :
	explicit CError(int code, const std::string &message) {
		m_Data = std::move(std::make_tuple(code, message));
	}

	void PushObject(CSession *session) override {
		ForwardEvent(session, ON_ERROR, "ERROR", std::get<0>(m_Data), std::get<1>(m_Data));
	}
};

// ------------------------------------------------------------------------------------------------
class CReady : public SqEvent {
public :
	CReady() = default;

	void PushObject(CSession *session) override {
		ForwardEvent(session, ON_READY, "READY");
	}
};

// ------------------------------------------------------------------------------------------------
class CDisconnect : public SqEvent {
public :
	CDisconnect() = default;

	void PushObject(CSession *session) override {
		ForwardEvent(session, ON_DISCONNECT, "DISCONNECT");
	}
};

// ------------------------------------------------------------------------------------------------
class CQuit : public SqEvent {
public :
	CQuit() = default;

	void PushObject(CSession *session) override {
		ForwardEvent(session, ON_QUIT, "QUIT");
	}
};

// ------------------------------------------------------------------------------------------------
class CMessage : public SqEvent {
private :
	Message m_Data;
public:
	explicit CMessage(SleepyDiscord::Message &message) {
		m_Data = std::move(Message(message));
	}

	void PushObject(CSession *session) override {
		ForwardEvent(session, ON_MESSAGE, "MESSAGE", std::move(m_Data));
	}
};

// ------------------------------------------------------------------------------------------------
class CGuild : public SqEvent {
private:
	Guild m_Data;
public:
	explicit CGuild(SleepyDiscord::Server &server) {
		m_Data = std::move(Guild(server));
	}

	void PushObject(CSession *session) override {
		ForwardEvent(session, ON_SERVER, "GUILD", std::move(m_Data));
	}
};

// ------------------------------------------------------------------------------------------------
class CGuildEdit : public SqEvent {
private :
	Guild m_Data;
public:
	explicit CGuildEdit(SleepyDiscord::Server &server) {
		m_Data = std::move(Guild(server));
	}

	void PushObject(CSession *session) override {
		ForwardEvent(session, ON_SERVER_EDIT, "GUILD_EDIT", std::move(m_Data));
	}
};

// ------------------------------------------------------------------------------------------------
class CGuildDelete : public SqEvent {
private :
	Guild m_Data;
public:
	explicit CGuildDelete(SleepyDiscord::UnavailableServer &server) {
		m_Data = std::move(Guild(reinterpret_cast<SleepyDiscord::Server &>(server)));
	}

	void PushObject(CSession *session) override {
		ForwardEvent(session, ON_SERVER_DELETE, "GUILD_DELETE", std::move(m_Data));
	}
};

// ------------------------------------------------------------------------------------------------
class CChannel : public SqEvent {
private:
	Channel m_Data;
public :
	explicit CChannel(SleepyDiscord::Channel &channel) {
		m_Data = std::move(Channel(channel));
	}

	void PushObject(CSession *session) override {
		ForwardEvent(session, ON_CHANNEL, "CHANNEL", std::move(m_Data));
	}
};

// ------------------------------------------------------------------------------------------------
class CChannelEdit : public SqEvent {
private:
	Channel m_Data;
public :
	explicit CChannelEdit(SleepyDiscord::Channel &channel) {
		m_Data = std::move(Channel(channel));
	}

	void PushObject(CSession *session) override {
		ForwardEvent(session, ON_CHANNEL_EDIT, "CHANNEL_EDIT", std::move(m_Data));
	}
};

// ------------------------------------------------------------------------------------------------
class CChannelDelete : public SqEvent {
private:
	Channel m_Data;
public :
	explicit CChannelDelete(SleepyDiscord::Channel &channel) {
		m_Data = std::move(Channel(channel));
	}

	void PushObject(CSession *session) override {
		ForwardEvent(session, ON_CHANNEL_DELETE, "CHANNEL_DELETE", std::move(m_Data));
	}
};

// ------------------------------------------------------------------------------------------------
class CRole : public SqEvent {
private:
	std::tuple<std::string, Role> m_Data;
public :
	explicit CRole(const std::string &serverID, SleepyDiscord::Role &role) {
		m_Data = std::move(std::make_tuple(serverID, std::move(Role(role))));
	}

	void PushObject(CSession *session) override {
		ForwardEvent(session, ON_ROLE, "ROLE", std::get<0>(m_Data), std::move(std::get<1>(m_Data)));
	}
};

// ------------------------------------------------------------------------------------------------
class CRoleEdit : public SqEvent {
private:
	std::tuple<std::string, Role> m_Data;
public :
	explicit CRoleEdit(const std::string &serverID, SleepyDiscord::Role &role) {
		m_Data = std::move(std::make_tuple(serverID, std::move(Role(role))));
	}

	void PushObject(CSession *session) override {
		ForwardEvent(session, ON_ROLE_EDIT, "ROLE_EDIT", std::get<0>(m_Data), std::move(std::get<1>(m_Data)));
	}
};

// ------------------------------------------------------------------------------------------------
class CRoleDelete : public SqEvent {
private:
	std::tuple<std::string, std::string> m_Data;
public :
	explicit CRoleDelete(const std::string &serverID, const std::string &roleID) {
		m_Data = std::move(std::make_tuple(serverID, roleID));
	}

	void PushObject(CSession *session) override {
		ForwardEvent(session, ON_ROLE_DELETE, "ROLE_DELETE", std::get<0>(m_Data), std::get<1>(m_Data));
	}
};

// ------------------------------------------------------------------------------------------------
class CMember : public SqEvent {
private:
	std::tuple<std::string, ServerMember> m_Data;
public :
	explicit CMember(const std::string &serverID, SleepyDiscord::ServerMember &member) {
		m_Data = std::move(std::make_tuple(serverID, std::move(ServerMember(member))));
	}

	void PushObject(CSession *session) override {
		ForwardEvent(session, ON_MEMBER, "MEMBER", std::get<0>(m_Data), std::move(std::get<1>(m_Data)));
	}
};

// ------------------------------------------------------------------------------------------------
class CMemberEdit : public SqEvent {
private:
	std::tuple<std::string, User, sleepyRoles, std::string> m_Data;
public :
	explicit CMemberEdit(const std::string &serverID, SleepyDiscord::User &user, sleepyRoles &roles,
						 const std::string &nick) {
		m_Data = std::move(std::make_tuple(serverID, std::move(User(user)), roles, nick));
	}

	void PushObject(CSession *session) override {
		sleepyRoles &sRoles = std::get<2>(m_Data);
		Array roles(SqVM(), sRoles.size());

		SQInteger idx = 0;
		for (auto &role : sRoles) {
			roles.SetValue(idx, role.string().c_str());
			++idx;
		}

		ForwardEvent(session, ON_MEMBER_EDIT, "MEMBER_EDIT", std::get<0>(m_Data), std::move(std::get<1>(m_Data)), roles,
					 std::get<3>(m_Data));
	}
};

// ------------------------------------------------------------------------------------------------
class CMemberRemove : public SqEvent {
private:
	std::tuple<std::string, User> m_Data;
public :
	explicit CMemberRemove(const std::string &serverID, SleepyDiscord::User &user) {
		m_Data = std::move(std::make_tuple(serverID, std::move(User(user))));
	}

	void PushObject(CSession *session) override {
		ForwardEvent(session, ON_MEMBER_REMOVE, "MEMBER_REMOVE", std::get<0>(m_Data), std::move(std::get<1>(m_Data)));
	}
};

// ------------------------------------------------------------------------------------------------
class CUserEdit : public SqEvent {
private:
	User m_Data;
public :
	explicit CUserEdit(SleepyDiscord::User &user) {
		m_Data = std::move(User(user));
	}

	void PushObject(CSession *session) override {
		ForwardEvent(session, ON_USER_EDIT, "USER_EDIT", std::move(m_Data));
	}
};
}