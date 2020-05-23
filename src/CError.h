#pragma once

// ------------------------------------------------------------------------------------------------
#include <string>

// ------------------------------------------------------------------------------------------------
namespace SqDiscord {
// ------------------------------------------------------------------------------------------------
class CError {
public:
	int ErrorCode;
	std::string ErrorMessage;

	CError(int ErrorCode, std::string ErrorMessage) {
		this->ErrorCode = ErrorCode;
		this->ErrorMessage = std::move(ErrorMessage);
	}
};

} // Namespace:: SqDiscord
