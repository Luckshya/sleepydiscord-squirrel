#include "CallbackHandler.h"

// ------------------------------------------------------------------------------------------------
#include "sqrat.h"
#include "main.h"

// ------------------------------------------------------------------------------------------------
using namespace Sqrat;

// ------------------------------------------------------------------------------------------------
namespace SqDiscord
{
// ------------------------------------------------------------------------------------------------
void Event_onReady(CSession * session)
{
	HSQUIRRELVM vm = DefaultVM::Get();

	Function callback = RootTable(vm).GetFunction("onDiscord_Ready");

	if (callback.IsNull())
	{
		callback.Release();
		return;
	}

	try
	{
		callback.Execute(session);
	}
	catch (Sqrat::Exception& e)
	{
		std::ostringstream error;
		error << "Discord event [READY] => Squirrel error [" << e.what() << "]";

		OutputErr(error.str().c_str());
	}
	catch (const std::exception& e)
	{
		std::ostringstream error;
		error << "Discord event [READY] => Program error [" << e.what() << "]";

		OutputErr(error.str().c_str());
	}
	catch (...)
	{
		OutputErr("Discord event [READY] => Unknown error");
	}

	callback.Release();
}

// ------------------------------------------------------------------------------------------------
void Event_onMessage(CSession * session, CCStr channelID, CCStr author, CCStr authorNick, CCStr authorID, const std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>>& roles, CCStr message)
{
	HSQUIRRELVM vm = DefaultVM::Get();

	Function callback = RootTable(vm).GetFunction("onDiscord_Message");

	if (callback.IsNull())
	{
		callback.Release();
		return;
	}

	const int top = sq_gettop(vm);

	try
	{
		sq_pushobject(vm, callback.GetFunc());
		sq_pushobject(vm, callback.GetEnv());

		PushVar(vm, session);
		sq_pushstring(vm, channelID, -1);
		sq_pushstring(vm, author, -1);
		sq_pushstring(vm, authorNick, -1);
		sq_pushstring(vm, authorID, -1);

		sq_newarray(vm, 0);

		for (auto & role : roles) {
			sq_pushstring(vm, role.string().c_str(), -1);
			sq_arrayappend(vm, -2);
		}

		sq_pushstring(vm, message, -1);

		SQRESULT result = sq_call(vm, 8, 0, SQTrue);

		sq_settop(vm, top);

		if (SQ_FAILED(result))
		{
			throw Exception(LastErrorString(vm));
		}
	}
	catch (Sqrat::Exception& e)
	{
		std::ostringstream error;
		error << "Discord event [MESSAGE] => Squirrel error [" << e.what() << "]";

		OutputErr(error.str().c_str());
	}
	catch (const std::exception& e)
	{
		std::ostringstream error;
		error << "Discord event [MESSAGE] => Program error [" << e.what() << "]";

		OutputErr(error.str().c_str());
	}
	catch (...)
	{
		OutputErr("Discord event [MESSAGE] => Unknown error");
	}

	callback.Release();
}
} //Namespace - SqDiscord
