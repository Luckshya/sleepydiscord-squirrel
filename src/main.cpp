// Main include
#include "Common.hpp"
#include "main.h"
#include "DEmbed.h"
#include "CSession.h"
#include "Constants.h"
#include "Channel.h"
#include "Guild.h"
#include "Role.h"
#include "ServerMember.h"
#include "User.h"
#include "Message.h"

#if defined(WIN32) || defined(_WIN32)
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#endif

// Module imports
#include "SqImports.h"

// Definitions
HSQAPI sq;
HSQUIRRELVM v;

// Global variables (meh)
PluginFuncs *gFuncs;

// ------------------------------------------------------------------------------------------------
using namespace SqDiscord;
using namespace Sqrat;

// ------------------------------------------------------------------------------------------------
uint8_t SqDiscord_OnSquirrelScriptLoad() {
	// See if we have any imports from Squirrel
	size_t size;
	int sqId = gFuncs->FindPlugin("SQHost2");
	// Is there a squirrel host plugin?
	if (sqId < 0) {
		OutputMessage("Unable to locate the host plug-in");
		return 0;
	}
	const void **sqExports = gFuncs->GetPluginExports(sqId, &size);

	// We do!
	if (sqExports != NULL && size > 0) {
		// Cast to a SquirrelImports structure
		SquirrelImports **sqDerefFuncs = (SquirrelImports **) sqExports;

		// Now let's change that to a SquirrelImports pointer
		SquirrelImports *sqFuncs = (SquirrelImports *) (*sqDerefFuncs);

		// Now we get the virtual machine
		if (sqFuncs) {
			// Get a pointer to the VM and API
			sq = *(sqFuncs->GetSquirrelAPI());
			v = *(sqFuncs->GetSquirrelVM());

			ErrorHandling::Enable(true);
			DefaultVM::Set(v);

			Table discordcn(v);
			Table embeds(v);

			CSession::DRegister_CSession(discordcn);
			Channel::Register_Channel(discordcn);
			Guild::Register_Guild(discordcn);
			Role::Register_Role(discordcn);
			ServerMember::Register_ServerMember(discordcn);
			User::Register_User(discordcn);
			Message::Register_Message(discordcn);
			DRegister_Constants(discordcn);

			Register_Embeds(embeds);
			discordcn.Bind("Embed", embeds);
			RootTable(v).Bind("SqDiscord", discordcn);

			RootTable(v).SquirrelFunc("Regex_Match", &Regex_Match);

			return 1;
		}
	} else {
		OutputMessage("Failed to attach to SQHost2.");
	}
	return 0;
}

// ------------------------------------------------------------------------------------------------
uint8_t SqDiscord_OnPluginCommand(uint32_t command_identifier, const char * /*message*/) {
	switch (command_identifier) {
		case 0x7D6E22D8:
			return SqDiscord_OnSquirrelScriptLoad();
		default:
			break;
	}

	return 1;
}

// ------------------------------------------------------------------------------------------------
uint8_t SqDiscord_OnServerInitialise() {
	printf("\n");
	OutputMessage("Loaded Discord Module for VC:MP 0.4 by Luckshya.");

	return 1;
}

// ------------------------------------------------------------------------------------------------
void SqDiscord_OnServerFrame(float) {
	CSession::Process();
}

// ------------------------------------------------------------------------------------------------
void SqDiscord_OnServerShutdown() {
	CSession::Terminate();
}

// ------------------------------------------------------------------------------------------------
EXPORT unsigned int VcmpPluginInit(PluginFuncs *functions, PluginCallbacks *callbacks, PluginInfo *info) {
	// Set our plugin information
	info->pluginVersion = 0x1001; // 1.0.01
	info->apiMajorVersion = PLUGIN_API_MAJOR;
	info->apiMinorVersion = PLUGIN_API_MINOR;
	sprintf(info->name, "%s", "Discord Module for VC:MP");

	// Store functions for later use
	gFuncs = functions;

	// Store callback
	callbacks->OnServerInitialise = SqDiscord_OnServerInitialise;
	callbacks->OnPluginCommand = SqDiscord_OnPluginCommand;
	callbacks->OnServerFrame = SqDiscord_OnServerFrame;
	callbacks->OnServerShutdown = SqDiscord_OnServerShutdown;

	// Done!
	return 1;
}
