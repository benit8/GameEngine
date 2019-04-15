/*
** EPITECH PROJECT, 2019
** GameEngine
** File description:
** GUI / Parent.cpp
*/

#include "Parent.hpp"
#include "Widget.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////

Parent::~Parent()
{
	for (auto &c : m_children)
		c->setParent(nullptr);
}

////////////////////////////////////////////////////////////////////////////////

void Parent::addChild(std::shared_ptr<Widget> widget)
{
	widget->setParent(this);
	m_children.push_back(widget);
}

void Parent::removeChild(std::shared_ptr<Widget> widget)
{
	widget->setParent(nullptr);
	m_children.erase(std::remove_if(m_children.begin(), m_children.end(), [&](auto &c) {
		return c == widget;
	}), m_children.end());
}

std::shared_ptr<Widget> Parent::getWidget(const std::string &id)
{
	if (getId() == id) {
		auto w = dynamic_cast<Widget *>(this);
		return w ? w->shared_from_this() : nullptr;
	}
	return searchWidget(id);
}

////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<Widget> Parent::searchWidget(const std::string &id)
{
	for (auto &c : m_children) {
		if (c->getId() == id)
			return c;
		auto c2 = c->searchWidget(id);
		if (c2)
			return c2;
	}
	return {};
}

////////////////////////////////////////////////////////////////////////////////

}