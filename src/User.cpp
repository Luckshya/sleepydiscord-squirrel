#include "User.h"

// ------------------------------------------------------------------------------------------------
namespace SqDiscord {

// ------------------------------------------------------------------------------------------------
User::User(SleepyDiscord::User &user) {
	ID = user.ID;
	Username = user.username;
	Discriminator = user.discriminator;
	isBot = user.bot;
	Mfa_enabled = user.mfa_enabled;
	Verified = user.verified;
	Email = user.email;
}

// ------------------------------------------------------------------------------------------------
std::string User::GetID() const {
	return ID;
}

// ------------------------------------------------------------------------------------------------
std::string User::GetUsername() const {
	return Username;
}

// ------------------------------------------------------------------------------------------------
std::string User::GetDiscriminator() const {
	return Discriminator;
}

// ------------------------------------------------------------------------------------------------
bool User::IsBot() const {
	return isBot;
}

// ------------------------------------------------------------------------------------------------
bool User::IsMfaEnabled() const {
	return Mfa_enabled;
}

// ------------------------------------------------------------------------------------------------
bool User::IsVerified() const {
	return Verified;
}

// ------------------------------------------------------------------------------------------------
std::string User::GetEmail() const {
	return Email;
}

// ------------------------------------------------------------------------------------------------
void User::Register_User(Table &table) {
	table.Bind("User",
			   Class<User>(table.GetVM(), "User")

					   .Prop("ID", &User::GetID)
					   .Prop("Username", &User::GetUsername)
					   .Prop("Discriminator", &User::GetDiscriminator)
					   .Prop("IsBot", &User::IsBot)
					   .Prop("Mfa_enabled", &User::IsMfaEnabled)
					   .Prop("Verified", &User::IsVerified)
					   .Prop("Email", &User::GetEmail)
	);
}
} //Namespace:: SqDiscord