/*
** EPITECH PROJECT, 2019
** GameEngine
** File description:
** GUI / Parent.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace GUI {
	class Parent;

	class Root;
	class Widget;
}

////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class Parent
{
public:
	virtual ~Parent();

	virtual Root *getRoot() = 0;
	virtual const Root *getRoot() const = 0;
	virtual const std::string &getId() const = 0;

	void addChild(std::shared_ptr<Widget> widget);
	void removeChild(std::shared_ptr<Widget> widget);
	template <typename T, typename... Args>
	std::shared_ptr<T> makeChild(Args&&... args)
	{
		std::shared_ptr<T> child = std::make_shared<T>(std::forward<Args>(args)...);
		addChild(child);
		return child;
	}

	std::vector<std::shared_ptr<Widget>> &getChildren() { return m_children; }
	const std::vector<std::shared_ptr<Widget>> &getChildren() const { return m_children; }
	std::shared_ptr<Widget> getWidget(const std::string &id);
	template <typename T>
	std::shared_ptr<T> getWidgetAs(const std::string &id)
	{
		return std::dynamic_pointer_cast<T>(getWidget(id));
	}

private:
	std::shared_ptr<Widget> searchWidget(const std::string &id);

private:
	std::vector<std::shared_ptr<Widget>> m_children;
};

}