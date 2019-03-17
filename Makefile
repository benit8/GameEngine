##
## EPITECH PROJECT, 2018
## Engine
## File description:
## Makefile utils
##

RM	=	rm -f
CC	=	g++

################################################################################

NAME	=	exe

SRCS	=	extern/stb/stb_image.cpp		\
		extern/imgui/imgui-SFML.cpp		\
		extern/imgui/imgui.cpp			\
		extern/imgui/imgui_demo.cpp		\
		extern/imgui/imgui_draw.cpp		\
		extern/imgui/imgui_widgets.cpp		\
		tests/main.cpp				\
		engine/Application.cpp			\
		engine/EventDispatcher.cpp		\
		engine/Graphics/AnimatedSprite.cpp	\
		engine/Graphics/Animation.cpp		\
		engine/Graphics/FPSCounter.cpp		\
		engine/Graphics/FontLoader.cpp		\
		engine/Graphics/GIF.cpp			\
		engine/Graphics/Window.cpp		\
		engine/StateManager.cpp			\
		engine/States/State.cpp			\

OBJS	=	$(SRCS:.cpp=.o)

################################################################################

CXXFLAGS	+=	-std=c++17
CXXFLAGS	+=	-W -Wall -Wextra
CXXFLAGS	+=	-Iengine -Iextern

LDFLAGS	+=	-lsfml-system -lsfml-window -lsfml-graphics -lGL

################################################################################

all: $(NAME)

debug: CXXFLAGS += -g3
debug: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
de: fclean debug

dump:
	@ echo "CXXFLAGS: [$(CXXFLAGS)]"
	@ echo "LDFLAGS: [$(LDFLAGS)]"

.PHONY: all debug $(NAME) clean fclean re de dump