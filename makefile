NAME = test	

# Files
SRC= sourceFiles/main.c\
sourceFiles/game_event_2.c\
sourceFiles/game_destroy_2.c\
sourceFiles/game_init_2.c\
sourceFiles/game_draw_2.c\
sourceFiles/my_strlen.c

OBJ	= $(SRC:%.c=%.o)

# Build settings
CC=gcc
# SDL options
CC_SDL= -Wall -Wextra -Werror -lSDL2_image -lSDL2_ttf  `sdl2-config --cflags --libs`

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