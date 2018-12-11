/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** extern / stb_gif.h
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

extern "C" {

unsigned char *stbi_gif_load(char const *filename, int *x, int *y, int *frames);

}

////////////////////////////////////////////////////////////////////////////////

// #include <list>
// #include <string>

////////////////////////////////////////////////////////////////////////////////

// class GIFLoader
// {
// public:

// private:
// 	GIFLoader();
// 	~GIFLoader();

// public:
// 	static bool loadFromFile(const std::string &filename, std::list<GIF::Frame *> &frames, unsigned &width, unsigned &height);
// };