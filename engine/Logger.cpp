/*
** EPITECH PROJECT, 2019
** GameEngine
** File description:
** Logger.cpp
*/

#include "Logger.hpp"

#include <sys/time.h>

////////////////////////////////////////////////////////////////////////////////

Logger::Level Logger::s_level = Logger::Level::Trace;
bool Logger::s_useColors = true;

////////////////////////////////////////////////////////////////////////////////

std::ostream &Logger::log(Logger::Level level)
{
	static std::ostream nullstream(nullptr);
	if (level < s_level) {
		return nullstream;
	}

	struct timeval tv;
	gettimeofday(&tv, NULL);
	int millisec = tv.tv_usec / 1000.0;

	struct tm *lt = localtime(&tv.tv_sec);
	char tbuf[16] = {0};
	int n = strftime(tbuf, sizeof(tbuf), "%H:%M:%S", lt);
	snprintf(tbuf + n, sizeof(tbuf) - n - 1, ".%03d", millisec);

	return std::cout << tbuf << " " << levelString(level) << " " << std::dec;
}

const char *Logger::levelString(Logger::Level level)
{
	if (s_useColors) {
		switch (level) {
			case Logger::Level::Trace: return "\x1b[90mTRACE\x1b[0m";
			case Logger::Level::Debug: return "\x1b[35mDEBUG\x1b[0m";
			case Logger::Level::Info:  return "\x1b[32mINFO\x1b[0m ";
			case Logger::Level::Warn:  return "\x1b[33mWARN\x1b[0m ";
			case Logger::Level::Error: return "\x1b[31mERROR\x1b[0m";
			case Logger::Level::Fatal: return "\x1b[31;1mFATAL\x1b[0m";
		}
	}
	else {
		switch (level) {
			case Logger::Level::Trace: return "TRACE";
			case Logger::Level::Debug: return "DEBUG";
			case Logger::Level::Info:  return "INFO ";
			case Logger::Level::Warn:  return "WARN ";
			case Logger::Level::Error: return "ERROR";
			case Logger::Level::Fatal: return "FATAL";
		}
	}

	return "?????";
}