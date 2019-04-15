/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** GUI / Modal.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace GUI {
	class Modal;
}

////////////////////////////////////////////////////////////////////////////////

#include "Widget.hpp"
#include "Background.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class Modal : public Widget
{
public:
	Modal();
	virtual ~Modal();

public:
	virtual void draw(sf::RenderTarget &rt) override;
	virtual void updatePositions(sf::Vector2u size);

	virtual void open();
	virtual void close();

	bool isOpen() const { return m_opened; }
	void deleteOnClose(bool d = true) { m_deleteOnClose = d; }

private:
	Widget *m_previousModal = nullptr;
	bool m_opened = false;
	bool m_deleteOnClose = false;
	Background m_back;
};

}