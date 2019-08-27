NAME = game
NAME2 = client
NAME3 = server
NAME4 = bomberman

SRC2 = sourceFiles/client.c

SRC3 = sourceFiles/main.c sourceFiles/game_connection.c\
	sourceFiles/networkFunction.c\
	sourceFiles/fonts.c \
	sourceFiles/game/game.c\
	sourceFiles/game/textures.c\
	sourceFiles/game/character.c\
	sourceFiles/game/objects.c\
	sourceFiles/game/map.c


SRC4 = sourceFiles/game/main.c\
	sourceFiles/game/game.c\
	sourceFiles/game/textures.c\
	sourceFiles/game/character.c\
	sourceFiles/game/objects.c\
	sourceFiles/game/map.c

OBJ	= $(SRC:%.c=%.o)
OBJ2 = $(SRC2:%.c=%.o)
OBJ3 = $(SRC3:%.c=%.o)
OBJ4	= $(SRC4:%.c=%.o)

OBJ0 =$(SRC2:%.c=%.o)\
	$(SRC3:%.c=%.o)\
	$(SRC4:%.c=%.o)

CC=gcc
CC_SDL=-Wall -Wextra -Werror -lSDL2_image -lSDL2_ttf `sdl2-config --cflags --libs`

all: $(NAME)

client : $(OBJ2)
	$(CC) $(OBJ2) $(CC_SDL) -o $(NAME2)

server : $(OBJ3)
	$(CC) $(OBJ3) $(CC_SDL) -o $(NAME3)

bomberman : $(OBJ4)
	$(CC) $(OBJ4) $(CC_SDL) -o $(NAME4)

game : $(OBJ0)
	$(CC) $(OBJ0) $(CC_SDL) -o $(NAME)

cleanBomberman:
	rm -f $(NAME4)
	rm -f $(OBJ4)

cleanClient :
	rm -f $(NAME2)
	rm -f $(OBJ2)

cleanServer :
	rm -f $(NAME3)
	rm -f $(OBJ3)

fclean:	clean
		rm -f $(NAME2)
		rm -f $(NAME3)
		rm -f $(NAME4)
		rm -f $(OBJ0)

re:		fclean all

.PHONY: all clean fclean re