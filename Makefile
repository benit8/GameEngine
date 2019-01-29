##
## EPITECH PROJECT, 2018
## Engine
## File description:
## Makefile utils
##

RM	=	rm -f
CC	=	g++

################################################################################

NAME	=	engine

SRCS	=	extern/stb/stb_image.cpp		\
		extern/imgui/imgui.cpp			\
		extern/imgui/imgui_draw.cpp		\
		extern/imgui/imgui_widgets.cpp		\
		extern/imgui/imgui-SFML.cpp		\
		extern/imgui/imgui_demo.cpp		\
		main.cpp				\
		src/Application.cpp			\
		src/EventDispatcher.cpp			\
		src/StateManager.cpp			\
		src/States/State.cpp			\
		src/Graphics/AnimatedSprite.cpp		\
		src/Graphics/Animation.cpp		\
		src/Graphics/FPSCounter.cpp		\
		src/Graphics/FontLoader.cpp		\
		src/Graphics/GIF.cpp			\
		src/Graphics/Window.cpp			\

OBJS	=	$(SRCS:.cpp=.o)

################################################################################

CXXFLAGS	+=	-std=c++17
CXXFLAGS	+=	-W -Wall -Wextra
CXXFLAGS	+=	-I. -Isrc -Iextern

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