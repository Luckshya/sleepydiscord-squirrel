#include "Functions.h"

// ------------------------------------------------------------------------------------------------
#include <regex>

// ------------------------------------------------------------------------------------------------
SQInteger Regex_Match(HSQUIRRELVM vm) {
	const SQChar *regex_string;
	const SQChar *value_string;

	if (SQ_FAILED(sq_getstring(vm, 2, &regex_string))) {
		return sq_throwerror(vm, "Unable to retrieve argument 1 as string");
	} else if (SQ_FAILED(sq_getstring(vm, 3, &value_string))) {
		return sq_throwerror(vm, "Unable to retrieve argument 2 as string");
	}

	try {
		std::regex r(regex_string);
		std::string s(value_string);

		std::smatch string_flag;

		bool matches = std::regex_match(s, r);

		sq_pushbool(vm, matches);
	}
	catch (std::regex_error &e) {
		return sq_throwerror(vm, e.what());
	}
	catch (...) {
		return sq_throwerror(vm, "An Error has occured at [Global] function => [Regex_Match]");
	}

	return 1;
}