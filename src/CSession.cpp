// ------------------------------------------------------------------------------------------------
#include "CallbackHandler.h"
#include "main.h"
#include "DEmbed.h"
#include "CDiscord.h"

// ------------------------------------------------------------------------------------------------
namespace SqDiscord
{
// variable to hold in case on one connection only
CSession * s_Session = nullptr;

// container to hold connections
std::vector< CSession* > s_Sessions;

// ------------------------------------------------------------------------------------------------
CSession::CSession()
{
	try
	{
		if (!s_Session && s_Sessions.empty())
		{
			s_Session = this;
			connID = 0;
		}
		// Is this the second session instance?
		else if (s_Sessions.empty())
		{
			s_Sessions.push_back(s_Session);
			s_Session = nullptr;
			s_Sessions.push_back(this);
			connID = 1;
		}
		// This is part of multiple session instances
		else
		{
			connID = s_Sessions.size();
			s_Sessions.push_back(this);
		}
	}
	catch (...)
	{
		OutputErr("An Error has occured at [CSession] function => [CSession]");
	}
}

// ------------------------------------------------------------------------------------------------
void CSession::Process()
{
	// Do we only have one Discord session?
	if (s_Session)
	{
		s_Session->Update();
	}
	// Do we have multiple sessions?
	else if (!s_Sessions.empty())
	{
		for (auto & session : s_Sessions)
		{
            session->Update();
		}
	}
}

// ------------------------------------------------------------------------------------------------
void CSession::Update()
{
	if (!client)
	{
		return;
	}

	if (!client->session)
	{
		return;
	}

	if (!isConnected)
	{
		return;
	}

	if(!s_ReadySession.empty())
	{
		std::lock_guard<std::mutex> lockA(m_ReadyGuard);

		for (auto & session : s_ReadySession)
		{
			if (session != nullptr && session->client != nullptr)
			{
				Event_onReady(session);
			}
		}

		s_ReadySession.clear();
	}
	
	if(!s_Messages.empty())
	{
		std::lock_guard<std::mutex> lockB(m_MsgGuard);

		for (auto & message : s_Messages)
		{
			Event_onMessage(this, (message.channelID).c_str(), (message.author).c_str(), (message.authorNick).c_str(), (message.authorID).c_str(), message.roles, (message.message).c_str());
		}

		s_Messages.clear();
	}
}

// ------------------------------------------------------------------------------------------------
SQInteger CSession::Connect(HSQUIRRELVM vm)
{
	const int top = sq_gettop(vm);

	if (top <= 1)
	{
		return sq_throwerror(vm, "Missing the token value");
	}

	CSession * session = nullptr;

	try {
		session = Sqrat::Var< CSession * >(vm, 1).value;
	}
	catch (const Sqrat::Exception& e) {
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
	if (SQ_FAILED(sq_getstring(vm, 2, &token)))
	{
		return sq_throwerror(vm, "Failed to retrieve argument 1 as string");
	}

	try
	{
		// initialize the connection
		session->sleepyThread = new std::thread(&CSession::runSleepy, session, std::string(token));
	}
	catch (...)
	{
		OutputErr("An Error has occured at [CSession] function => [Connect]");
	}

	return 0;
}

// ------------------------------------------------------------------------------------------------
void CSession::runSleepy(std::string token) {
	try
	{
		{
			std::lock_guard<std::mutex> lock(m_Guard);

			isConnecting = true;
			client = new CDiscord(token);

			/*auto intents = {
                SleepyDiscord::Intent::SERVERS,
                SleepyDiscord::Intent::SERVER_MESSAGES,
                SleepyDiscord::Intent::SERVER_MEMBERS,
                SleepyDiscord::Intent::DIRECT_MESSAGES
			};

			client->setIntents(intents);*/
			this->client->session = this;
		}

		client->run();
	}
	catch (...)
	{
		OutputErr("An Error has occured at [CSession] function => [runSleepy]");
	}
}

// ------------------------------------------------------------------------------------------------
unsigned short int CSession::GetConnID()
{
	return connID;
}

// ------------------------------------------------------------------------------------------------
SQInteger CSession::Message(HSQUIRRELVM vm)
{
	const int top = sq_gettop(vm);

	if (top <= 1)
	{
		return sq_throwerror(vm, "Missing the channel ID value");
	}

	else if (top <= 2)
	{
		return sq_throwerror(vm, "Missing the message value");
	}

	CSession * session = nullptr;

	try {
		session = Sqrat::Var< CSession * >(vm, 1).value;
	}
	catch (const Sqrat::Exception& e) {
		return sq_throwerror(vm, e.what());
	}

	if (!session) {
		return sq_throwerror(vm, "Invalid session instance");
	}

	else if (!session->client) {
		return sq_throwerror(vm, "Invalid Discord client");
	}

	else if (!session->isConnected) {
		return sq_throwerror(vm, "Session is not connected");
	}

	CCStr channelID = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 2, &channelID)))
	{
		return sq_throwerror(vm, "Failed to retrieve argument 1 as string");
	}

	CCStr message = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 3, &message)))
	{
		return sq_throwerror(vm, "Failed to retrieve argument 2 as string");
	}

	try
	{
		auto msg = session->client->sendMessage(channelID, message, SleepyDiscord::Async);
	}
	catch (...)
	{
		OutputErr("An Error has occured at [CSession] function => [Message]");
	}

	return 0;
}

// ------------------------------------------------------------------------------------------------
SQInteger CSession::MessageEmbed(HSQUIRRELVM vm)
{
	const int top = sq_gettop(vm);

	if (top <= 1)
	{
		return sq_throwerror(vm, "Missing the channel ID value");
	}

	else if (top <= 2)
	{
		return sq_throwerror(vm, "Missing the content value");
	}

	else if (top <= 3)
	{
		return sq_throwerror(vm, "Missing the Embed value");
	}

	CSession * session = nullptr;

	try {
		session = Sqrat::Var< CSession * >(vm, 1).value;
	}
	catch (const Sqrat::Exception& e) {
		return sq_throwerror(vm, e.what());
	}

	if (!session) {
		return sq_throwerror(vm, "Invalid session instance");
	}

	else if (!session->client) {
		return sq_throwerror(vm, "Invalid Discord client");
	}

	else if (!session->isConnected) {
		return sq_throwerror(vm, "Session is not connected");
	}

	Embed * embed = nullptr;

	try {
		embed = Sqrat::Var< Embed * >(vm, 4).value;
	}
	catch (const Sqrat::Exception& e) {
		return sq_throwerror(vm, e.what());
	}

	if (!embed) {
		return sq_throwerror(vm, "Invalid Embed instance");
	}

	CCStr channelID = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 2, &channelID)))
	{
		return sq_throwerror(vm, "Failed to retrieve argument 1 as string");
	}

	CCStr content = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 3, &content)))
	{
		return sq_throwerror(vm, "Failed to retrieve argument 2 as string");
	}

	try
	{
		auto msg = session->client->sendMessage(channelID, content, *(embed->embed), false, SleepyDiscord::Async);
	}
	catch (...)
	{
		OutputErr("An Error has occured at [CSession] function => [MessageEmbed]");
	}

	return 0;
}

// ------------------------------------------------------------------------------------------------
SQInteger CSession::GetRoleName(HSQUIRRELVM vm)
{
	const int top = sq_gettop(vm);

	if (top <= 1)
	{
		return sq_throwerror(vm, "Missing the server ID value");
	}

	else if (top <= 2)
	{
		return sq_throwerror(vm, "Missing the role ID value");
	}

	CSession * session = nullptr;

	try {
		session = Sqrat::Var< CSession * >(vm, 1).value;
	}
	catch (const Sqrat::Exception& e) {
		return sq_throwerror(vm, e.Message().c_str());
	}

	if (!session) {
		return sq_throwerror(vm, "Invalid session instance");
	}

	else if (!session->client) {
		return sq_throwerror(vm, "Invalid Discord client");
	}

	else if (!session->isConnected) {
		return sq_throwerror(vm, "Session is not connected");
	}

	CCStr serverID = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 2, &serverID)))
	{
		return sq_throwerror(vm, "Failed to retrieve argument 1 as string");
	}

	CCStr roleID = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 3, &roleID)))
	{
		return sq_throwerror(vm, "Failed to retrieve argument 2 as string");
	}

	try {
		std::list<SleepyDiscord::Role> roles = session->client->s_servers.at(std::string(serverID)).roles;

		bool found = false;
		CCStr role_name = nullptr;

		for (const auto & role : roles) {
			if (role.ID.string() == std::string(roleID)) {
				found = true;
				role_name = role.name.c_str();
				sq_pushstring(vm, role_name, -1);
				break;
			}
		}


		if (!found) {
			return sq_throwerror(vm, "Invalid role ID");
		}
	}
	catch (...) {
		OutputErr("An Error has occured at [CSession] function => [RoleName]");
	}

	return 1;
}

// ------------------------------------------------------------------------------------------------
SQInteger CSession::SetActivity(HSQUIRRELVM vm)
{
	const int top = sq_gettop(vm);

	if (top <= 1)
	{
		return sq_throwerror(vm, "Missing the activity value");
	}

	CSession * session = nullptr;

	try {
		session = Sqrat::Var< CSession * >(vm, 1).value;
	}
	catch (const Sqrat::Exception& e) {
		return sq_throwerror(vm, e.what());
	}

	if (!session) {
		return sq_throwerror(vm, "Invalid session instance");
	}

	else if (!session->client) {
		return sq_throwerror(vm, "Invalid Discord client");
	}

	else if (!session->isConnected) {
		return sq_throwerror(vm, "Session is not connected");
	}

	CCStr activity = nullptr;
	if (SQ_FAILED(sq_getstring(vm, 2, &activity)))
	{
		return sq_throwerror(vm, "Failed to retrieve argument 1 as string");
	}

	try {
		session->client->updateStatus(std::string(activity));
	}
	catch (...) {
		OutputErr("An Error has occured at [CSession] function => [SetActivity]");
	}

	return 0;
}

// ------------------------------------------------------------------------------------------------
void CSession::Disconnect()
{
	try
	{
		std::lock_guard<std::mutex> lock(m_Guard);

		if (client != nullptr)
		{
			client->quit();

			if (sleepyThread != nullptr)
			{
				sleepyThread->join();
				delete sleepyThread;
				sleepyThread = nullptr;
			}

			isConnected		= false;
			isConnecting	= false;

			delete client;
			client = nullptr;
		}
	}
	catch(...)
	{
		OutputErr("An Error has occured at [CSession] function => [Disconnect]");
	}
}

// ------------------------------------------------------------------------------------------------
void CSession::Destroy()
{
	{
		std::lock_guard<std::mutex> lock(m_Guard);

		if (!client)
		{
			return;
		}
	}

	// Disconnect the session
	Disconnect();
}

// ------------------------------------------------------------------------------------------------
CSession::~CSession()
{
	Destroy();

	// Attempt to find our self in the session pool
	auto itr = std::find(s_Sessions.begin(), s_Sessions.end(), this);
	// Are we in the pool?
	if (itr != s_Sessions.end())
	{
		s_Sessions.erase(itr); /* Remove our self from the pool. */
	}
	// Is there a single session and that's us?
	if (s_Session == this)
	{
		s_Session = nullptr;
	}
}

// ------------------------------------------------------------------------------------------------
void CSession::Terminate()
{
	// Do we only have one Discord session?
	if (s_Session)
	{
		s_Session->Destroy(); /* This should do the job. */
	}
	// Do we have multiple sessions?
	else if (!s_Sessions.empty())
	{
		for (auto & session : s_Sessions)
		{
            session->Destroy();
		}
	}
}

// ------------------------------------------------------------------------------------------------
void Register_CSession(Sqrat::Table discordcn)
{
	using namespace Sqrat;

	discordcn.Bind("CSession",
		Class< CSession, NoCopy< CSession > >(discordcn.GetVM(), "CSession")

		.Prop("ConnID", &CSession::GetConnID)
		.Func("Disconnect", &CSession::Disconnect)

		.SquirrelFunc("Connect", &CSession::Connect)
		.SquirrelFunc("Message", &CSession::Message)
		.SquirrelFunc("MessageEmbed", &CSession::MessageEmbed)
		.SquirrelFunc("GetRoleName", &CSession::GetRoleName)
		.SquirrelFunc("SetActivity", &CSession::SetActivity)
	);
}
} // Namespace - SqDiscord
