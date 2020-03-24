#pragma once

// ------------------------------------------------------------------------------------------------
#include "sqrat.h"
#include "CMessage.h"

// ------------------------------------------------------------------------------------------------
#include <thread>

// guard to lock while disconnecting
extern std::mutex m_Guard;

// ------------------------------------------------------------------------------------------------
class CDiscord;

// ------------------------------------------------------------------------------------------------
namespace SqDiscord
{
typedef const char * CCStr;

class CSession
{
public:
	CCStr token = NULL;
	CDiscord * client = nullptr;
	std::thread * sleepyThread = nullptr;
	unsigned short int connID = 0;
	bool isConnecting = false;
	bool isConnected = false;

	// Mutex lock to guard s_Messages container
	std::mutex m_MsgGuard;

	// Mutex lock to guard s_ReadySessions container
	std::mutex m_ReadyGuard;

	// Container to hold messages
	std::vector<CMessage> s_Messages;

	// Container to hold readyEvent to be called in a Queue
	std::vector<CSession *> s_ReadySession;

	CSession();
	~CSession();
	
	static void Process();
	static void Terminate();

	void Update();
	void runSleepy();
	void Disconnect();
	void Destroy();
	unsigned short int GetConnID();

	static SQInteger Connect(HSQUIRRELVM vm);
	static SQInteger Message(HSQUIRRELVM vm);
	static SQInteger MessageEmbed(HSQUIRRELVM vm);
	static SQInteger GetRoleName(HSQUIRRELVM vm);
	static SQInteger SetActivity(HSQUIRRELVM vm);
};

void Register_CSession(Sqrat::Table discordcn);
}