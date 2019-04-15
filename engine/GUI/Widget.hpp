/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** GUI / Widget.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace GUI {
	class Widget;
}

////////////////////////////////////////////////////////////////////////////////

#include "Parent.hpp"
#include "Env.hpp"
#include "../EventDispatcher.hpp"
#include "../Utils/Signal.hpp"

#include <list>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class Widget : public Parent, public std::enable_shared_from_this<Widget>
{
	friend class Root;
	friend class Parent;

public:
	enum State {
		Normal	= (1 << 0),
		Hovered	= (1 << 1),
		Clicked	= (1 << 2),
		Dragged	= (1 << 3)
	};

	enum Mode {
		Visible,
		Hoverable,
		Clickable,
		Draggable
	};

public:
	Widget(const std::string &id = "");
	Widget(const std::string &id, Mode mode);
	virtual ~Widget();

public:
	void handleEvent(const sf::Event &e);
	void doUpdate(const sf::Time &delta);
	void doRender(sf::RenderTarget &rt);

protected:
	virtual void update(const sf::Time &) {}
	virtual void render(sf::RenderTarget &) {}

public:
	void focus();
	void unfocus();

	/// State / Mode
	bool isTargeted() const { return this == Env::target; }
	bool isHovered() const { return m_state & State::Hovered; }
	bool isClicked() const { return m_state & State::Clicked; }
	bool isDragged() const { return m_state & State::Dragged; }
	bool isHoverable() const { return m_mode >= Mode::Hoverable; }
	bool isClickable() const { return m_mode >= Mode::Clickable; }
	bool isDraggable() const { return m_mode >= Mode::Draggable; }
	void setMode(Mode mode) { m_mode = mode; }

	/// Inheritence
	Root *getRoot() override { return m_parent ? m_parent->getRoot() : nullptr; }
	const Root *getRoot() const override { return m_parent ? m_parent->getRoot() : nullptr; }
	Parent *getParent() const { return m_parent; }

	void setId(const std::string &id) { m_id = id; }
	const std::string &getId() const override { return m_id; }

	/// Positions
	float left() const { return getPosition().x; }
	float top() const { return getPosition().y; }
	void left(float left) { setPosition(left, top()); }
	void top(float top) { setPosition(left(), top); }
	void move(float offsetX, float offsetY) { move(sf::Vector2f(offsetX, offsetY)); }
	void move(const sf::Vector2f &offset) { setPosition(getPosition() + offset); }
	void setPosition(float offsetX, float offsetY) { setPosition(sf::Vector2f(offsetX, offsetY)); }
	virtual void setPosition(const sf::Vector2f &position) { m_zone.setPosition(position); update(sf::Time::Zero); }
	virtual const sf::Vector2f &getPosition() const { return m_zone.getPosition(); }
	sf::Vector2f getGlobalPosition() { return getPosition() + getParentOffset(); }

	/// Sizes
	float width() const { return getSize().x; }
	float height() const { return getSize().y; }
	void width(float width) { setSize(width, height()); }
	void height(float height) { setSize(width(), height); }
	void setSize(float width, float height) { setSize(sf::Vector2f(width, height)); }
	virtual void setSize(const sf::Vector2f &size) { m_zone.setSize(size); update(sf::Time::Zero); }
	virtual const sf::Vector2f &getSize() const { return m_zone.getSize(); }

public:
	Signal<sf::Vector2i> onHoverIn;
	Signal<sf::Vector2i> onHoverOut;
	Signal<sf::Vector2i> onClick;
	Signal<sf::Vector2i> onRelease;
	Signal<sf::Vector2i, sf::Vector2i> onDrag;
	Signal<sf::Vector2i> ParentragBegin;
	Signal<sf::Vector2i> onDragBegin;
	Signal<sf::Vector2i> onDragEnd;
	Signal<unsigned> onTextInput;
	Signal<> onFocusIn;
	Signal<> onFocusOut;

private:
	bool isMouseHover(sf::Vector2i mouse);
	bool isMouseHover(sf::Vector2f mouse);
	sf::Vector2f getParentOffset();
	void setParent(Parent *parent);

private:
	void callback_mouseMove(sf::Vector2i pos, sf::Vector2i offset);
	void callback_mouseDown(sf::Vector2i pos);
	void callback_mouseUp(sf::Vector2i pos);
	void callback_text(unsigned unicode);

protected:
	Parent *m_parent = nullptr;
	std::string m_id = "";
	int m_state = Normal;
	int m_mode = Visible;
	sf::RectangleShape m_zone;
	EventDispatcher m_eventDispatcher;
};

}