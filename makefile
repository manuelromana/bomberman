NAME = bomberman	

SRC = sourceFiles/main.c\
	sourceFiles/character.c\
	sourceFiles/game.c\
	sourceFiles/objects.c\
	sourceFiles/map.c

OBJ	= $(SRC:%.c=%.o)

CC=gcc
CC_SDL=-ggdb -g -Wall -Wextra -Werror -lSDL2_image  `sdl2-config --cflags --libs`

$(NAME): $(OBJ) 
	$(CC) $(OBJ) $(CC_SDL) -o $(NAME) 

all: $(NAME)

clean:
		rm -f $(NAME)
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)
		rm -f $(OBJ)

re:		fclean all

.PHONY: all clean fclean re