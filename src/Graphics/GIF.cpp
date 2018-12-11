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
// , m_frames(0)
, m_playing(false)
, m_progress(sf::Time::Zero)
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
	uint8_t *data = stbi_gif_load(filename.c_str(), &width, &height, &frames);
	if (data == NULL) {
		std::cerr << "GIF loading failed" << std::endl;
		return false;
	}

	std::cout << frames << " frames of " << width << "x" << height << std::endl;

	m_size.x = width;
	m_size.y = height;
	m_frames.reserve(frames);

	uint8_t *d = data;
	for (int i = 0; i < frames; ++i) {
		auto frame = new Frame(m_size);
		frame->image.create(width, height, data);
		d += width * height * 4;

		uint16_t delay = d[0] + (d[1] << 8);
		frame->delay = sf::seconds(delay / 100.f);
		d += 2;

		m_frames.push_back(frame);
	}

	free(data);
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
	m_progress += delta;

	sf::Time p = m_progress;
	for (size_t i = 0; i < m_frames.size(); ) {
		p -= m_frames[i]->delay;

		if (i == m_frames.size() - 1) {
			i = 0;
			continue;
		}
		else if (p <= sf::Time::Zero && m_currentFrame != i) {
			m_currentFrame = i;
			m_targetUpdate = true;
			break;
		}
		++i;
	}
}

////////////////////////////////////////////////////////////////////////////////

}