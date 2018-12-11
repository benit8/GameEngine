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

SRCS	=	extern/stb_image.cpp			\
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
		src/GUI/GUI.cpp				\
		src/GUI/Env.cpp				\
		src/GUI/Widget.cpp			\
		src/GUI/Box.cpp				\
		src/GUI/Button.cpp			\
		src/GUI/Input.cpp			\
		src/GUI/Modal.cpp			\
		src/GUI/MessageBox.cpp			\

OBJS	=	$(SRCS:.cpp=.o)

################################################################################

CXXFLAGS	+=	-std=c++17
CXXFLAGS	+=	-W -Wall -Wextra
CXXFLAGS	+=	-I. -Isrc

LDFLAGS	+=	-lsfml-system		\
		-lsfml-window		\
		-lsfml-graphics

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