// ------------------------------------------------------------------------------------------------
#include "CSession.h"

// ------------------------------------------------------------------------------------------------
#include <utility>
#include "CDiscord.h"
#include "DEmbed.h"
#include "EventHandler.h"

// ------------------------------------------------------------------------------------------------
namespace SqDiscord {
// variable to hold in case on one connection only
CSession *s_Session = nullptr;

// container to hold connections
std::vector<CSession *> s_Sessions;

// ------------------------------------------------------------------------------------------------
CSession::CSession() {
	try {
		if (!s_Session && s_Sessions.empty()) {
			s_Session = this;
			connID = 0;
		}
			// Is this the second session instance?
		else if (s_Sessions.empty()) {
			s_Sessions.push_back(s_Session);
			s_Session = nullptr;
			s_Sessions.push_back(this);
			connID = 1;
		}
			// This is part of multiple session instances
		else {
			connID = s_Sessions.size();
			s_Sessions.push_back(this);
		}

		s_EventHandler = new EventHandler();
	}
	catch (...) {
		OutputError("An Error has occured at [CSession] function => [CSession]");
	}
}

// ------------------------------------------------------------------------------------------------
void CSession::Process() {
	// Do we only have one Discord session?
	if (s_Session) {
		s_Session->Update();
	}
		// Do we have multiple sessions?
	else if (!s_Sessions.empty()) {
		for (auto &session : s_Sessions) {
			session->Update();
		}
	}
}

// ------------------------------------------------------------------------------------------------
void CSession::Update() {
	if (!client) {
		return;
	}

	if (!client->session) {
		return;
	}

	if (!isConnected) {
		return;
	}

	if (internalCacheEnabled) {
		while (Servers_Queue.try_dequeue(LatestCopy_Servers)) {};
		while (OtherChannels_Queue.try_dequeue(LatestCopy_OtherChannels)) {};
	}

	s_EventHandler->PushEvents(this);
}

// ------------------------------------------------------------------------------------------------
unsigned short int CSession::GetConnID() {
	return connID;
}

// ------------------------------------------------------------------------------------------------
SQInteger CSession::Connect(HSQUIRRELVM vm) {
	const int top = sq_gettop(vm);

	if (top <= 1) {
		return sq_throwerror(vm, "Missing the token value");
	}

	CSession *session = nullptr;

	try {
		session = Sqrat::Var<CSession *>(vm, 1).value;
	}
	catch (const Sqrat::Exception &e) {
		return sq_throwerror(vm, e.what());
	}

	if (!session) {
		return sq_throwerror(vm, "Invalid session instance");
	}

	if (session->isConnecting) {
		return sq_throwerror(vm, "Already trying to connect or disconnect");
	}

	if (session->isConnected) {
		return sq_throwerror(vm, "Already connected");
	}

	CCStr token = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 2, &token))) {
		return sq_throwerror(vm, "Failed to retrieve argument 1 as string");
	}

	try {
		// initialize the connection
		session->sleepyThread = new std::thread(&CSession::runSleepy, session, std::string(token));
	}
	catch (...) {
		OutputError("An Error has occured at [CSession] function => [Connect]");
	}

	return 0;
}

// ------------------------------------------------------------------------------------------------
void CSession::runSleepy(std::string token) {
	try {
		{
			std::lock_guard<std::mutex> lock(m_Guard);

			this->isConnecting = true;
			this->client = new CDiscord(std::move(token));
			this->client->session = this;
		}

		client->run();
	}
	catch (...) {
		OutputError("An Error has occured at [CSession] function => [runSleepy]");
	}
}

// ------------------------------------------------------------------------------------------------
bool CSession::GetErrorEventEnabled() const {
	return errorEventEnabled;
}

// ------------------------------------------------------------------------------------------------
void CSession::SetErrorEventEnabled(bool toggle) {
	errorEventEnabled = toggle;
}

// ------------------------------------------------------------------------------------------------
bool CSession::GetInternalCacheEnabled() const {
	return internalCacheEnabled;
}

// ------------------------------------------------------------------------------------------------
void CSession::SetInternalCacheEnabled(bool toggle) {
	if (isConnected || isConnecting) {
		OutputError("Cannot toggle internal cache while already connected or connecting");
		return;
	}

	internalCacheEnabled = toggle;
}

// ------------------------------------------------------------------------------------------------
SQInteger CSession::Message(HSQUIRRELVM vm) {
	const int top = sq_gettop(vm);

	if (top <= 1) {
		return sq_throwerror(vm, "Missing the channel ID value");
	} else if (top <= 2) {
		return sq_throwerror(vm, "Missing the message value");
	}

	CSession *session = nullptr;

	try {
		session = Sqrat::Var<CSession *>(vm, 1).value;
	}
	catch (const Sqrat::Exception &e) {
		return sq_throwerror(vm, e.what());
	}

	if (!session) {
		return sq_throwerror(vm, "Invalid session instance");
	} else if (!session->client) {
		return sq_throwerror(vm, "Invalid Discord client");
	} else if (!session->isConnected) {
		return sq_throwerror(vm, "Session is not connected");
	}

	CCStr channelID = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 2, &channelID))) {
		return sq_throwerror(vm, "Failed to retrieve argument 1 as string");
	}

	CCStr message = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 3, &message))) {
		return sq_throwerror(vm, "Failed to retrieve argument 2 as string");
	}

	try {
		auto msg = session->client->sendMessage(channelID, message, SleepyDiscord::Async);
	}
	catch (...) {
		OutputError("An Error has occured at [CSession] function => [Message]");
	}

	return 0;
}

// ------------------------------------------------------------------------------------------------
SQInteger CSession::MessageEmbed(HSQUIRRELVM vm) {
	const int top = sq_gettop(vm);

	if (top <= 1) {
		return sq_throwerror(vm, "Missing the channel ID value");
	} else if (top <= 2) {
		return sq_throwerror(vm, "Missing the content value");
	} else if (top <= 3) {
		return sq_throwerror(vm, "Missing the Embed value");
	}

	CSession *session = nullptr;

	try {
		session = Sqrat::Var<CSession *>(vm, 1).value;
	}
	catch (const Sqrat::Exception &e) {
		return sq_throwerror(vm, e.what());
	}

	if (!session) {
		return sq_throwerror(vm, "Invalid session instance");
	} else if (!session->client) {
		return sq_throwerror(vm, "Invalid Discord client");
	} else if (!session->isConnected) {
		return sq_throwerror(vm, "Session is not connected");
	}

	Embed *embed = nullptr;

	try {
		embed = Sqrat::Var<Embed *>(vm, 4).value;
	}
	catch (const Sqrat::Exception &e) {
		return sq_throwerror(vm, e.what());
	}

	if (!embed) {
		return sq_throwerror(vm, "Invalid Embed instance");
	}

	CCStr channelID = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 2, &channelID))) {
		return sq_throwerror(vm, "Failed to retrieve argument 1 as string");
	}

	CCStr content = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 3, &content))) {
		return sq_throwerror(vm, "Failed to retrieve argument 2 as string");
	}

	try {
		auto msg = session->client->sendMessage(channelID, content, *(embed->embed), SleepyDiscord::TTS::Default,
												SleepyDiscord::Async);
	}
	catch (...) {
		OutputError("An Error has occured at [CSession] function => [MessageEmbed]");
	}

	return 0;
}

// ------------------------------------------------------------------------------------------------
SQInteger CSession::GetRoleName(HSQUIRRELVM vm) {
	const int top = sq_gettop(vm);

	if (top <= 1) {
		return sq_throwerror(vm, "Missing the server ID value");
	} else if (top <= 2) {
		return sq_throwerror(vm, "Missing the role ID value");
	}

	CSession *session = nullptr;

	try {
		session = Sqrat::Var<CSession *>(vm, 1).value;
	}
	catch (const Sqrat::Exception &e) {
		return sq_throwerror(vm, e.what());
	}

	if (!session) {
		return sq_throwerror(vm, "Invalid session instance");
	} else if (!session->client) {
		return sq_throwerror(vm, "Invalid Discord client");
	} else if (!session->isConnected) {
		return sq_throwerror(vm, "Session is not connected");
	}

	CCStr serverID = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 2, &serverID))) {
		return sq_throwerror(vm, "Failed to retrieve argument 1 as string");
	}

	CCStr roleID = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 3, &roleID))) {
		return sq_throwerror(vm, "Failed to retrieve argument 2 as string");
	}

	try {
		std::string s_serverID = std::string(serverID);

		auto rolesIndex = session->LatestCopy_Servers.find(std::string(serverID));

		if (rolesIndex == session->LatestCopy_Servers.end()) {
			sq_pushnull(vm);
			return 1;
		}

		auto &roles = (rolesIndex->second).Roles;
		bool found = false;
		CCStr role_name = nullptr;

		for (const auto &role : roles) {
			if (role.second.ID == std::string(roleID)) {
				found = true;
				role_name = role.second.Name.c_str();
				sq_pushstring(vm, role_name, -1);
				break;
			}
		}

		if (!found) {
			return sq_throwerror(vm, "Invalid role ID");
		}
	}
	catch (...) {
		OutputError("An Error has occured at [CSession] function => [RoleName]");
	}

	return 1;
}

// ------------------------------------------------------------------------------------------------
SQInteger CSession::EditChannel(HSQUIRRELVM vm) {
	const int top = sq_gettop(vm);

	if (top <= 1) {
		return sq_throwerror(vm, "Missing the channel ID value");
	} else if (top <= 2) {
		return sq_throwerror(vm, "Missing the channel name value");
	} else if (top <= 3) {
		return sq_throwerror(vm, "Missing the channel topic value");
	}

	CSession *session = nullptr;

	try {
		session = Sqrat::Var<CSession *>(vm, 1).value;
	}
	catch (const Sqrat::Exception &e) {
		return sq_throwerror(vm, e.what());
	}

	if (!session) {
		return sq_throwerror(vm, "Invalid session instance");
	} else if (!session->client) {
		return sq_throwerror(vm, "Invalid Discord client");
	} else if (!session->isConnected) {
		return sq_throwerror(vm, "Session is not connected");
	}

	CCStr channelID = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 2, &channelID))) {
		return sq_throwerror(vm, "Failed to retrieve argument 1 as string");
	}

	CCStr name = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 3, &name))) {
		return sq_throwerror(vm, "Failed to retrieve argument 2 as string");
	}

	CCStr topic = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 4, &topic))) {
		return sq_throwerror(vm, "Failed to retrieve argument 3 as string");
	}

	try {
		auto response = session->client->editChannel(std::string(channelID), std::string(name), std::string(topic),
													 SleepyDiscord::Async);
	}
	catch (...) {
		OutputError("An Error has occured at [CSession] function => [EditChannel]");
	}

	return 0;
}

// ------------------------------------------------------------------------------------------------
SQInteger CSession::SetActivity(HSQUIRRELVM vm) {
	const int top = sq_gettop(vm);

	if (top <= 1) {
		return sq_throwerror(vm, "Missing the activity value");
	}

	CSession *session = nullptr;

	try {
		session = Sqrat::Var<CSession *>(vm, 1).value;
	}
	catch (const Sqrat::Exception &e) {
		return sq_throwerror(vm, e.what());
	}

	if (!session) {
		return sq_throwerror(vm, "Invalid session instance");
	} else if (!session->client) {
		return sq_throwerror(vm, "Invalid Discord client");
	} else if (!session->isConnected) {
		return sq_throwerror(vm, "Session is not connected");
	}

	CCStr activity = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 2, &activity))) {
		return sq_throwerror(vm, "Failed to retrieve argument 1 as string");
	}

	try {
		session->client->updateStatus(std::string(activity));
	}
	catch (...) {
		OutputError("An Error has occured at [CSession] function => [SetActivity]");
	}

	return 0;
}

// ------------------------------------------------------------------------------------------------
void CSession::Disconnect() {
	try {
		// Update events last time
		Update();

		std::lock_guard<std::mutex> lock(m_Guard);

		if (client != nullptr) {
			client->quit();

			if (sleepyThread != nullptr) {
				sleepyThread->join();
				delete sleepyThread;
				sleepyThread = nullptr;
			}

			isConnected = false;
			isConnecting = false;

			delete client;
			client = nullptr;
		}
	}
	catch (...) {
		OutputError("An Error has occured at [CSession] function => [Disconnect]");
	}
}

// ------------------------------------------------------------------------------------------------
void CSession::Destroy() {

	// Disconnect the session
	Disconnect();

	delete s_EventHandler;
	s_EventHandler = nullptr;
}

// ------------------------------------------------------------------------------------------------
CSession::~CSession() {
	Destroy();

	// Attempt to find our self in the session pool
	auto itr = std::find(s_Sessions.begin(), s_Sessions.end(), this);
	// Are we in the pool?
	if (itr != s_Sessions.end()) {
		s_Sessions.erase(itr); /* Remove our self from the pool. */
	}
	// Is there a single session and that's us?
	if (s_Session == this) {
		s_Session = nullptr;
	}
}

// ------------------------------------------------------------------------------------------------
void CSession::Terminate() {
	// Do we only have one Discord session?
	if (s_Session) {
		s_Session->Destroy(); /* This should do the job. */
	}
		// Do we have multiple sessions?
	else if (!s_Sessions.empty()) {
		for (auto &session : s_Sessions) {
			session->Destroy();
		}
	}
}

// ------------------------------------------------------------------------------------------------
Object CSession::GetGuild(const std::string &serverID) {
	auto serverIndex = LatestCopy_Servers.find(serverID);

	if (serverIndex == LatestCopy_Servers.end()) {
		return Object{};
	}

	return Object(serverIndex->second, SqVM());
}

// ------------------------------------------------------------------------------------------------
Object CSession::GetOtherChannel(const std::string &channelID) {
	auto channelIndex = LatestCopy_OtherChannels.find(channelID);

	if (channelIndex == LatestCopy_OtherChannels.end()) {
		return Object{};
	}

	return Object(channelIndex->second, SqVM());
}

// ------------------------------------------------------------------------------------------------
void CSession::DRegister_CSession(Sqrat::Table &discordcn) {
	using namespace Sqrat;

	discordcn.Bind("CSession",
				   Class<CSession, NoCopy<CSession> >(discordcn.GetVM(), "CSession")

						   .Prop("ConnID", &CSession::GetConnID)
						   .Prop("ErrorEventEnabled", &CSession::GetErrorEventEnabled, &CSession::SetErrorEventEnabled)
						   .Prop("InternalCacheEnabled", &CSession::GetInternalCacheEnabled,
								 &CSession::SetInternalCacheEnabled)

						   .Func("Disconnect", &CSession::Disconnect)
						   .Func("GetGuild", &CSession::GetGuild)
						   .Func("GetOtherChannel", &CSession::GetOtherChannel)

						   .SquirrelFunc("Connect", &CSession::Connect)
						   .SquirrelFunc("Message", &CSession::Message)
						   .SquirrelFunc("MessageEmbed", &CSession::MessageEmbed)
						   .SquirrelFunc("GetRoleName", &CSession::GetRoleName)
						   .SquirrelFunc("EditChannel", &CSession::EditChannel)
						   .SquirrelFunc("SetActivity", &CSession::SetActivity)
	);
}
} // Namespace - SqDiscord
