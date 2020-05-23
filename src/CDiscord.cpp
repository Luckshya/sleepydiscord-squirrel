// ------------------------------------------------------------------------------------------------
#include "CDiscord.h"
#include "main.h"

// ------------------------------------------------------------------------------------------------
#include <list>
#include <mutex>

// ------------------------------------------------------------------------------------------------
using namespace SqDiscord;

// ------------------------------------------------------------------------------------------------
void CDiscord::onServer(SleepyDiscord::Server server) {
	//std::lock_guard<std::mutex> lock(session->m_Guard);
	try {
		s_servers[server.ID.string()] = server;
	}
	catch (...) {
		OutputErr("An Error has occured at [CDiscord] function => [onServer]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onMessage(SleepyDiscord::Message message) {
	//std::lock_guard<std::mutex> lock(session->m_Guard);
	try {
		std::string author_nick;
		SleepyDiscord::Server server;
		std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>> roles;

		bool isDM = false;

		SleepyDiscord::ObjectResponse<SleepyDiscord::Channel> getChannelResponse = this->getChannel(message.channelID);
		if (getChannelResponse.error())
		{
			std::cout << getChannelResponse.text;
			return;
		}

        SleepyDiscord::Channel chan = getChannelResponse;

		if (chan.type == SleepyDiscord::Channel::ChannelType::DM || chan.type == SleepyDiscord::Channel::ChannelType::GROUP_DM) {
			isDM = true;
		}

		if (!isDM) {
			server = s_servers.at(message.serverID.string());
			for (const auto & member : server.members) {
				if (member.user.ID.number() == message.author.ID.number()) {
					roles = member.roles;
					break;
				}
			}

			author_nick = server.findMember(message.author.ID)->nick;
		}

		std::lock_guard<std::mutex> guard(this->session->m_MsgGuard);
		this->session->s_Messages.emplace_back(message.channelID.string(), message.author.username, author_nick, message.author.ID.string(), roles, message.content);
	}
	catch (...) {
		OutputErr("An Error has occured at [CDiscord] function => [onMessage]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onReady(SleepyDiscord::Ready readyData) {
	//std::lock_guard<std::mutex> lock(session->m_Guard);
	try {
		this->session->isConnected = true;
		this->session->isConnecting = false;

		std::lock_guard<std::mutex> guard(this->session->m_ReadyGuard);
		this->session->s_ReadySession.push_back(this->session);
	}
	catch (...) {
		OutputErr("An Error has occured at [CDiscord] function => [onReady]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onEditMember(SleepyDiscord::Snowflake<SleepyDiscord::Server> serverID, SleepyDiscord::User user, std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>> nroles, std::string nnick) {
	//std::lock_guard<std::mutex> lock(session->m_Guard);
	try {
		std::list<SleepyDiscord::ServerMember> & members = s_servers.at(serverID).members;

		for (auto & member : members) {
			if (member.ID.number() == user.ID.number()) {
				member.roles = nroles;
				member.nick = nnick;
				break;
			}
		}
	}
	catch (...) {
		OutputErr("An Error has occured at [CDiscord] function => [onEditMember]");
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onError(SleepyDiscord::ErrorCode errorCode, std::string errorMessage) {
    if(!session->errorEventEnabled) {
		if (errorCode != 0)
			std::cout << "Error " << errorCode << ": " + errorMessage + '\n';
		else
			std::cout << "Error: " + errorMessage + '\n';
	}
	else {
		//std::lock_guard<std::mutex> lock(session->m_Guard);
		try {
			std::lock_guard<std::mutex> guard(this->session->m_ErrorGuard);
			this->session->s_Errors.emplace_back(errorCode, errorMessage);
		}
		catch (...) {
			OutputErr("An Error has occured at [CDiscord] function => [onError]");
		}
	}
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onDisconnect() {
    //std::lock_guard<std::mutex> lock(session->m_Guard);
    try {
        std::lock_guard<std::mutex> guard(this->session->m_DisconnectsGuard);
        this->session->s_Disconnects.emplace_back(session);
    }
    catch (...) {
        OutputErr("An Error has occured at [CDiscord] function => [onDisconnect]");
    }
}

// ------------------------------------------------------------------------------------------------
void CDiscord::onQuit() {
    //std::lock_guard<std::mutex> lock(session->m_Guard);
    try {
        std::lock_guard<std::mutex> guard(this->session->m_QuitsGuard);
        this->session->s_Quits.emplace_back(session);
    }
    catch (...) {
        OutputErr("An Error has occured at [CDiscord] function => [onQuit]");
    }
}
