#pragma once

#include <vector>
#include <string>

enum Log_Type {
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR
};

struct Log_Entry {
	Log_Type type;
	std::string text;
};

class Logger {
public:
	static std::vector<Log_Entry> messages;
	static void err(const std::string& msg);
	static void log(const std::string& msg);
};

