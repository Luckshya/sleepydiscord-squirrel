#pragma once

// ------------------------------------------------------------------------------------------------
#include "Common.hpp"
#include "Message.h"
#include "Guild.h"

// ------------------------------------------------------------------------------------------------
#include <thread>
#include <mutex>
#include <readerwriterqueue.h>

// ------------------------------------------------------------------------------------------------
using namespace DiscordEvent;
using namespace moodycamel;

// ------------------------------------------------------------------------------------------------
namespace SqDiscord {
class CSession {
private:
	CDiscord *client = nullptr;

	void runSleepy(std::string);

public:
	// --------------------------------------------------------------------------------------------
	std::thread *sleepyThread = nullptr;
	EventHandler *s_EventHandler = nullptr;

	//unsigned short int connID	= 0;
	bool isConnecting = false;
	bool isConnected = false;
	bool errorEventEnabled = false;
	bool internalCacheEnabled = true;

	unsigned short int connID = 0;

	// Mutex lock to guard while connecting and disconnecting
	std::mutex m_Guard;

	std::unordered_map<std::string, SqDiscord::Channel> LatestCopy_OtherChannels;
	std::unordered_map<std::string, SqDiscord::Guild> LatestCopy_Servers;

	ReaderWriterQueue <std::unordered_map<std::string, SqDiscord::Channel>> OtherChannels_Queue;
	ReaderWriterQueue <std::unordered_map<std::string, SqDiscord::Guild>> Servers_Queue;

	CSession();

	~CSession();

	CSession(const CSession &o) = delete;

	CSession(CSession &&o) = delete;

	static void Process();

	static void Terminate();

	void Update();

	void Disconnect();

	void Destroy();

	unsigned short int GetConnID();

	Object GetGuild(const std::string &serverID);

	Object GetOtherChannel(const std::string &channelID);

	bool GetErrorEventEnabled() const;

	void SetErrorEventEnabled(bool toggle);

	bool GetInternalCacheEnabled() const;

	void SetInternalCacheEnabled(bool toggle);

	static SQInteger Connect(HSQUIRRELVM vm);

	static SQInteger Message(HSQUIRRELVM vm);

	static SQInteger MessageEmbed(HSQUIRRELVM vm);

	static SQInteger GetRoleName(HSQUIRRELVM vm);

	static SQInteger EditChannel(HSQUIRRELVM vm);

	static SQInteger SetActivity(HSQUIRRELVM vm);

	static void DRegister_CSession(Sqrat::Table &);
};
} //Namespace:: SqDiscord