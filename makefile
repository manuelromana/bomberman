NAME = draw
NAME2 = client
NAME3 = server
# Files
SRC= sourceFiles/gameInitTest.c\
sourceFiles/main_test.c

SRC2 = sourceFiles/game_connection.c\
sourceFiles/main.c  sourceFiles/my_strlen.c

SRC3 = sourceFiles/server.c sourceFiles/my_strlen.c

OBJ	= $(SRC:%.c=%.o)
OBJ2 = $(SRC2:%.c=%.o)
OBJ3 = $(SRC3:%.c=%.o)

# Build settings
CC=gcc
# SDL options
CC_SDL= -Wall -Wextra -Werror -lSDL2_image -lSDL2_ttf  `sdl2-config --cflags --libs`

$(NAME): $(OBJ) 
	$(CC) $(OBJ) $(CC_SDL) -o $(NAME) 

all: $(NAME)

client : $(OBJ2)
	$(CC) $(OBJ2) $(CC_SDL) -o $(NAME2)

server : $(OBJ3)
	$(CC) $(OBJ3) $(CC_SDL) -o $(NAME3)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)
		rm -f $(OBJ)

re:		fclean all

.PHONY: all clean fclean re