/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** GUI / Env.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace GUI {
	namespace Env {}
}

////////////////////////////////////////////////////////////////////////////////

#include "Widget.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{
	namespace Env
	{
		extern bool foundTarget;
		extern Widget *target;
		extern Widget *modal;
	}
}