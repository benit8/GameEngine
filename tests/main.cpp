/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** tests / main.cpp
*/

#include "Application.hpp"
#include "States/Test.hpp"

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	Application *app = Application::instance();
	app->name("Engine");
	app->args(argc, argv);
	app->pushState<States::Test>();
	app->window().setMode(Window::Windowed, {1280, 720});

	return app->run();
}