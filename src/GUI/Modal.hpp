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
#include "Box.hpp"

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

	bool isOpen();

	void setSuicidal(bool suicidal);
	bool isSuicidal() const;

private:
	Widget *m_previousModal;
	Box m_back;
	bool m_opened;
	bool m_suicidal; // Does it deletes itself upon destruction ?
};

}