/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** tests / main.cpp
*/

#include "Application.hpp"
#include "States/Menu.hpp"

////////////////////////////////////////////////////////////////////////////////

int main(/*int argc, char **argv*/)
{
	Application *app = Application::instance();
	app->name("Engine");
	app->pushState<States::Menu>();

	return app->run();
}