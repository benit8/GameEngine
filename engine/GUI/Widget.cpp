/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** GUI / Widget.cpp
*/

#include "Widget.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////

Widget::Widget(const std::string &id)
: m_id(id)
{
	m_eventDispatcher.onMouseMove(BIND2(Widget::callback_mouseMove));
	m_eventDispatcher.onMouseDown(BIND1(Widget::callback_mouseDown), sf::Mouse::Left);
	m_eventDispatcher.onMouseUp(BIND1(Widget::callback_mouseUp), sf::Mouse::Left);
	m_eventDispatcher.onText(BIND1(Widget::callback_text));
}

Widget::Widget(const std::string &id, Mode mode)
: Widget(id)
{
	setMode(mode);
}

Widget::~Widget()
{
}

////////////////////////////////////////////////////////////////////////////////

void Widget::handleEvent(const sf::Event &e)
{
	for (auto &child : getChildren())
		child->handleEvent(e);

	m_eventDispatcher.dispatchEvent(e);
}

void Widget::doUpdate(const sf::Time &delta)
{
	update(delta);
	for (auto &c : getChildren())
		c->doUpdate(delta);
}

void Widget::doRender(sf::RenderTarget &rt)
{
	sf::Vector2f offset = getParentOffset();
	m_zone.move(offset);
	render(rt);
	m_zone.move(-offset);

	for (auto &c : getChildren())
		c->doRender(rt);
}

////////////////////////////////////////////////////////////////////////////////

void Widget::focus()
{
	if (isTargeted())
		return;

	if (Env::target)
		Env::target->unfocus();
	Env::target = this;
	onFocusIn.emit();
}

void Widget::unfocus()
{
	if (isClicked()) {
		onRelease.emit({0, 0});
		m_state &= ~State::Clicked;
	}
	Env::target = nullptr;
	onFocusOut.emit();
}


bool Widget::isMouseHover(sf::Vector2i mouse)
{
	return isMouseHover(sf::Vector2f(mouse.x, mouse.y));
}

bool Widget::isMouseHover(sf::Vector2f mouse)
{
	sf::FloatRect rect(getPosition(), getSize());
	sf::Vector2f parentOffset = getParentOffset();

	rect.left += parentOffset.x;
	rect.top += parentOffset.y;
	return rect.contains(mouse);
}

sf::Vector2f Widget::getParentOffset()
{
	auto w = dynamic_cast<Widget *>(m_parent);
	return w ? w->getParentOffset() + w->getPosition() : sf::Vector2f();
}

void Widget::setParent(Parent *parent)
{
	m_parent = parent;
}

////////////////////////////////////////////////////////////////////////////////

void Widget::callback_mouseMove(sf::Vector2i pos, sf::Vector2i offset)
{
	if (!isHoverable())
		return;

	if (isDragged()) {
		move(offset.x, offset.y);
		onDrag.emit(pos, offset);
		return;
	}

	bool in = isMouseHover(pos);
	if (in && isClicked() && isDraggable()) {
		onDragBegin.emit(pos);
		m_state |= State::Dragged;
	}
	else if (!in && isHovered()) {
		onHoverOut.emit(pos);
		m_state &= ~State::Hovered;
	}
	else if (in && !isHovered()) {
		onHoverIn.emit(pos);
		m_state |= State::Hovered;
	}
	else if (!in && !isHovered() && isClicked()) {
		onRelease.emit(pos);
		m_state &= ~State::Clicked;
	}
}

void Widget::callback_mouseDown(sf::Vector2i pos)
{
	if (!isClickable())
		return;

	if (isHovered()) {
		onClick.emit(pos);
		m_state |= State::Clicked;

		if (!Env::foundTarget) {
			focus();
			Env::foundTarget = true;
		}
	}
}

void Widget::callback_mouseUp(sf::Vector2i pos)
{
	if (!isClickable())
		return;

	if (isClicked()) {
		if (isDragged()) {
			onDragEnd.emit(pos);
			m_state &= ~State::Dragged;
		}
		onRelease.emit(pos);
		m_state &= ~State::Clicked;
	}
}

void Widget::callback_text(unsigned unicode)
{
	if (Env::target == this)
		onTextInput.emit(unicode);
}

////////////////////////////////////////////////////////////////////////////////

}