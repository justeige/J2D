#define _CRT_SECURE_NO_WARNINGS

#include "Logger.h"
#include <iostream>
#include <chrono>
#include <ctime>

std::vector<Log_Entry> Logger::messages;

std::string current_date_time_to_string()
{
	const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string output(30, '\0');
	std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));
	return output;
}

void Logger::err(const std::string& msg)
{
	Log_Entry log_entry{};
	log_entry.type = LOG_ERROR;
	log_entry.text = "ERR: [" + current_date_time_to_string() + "] " + msg;

	std::cerr << log_entry.text << '\n';

	messages.push_back(log_entry);
}

void Logger::log(const std::string& msg)
{
	Log_Entry log_entry{};
	log_entry.type = LOG_INFO;
	log_entry.text = "LOG: [" + current_date_time_to_string() + "] " + msg;

	std::cerr << log_entry.text << '\n';

	messages.push_back(log_entry);
}
