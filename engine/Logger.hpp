/*
** EPITECH PROJECT, 2019
** G13
** File description:
** Logger.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class Logger;

////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "tinyformat/tinyformat.hpp"

////////////////////////////////////////////////////////////////////////////////

class Logger
{
public:
	enum Level
	{
		Trace,
		Debug,
		Info,
		Warn,
		Error,
		Fatal
	};

public:
	static Level level() { return s_level; }
	static void setLevel(Level level) { s_level = level; }
	static void useColors(bool useColors) { s_useColors = useColors; }

	static std::ostream &log(Level level);
	static std::ostream &trace() { return log(Trace); }
	static std::ostream &debug() { return log(Debug); }
	static std::ostream &info() { return log(Info); }
	static std::ostream &warn() { return log(Warn); }
	static std::ostream &error() { return log(Error); }
	static std::ostream &fatal() { return log(Fatal); }

	template <typename... Args> static void log(Level level, const char *fmt, const Args&... args) { log(level) << tfm::format(fmt, args...) << std::endl; }
	template <typename... Args> static void trace(const char *fmt, const Args&... args) { log(Trace, fmt, args...); }
	template <typename... Args> static void debug(const char *fmt, const Args&... args) { log(Debug, fmt, args...); }
	template <typename... Args> static void info(const char *fmt, const Args&... args) { log(Info, fmt, args...); }
	template <typename... Args> static void warn(const char *fmt, const Args&... args) { log(Warn, fmt, args...); }
	template <typename... Args> static void error(const char *fmt, const Args&... args) { log(Error, fmt, args...); }
	template <typename... Args> static void fatal(const char *fmt, const Args&... args) { log(Fatal, fmt, args...); }

private:
	static const char *levelString(Level level);

private:
	static Level s_level;
	static bool s_useColors;
};

////////////////////////////////////////////////////////////////////////////////

#define LogTrace(FMT, ...)	Logger::trace("%s:%d: %s: " FMT, __FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__);
#define LogDebug(FMT, ...)	Logger::debug("%s:%d: %s: " FMT, __FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__);
#define LogInfo(FMT, ...)	Logger::info("%s:%d: %s: " FMT, __FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__);
#define LogWarn(FMT, ...)	Logger::warn("%s:%d: %s: " FMT, __FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__);
#define LogError(FMT, ...)	Logger::error("%s:%d: %s: " FMT, __FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__);
#define LogFatal(FMT, ...)	Logger::fatal("%s:%d: %s: " FMT, __FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__);