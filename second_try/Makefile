NAME = scop
CC = g++
CFLAGS =  -std=c++11
OPENGL = -lglut -lGLU -lGL -lGLEW -lglfw  

SRCS =	main.cpp\
		utils.cpp\
		glad.c\
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