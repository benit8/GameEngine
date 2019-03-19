/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** tests / main.cpp
*/

#include "Application.hpp"
#include "States/Test.hpp"

////////////////////////////////////////////////////////////////////////////////

int main(void)
{
	Application *app = Application::get();
	app->appName("Engine");
	app->window().setMode(Window::Windowed/*, {1280, 720}*/);
	app->pushState<States::Test>();

	return app->run();
}