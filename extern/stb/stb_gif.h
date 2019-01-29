/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** extern / stb_gif.h
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

typedef struct gif_result
{
	int delay;
	unsigned char *data;
	struct gif_result *next;
} gif_result_t;

gif_result_t *stbi_gif_load(char const *filename, int *x, int *y, int *frames);

#ifdef __cplusplus
}
#endif