/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** Graphics / GIF.cpp
*/

#include "extern/stb_image.h"
#include "GIF.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace Graphics
{

////////////////////////////////////////////////////////////////////////////////

GIF::GIF()
: m_size(0, 0)
, m_playing(false)
, m_progress(sf::Time::Zero)
, m_nextProgressStep(sf::Time::Zero)
, m_currentFrame(0)
, m_targetUpdate(false)
{
}

GIF::~GIF()
{
	for (auto frame : m_frames)
		delete frame;
}

////////////////////////////////////////////////////////////////////////////////

bool GIF::loadFromFile(const std::string &filename)
{
	int width = 0;
	int height = 0;
	int frames = 0;
	gif_result_t *data = stbi_gif_load(filename.c_str(), &width, &height, &frames);
	if (data == NULL) {
		std::cerr << "GIF loading failed" << std::endl;
		return false;
	}

	m_frames.reserve(frames);
	m_size.x = width;
	m_size.y = height;

	gif_result_t *cur = data;
	while (cur != NULL) {
		m_frames.push_back(new Frame(m_size, cur->data, cur->delay));

		gif_result_t *next = cur->next;
		free(cur->data);
		free(cur);
		cur = next;
	}

	return true;
}


void GIF::play()
{
	if (m_playing)
		return;
	m_playing = true;
	m_progress = sf::Time::Zero;
}

void GIF::stop()
{
	m_playing = false;
}

void GIF::update(const sf::Time &delta)
{
	if (!m_playing)
		return;

	if (m_nextProgressStep == sf::Time::Zero) {
		m_nextProgressStep = m_frames[0]->duration;
	}

	m_progress += delta;
	while (m_progress >= m_nextProgressStep) {
		m_currentFrame++;
		if (m_currentFrame >= m_frames.size())
			m_currentFrame = 0;

		m_targetUpdate = true;
		m_nextProgressStep += m_frames[m_currentFrame]->duration;
	}
}

////////////////////////////////////////////////////////////////////////////////

}