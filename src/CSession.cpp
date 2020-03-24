// ------------------------------------------------------------------------------------------------
#include "CallbackHandler.h"
#include "main.h"
#include "DEmbed.h"
#include "CDiscord.h"

// ------------------------------------------------------------------------------------------------
namespace SqDiscord
{
// ------------------------------------------------------------------------------------------------
typedef std::vector<CSession*> Sessions;

// variable to hold in case on one connection only
CSession * s_Session = nullptr;

// container to hold connections
std::vector< CSession* > s_Sessions;

// ------------------------------------------------------------------------------------------------
CSession::CSession()
{
	try
	{
		token = NULL;
		client = nullptr;

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
		for (auto itr = s_Sessions.begin(); itr != s_Sessions.end(); ++itr)
		{
			(*itr)->Update();
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

		for (auto itr = s_ReadySession.begin(); itr != s_ReadySession.end(); ++itr)
		{
			if ((*itr) != nullptr && (*itr)->client != nullptr)
			{
				Event_onReady(*itr);
			}
		}

		s_ReadySession.clear();
	}
	
	if(!s_Messages.empty())
	{
		std::lock_guard<std::mutex> lockB(m_MsgGuard);

		for (auto itr = s_Messages.begin(); itr != s_Messages.end(); ++itr)
		{
			Event_onMessage(this, (itr->channelID).c_str(), (itr->author).c_str(), (itr->authorNick).c_str(), (itr->authorID).c_str(), itr->roles, (itr->message).c_str());
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

	CCStr token = NULL;
	if (SQ_FAILED(sq_getstring(vm, 2, &token)))
	{
		return sq_throwerror(vm, "Failed to retrieve argument 1 as string");
	}

	try
	{
		// initialize the connection
		session->client = new CDiscord(token);
		session->isConnecting = true;
		session->token = token;
		session->sleepyThread = new std::thread(&CSession::runSleepy, session);
		session->client->session = session;
	}
	catch (...)
	{
		OutputErr("An Error has occured at [CSession] function => [Connect]");
	}

	return 0;
}

// ------------------------------------------------------------------------------------------------
void CSession::runSleepy() {
	try
	{
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

	CCStr channelID = NULL;
	if (SQ_FAILED(sq_getstring(vm, 2, &channelID)))
	{
		return sq_throwerror(vm, "Failed to retrieve argument 1 as string");
	}

	CCStr message = NULL;
	if (SQ_FAILED(sq_getstring(vm, 3, &message)))
	{
		return sq_throwerror(vm, "Failed to retrieve argument 2 as string");
	}

	try
	{
		auto msg = session->client->sendMessage(channelID, message);
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
		embed = Sqrat::Var< Embed * >(vm, 3).value;
	}
	catch (const Sqrat::Exception& e) {
		return sq_throwerror(vm, e.what());
	}

	if (!embed) {
		return sq_throwerror(vm, "Invalid Embed instance");
	}

	CCStr channelID = NULL;
	if (SQ_FAILED(sq_getstring(vm, 2, &channelID)))
	{
		return sq_throwerror(vm, "Failed to retrieve argument 2 as string");
	}

	try
	{
		auto msg = session->client->sendMessage(channelID, "", *(embed->embed));
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

	CCStr serverID = NULL;
	if (SQ_FAILED(sq_getstring(vm, 2, &serverID)))
	{
		return sq_throwerror(vm, "Failed to retrieve argument 1 as string");
	}

	CCStr roleID = NULL;
	if (SQ_FAILED(sq_getstring(vm, 3, &roleID)))
	{
		return sq_throwerror(vm, "Failed to retrieve argument 2 as string");
	}

	try {
		std::list<SleepyDiscord::Role> roles = session->client->s_servers.at(std::string(serverID)).roles;

		bool found = false;
		CCStr role_name = NULL;

		for (SleepyDiscord::Role role : roles) {
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

	CCStr activity = NULL;
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
		if (isConnected)
		{
			std::lock_guard<std::mutex> lock(m_Guard);
			client->quit();
			isConnected = false;
			isConnecting = false;
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
	if (!client)
	{
		return;
	}

	// Disconnect the session
	Disconnect();
	
	client->session = nullptr;
	delete client;
	client = nullptr;
}

// ------------------------------------------------------------------------------------------------
CSession::~CSession()
{
	Destroy();

	// Attempt to find our self in the session pool
	Sessions::iterator itr = std::find(s_Sessions.begin(), s_Sessions.end(), this);
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
		for (Sessions::iterator itr = s_Sessions.begin(); itr != s_Sessions.end(); ++itr)
		{
			(*itr)->Destroy();
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