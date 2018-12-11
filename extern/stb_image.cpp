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

extern "C" {

typedef struct gif_result_t {
	int delay;
	unsigned char *data;
	struct gif_result_t *next;
} gif_result;

unsigned char *stbi_gif_load(char const *filename, int *x, int *y, int *frames)
{
	FILE *f;
	stbi__context s;
	unsigned char *result = 0;

	if (!(f = stbi__fopen(filename, "rb")))
		return stbi__errpuc("can't fopen", "Unable to open file");

	stbi__start_file(&s, f);

	if (stbi__gif_test(&s))
	{
		int c = 0;
		stbi__gif g;
		gif_result head;
		gif_result *prev = 0;
		gif_result *gr = &head;

		memset(&g, 0, sizeof(g));
		memset(&head, 0, sizeof(head));

		*frames = 0;

		while ((gr->data = stbi__gif_load_next(&s, &g, &c, 4, prev ? prev->data : NULL)))
		{
			if (gr->data == (unsigned char*)&s)
			{
				gr->data = 0;
				break;
			}

			if (prev)
				prev->next = gr;
			gr->delay = g.delay;
			prev = gr;
			gr = (gif_result*)stbi__malloc(sizeof(gif_result));
			memset(gr, 0, sizeof(gif_result));
			++(*frames);
		}

		STBI_FREE(g.out);

		if (gr != &head)
			STBI_FREE(gr);

		if (*frames > 0)
		{
			*x = g.w;
			*y = g.h;
		}

		result = head.data;

		if (*frames > 1)
		{
			unsigned int size = 4 * g.w * g.h;
			unsigned char *p = 0;

			result = (unsigned char*)stbi__malloc(*frames * (size + 2));
			if (result == NULL)
				goto end;
			gr = &head;
			p = result;

			while (gr)
			{
				prev = gr;
				memcpy(p, gr->data, size);
				p += size;
				*p++ = gr->delay & 0xFF;
				*p++ = (gr->delay & 0xFF00) >> 8;
				gr = gr->next;

				STBI_FREE(prev->data);
				if (prev != &head)
					STBI_FREE(prev);
			}
		}
	}
	else
	{
		result = NULL;
		*frames = 0;
	}

end:
	fclose(f);
	return result;
}

}

////////////////////////////////////////////////////////////////////////////////

// bool GIFLoader::loadFromFile(const std::string &filename, std::list<GIF::Frame *> &frames, unsigned &width, unsigned &height)
// {
// 	FILE *f;
// 	stbi__context s;

// 	if (!(f = stbi__fopen(filename.c_str(), "rb")))
// 		return false;

// 	stbi__start_file(&s, f);

// 	if (stbi__gif_test(&s)) {
// 		fclose(f);
// 		return false;
// 	}

// 	int c = 0;
// 	stbi__gif g;
// 	uint8_t *prev = NULL, *data = NULL;
// 	::memset(&g, 0, sizeof(g));

// 	while ((data = stbi__gif_load_next(&s, &g, &c, 4, prev ? prev : NULL))) {
// 		if (data == (unsigned char*)&s) {
// 			data = NULL;
// 			break;
// 		}

// 		GIF::Frame *frame = new GIF::Frame;
// 		frame->pixels = data;
// 		frame->delay = g.delay;
// 		prev = data;
// 		frames.push_back(frame);
// 	}

// 	STBI_FREE(g.out);

// 	if (frames.size() > 0) {
// 		width = g.w;
// 		height = g.h;
// 	}

// 	fclose(f);
// 	return true;
// }