#include "Role.h"

// ------------------------------------------------------------------------------------------------
namespace SqDiscord {

// ------------------------------------------------------------------------------------------------
Role::Role(SleepyDiscord::Role &role) {
	ID = role.ID;
	Name = role.name;
	Color = role.color;
	Hoist = role.hoist;
	Position = role.position;
}


// ------------------------------------------------------------------------------------------------
std::string Role::GetID() const {
	return ID;
}

// ------------------------------------------------------------------------------------------------
std::string Role::GetName() const {
	return Name;
}


// ------------------------------------------------------------------------------------------------
int Role::GetColor() const {
	return Color;
}

// ------------------------------------------------------------------------------------------------
bool Role::IsHoist() const {
	return Hoist;
}


// ------------------------------------------------------------------------------------------------
int Role::GetPosition() const {
	return Position;
}

// ------------------------------------------------------------------------------------------------
void Role::Register_Role(Table &table) {
	table.Bind("Role",
			   Class<Role>(table.GetVM(), "Role")

					   .Prop("ID", &Role::GetID)
					   .Prop("Name", &Role::GetName)
					   .Prop("Color", &Role::GetColor)
					   .Prop("Hoist", &Role::IsHoist)
					   .Prop("Position", &Role::GetPosition)
	);
}
} // Namespace:: SqDiscord