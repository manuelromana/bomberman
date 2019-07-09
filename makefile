NAME = bomberman

SRC= sourceFiles/main.c\
sourceFiles/character.c\
	 sourceFiles/objects.c\
	 sourceFiles/game.c

OBJ	= $(SRC:%.c=%.o)

CC=gcc
CC_SDL= -Wall -Wextra -Werror -lSDL2_image  `sdl2-config --cflags --libs`

$(NAME): $(OBJ) 
	$(CC) $(OBJ) $(CC_SDL) -o $(NAME) 

all: $(NAME)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)
		rm -f $(OBJ)

re:		fclean all

.PHONY: all clean fclean re