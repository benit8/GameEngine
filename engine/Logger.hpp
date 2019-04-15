/*
** EPITECH PROJECT, 2019
** GameEngine
** File description:
** Logger.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class Logger;

////////////////////////////////////////////////////////////////////////////////

#include <iostream>

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

private:
	static const char *levelString(Level level);

private:
	static Level s_level;
	static bool s_useColors;
};