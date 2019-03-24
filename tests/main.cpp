/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** tests / main.cpp
*/

#include "Application.hpp"
#include "States/Test.hpp"

////////////////////////////////////////////////////////////////////////////////

int main(/*int argc, char **argv*/)
{
	Application *app = Application::instance();
	// app->parseOptions(argc, argv);
	app->name("Engine");
	app->pushState<States::Test>();

	return app->run();
}