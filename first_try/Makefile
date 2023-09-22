NAME = scop
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++11
OPENGL = -lglut -lGLU -lGL

SRCS =	main.cpp \
		utils.cpp \
		game.cpp

SOURCES = $(addprefix sources/, $(SRCS))

all: COMP

COMP: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(OPENGL) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re