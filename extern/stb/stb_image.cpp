/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** extern / stb_image.cpp
*/

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#define STBI_ONLY_JPEG
#define STBI_ONLY_BMP
#define STBI_ONLY_GIF

#include "stb_image.h"
#include "stb_gif.h"

////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

gif_result_t *stbi_gif_load(char const *filename, int *x, int *y, int *frames)
{
	FILE *f;
	stbi__context s;

	if (!(f = stbi__fopen(filename, "rb"))) {
		stbi__errpuc("can't fopen", "Unable to open file");
		return NULL;
	}

	*frames = 0;
	stbi__start_file(&s, f);

	if (!stbi__gif_test(&s))
	{
		fclose(f);
		return NULL;
	}

	int c = 0;
	stbi__gif gif;
	memset(&gif, 0, sizeof(stbi__gif));
	gif_result_t *head = (gif_result_t*)calloc(1, sizeof(gif_result_t));
	gif_result_t *prev = NULL;
	gif_result_t *curr = head;

	while ((curr->data = stbi__gif_load_next(&s, &gif, &c, 4, NULL)))
	{
		if (curr->data == (unsigned char*)&s)
		{
			curr->data = 0;
			break;
		}
		else
		{
			unsigned char *data = (unsigned char*)calloc(1, gif.w * gif.h * 4);
			memcpy(data, curr->data, gif.w * gif.h * 4);
			curr->data = data;
		}

		if (prev)
			prev->next = curr;
		curr->delay = gif.delay;
		prev = curr;
		curr = (gif_result_t*)calloc(1, sizeof(gif_result_t));
		++(*frames);
	}

	STBI_FREE(gif.out);

	if (*frames > 0)
	{
		*x = gif.w;
		*y = gif.h;
	}

	fclose(f);
	return head;
}

#ifdef __cplusplus
}
#endif