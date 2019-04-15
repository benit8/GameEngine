/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** FontLoader.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class FontLoader;

////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <SFML/Graphics/Font.hpp>

////////////////////////////////////////////////////////////////////////////////

class FontLoader
{
public:
	struct FontInfo
	{
		FontInfo(std::string _path, std::string _name, std::string _style)
		: path(_path)
		, name(_name)
		, style(_style)
		{}

		std::string path, name, style;
	};

private:
	FontLoader();
	~FontLoader();

public:
	static sf::Font getDefault();
	static bool loadFromSystem(sf::Font &font, const std::string &name);

private:
	static bool searchFonts();

private:
	static bool s_systemFontsLoaded;
	static std::vector<FontInfo> s_systemFonts;
};