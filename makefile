NAME = test	

<<<<<<< HEAD
SRC = sourceFiles/main.c\
	sourceFiles/character.c\
	sourceFiles/objects.c\
	sourceFiles/game.c\
	sourceFiles/map.c
=======
# Files
SRC= sourceFiles/main.c\
sourceFiles/game_event_2.c\
sourceFiles/game_destroy_2.c\
sourceFiles/game_init_2.c\
sourceFiles/game_draw_2.c\
sourceFiles/my_strlen.c
>>>>>>> 355992318ef981401873e1b6fcbc88b2b2689555

OBJ	= $(SRC:%.c=%.o)

CC=gcc
<<<<<<< HEAD
CC_SDL= -Wall -Wextra -Werror -lSDL2_image  `sdl2-config --cflags --libs`
=======
# SDL options
CC_SDL= -Wall -Wextra -Werror -lSDL2_image -lSDL2_ttf  `sdl2-config --cflags --libs`
>>>>>>> 355992318ef981401873e1b6fcbc88b2b2689555

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