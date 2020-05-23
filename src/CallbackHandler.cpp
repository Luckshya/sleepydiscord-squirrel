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
void Event_onMessage(CSession * session, CString channelID, CString author, CString authorNick, CString authorID, s_Roles roles, CString message)
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
		sq_pushstring(vm, channelID.c_str(), -1);
		sq_pushstring(vm, author.c_str(), -1);
		sq_pushstring(vm, authorNick.c_str(), -1);
		sq_pushstring(vm, authorID.c_str(), -1);

		sq_newarray(vm, 0);

		for (auto & role : roles) {
			sq_pushstring(vm, role.string().c_str(), -1);
			sq_arrayappend(vm, -2);
		}

		sq_pushstring(vm, message.c_str(), -1);

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

// ------------------------------------------------------------------------------------------------
void Event_onError(CSession * session, int errorCode, const std::string& errorMessage)
{
    HSQUIRRELVM vm = DefaultVM::Get();

    Function callback = RootTable(vm).GetFunction("onDiscord_Error");

    if (callback.IsNull())
    {
        callback.Release();
        return;
    }

    try
    {
        callback.Execute(session, errorCode, errorMessage);
    }
    catch (Sqrat::Exception& e)
    {
        std::ostringstream error;
        error << "Discord event [ERROR] => Squirrel error [" << e.what() << "]";

        OutputErr(error.str().c_str());
    }
    catch (const std::exception& e)
    {
        std::ostringstream error;
        error << "Discord event [ERROR] => Program error [" << e.what() << "]";

        OutputErr(error.str().c_str());
    }
    catch (...)
    {
        OutputErr("Discord event [ERROR] => Unknown error");
    }

    callback.Release();
}

// ------------------------------------------------------------------------------------------------
void Event_onDisconnect(CSession * session)
{
	HSQUIRRELVM vm = DefaultVM::Get();

	Function callback = RootTable(vm).GetFunction("onDiscord_Disconnect");

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
		error << "Discord event [DISCONNECT] => Squirrel error [" << e.what() << "]";

		OutputErr(error.str().c_str());
	}
	catch (const std::exception& e)
	{
		std::ostringstream error;
		error << "Discord event [DISCONNECT] => Program error [" << e.what() << "]";

		OutputErr(error.str().c_str());
	}
	catch (...)
	{
		OutputErr("Discord event [DISCONNECT] => Unknown error");
	}

	callback.Release();
}

// ------------------------------------------------------------------------------------------------
void Event_onQuit(CSession * session)
{
	HSQUIRRELVM vm = DefaultVM::Get();

	Function callback = RootTable(vm).GetFunction("onDiscord_Quit");

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
		error << "Discord event [QUIT] => Squirrel error [" << e.what() << "]";

		OutputErr(error.str().c_str());
	}
	catch (const std::exception& e)
	{
		std::ostringstream error;
		error << "Discord event [QUIT] => Program error [" << e.what() << "]";

		OutputErr(error.str().c_str());
	}
	catch (...)
	{
		OutputErr("Discord event [QUIT] => Unknown error");
	}

	callback.Release();
}
} //Namespace - SqDiscord
