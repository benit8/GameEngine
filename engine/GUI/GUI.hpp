/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** GUI.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics/Font.hpp>

#include "../Graphics/FontLoader.hpp"
#include "Env.hpp"
#include "Widget.hpp"
#include "Box.hpp"
#include "Background.hpp"
#include "Button.hpp"
#include "Input.hpp"
#include "Modal.hpp"
#include "MessageBox.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

	template <typename... Args>
	void alert(const std::string &fmt, Args&&... args)
	{
		int n = snprintf(NULL, 0, fmt.c_str(), std::forward<Args>(args)...) + 1;
		char buffer[n];
		snprintf(&buffer[0], n, fmt.c_str(), std::forward<Args>(args)...);

		std::string message(buffer, n - 1);
		MessageBox *msgbox = new MessageBox(message, {MessageBox::Close});
		msgbox->setSuicidal(true);
		msgbox->open();
	}

}