NAME = server	

# Files
SRC= sourceFiles/server.c\
sourceFiles/my_strlen.c\
sourceFiles/read_client.c

OBJ	= $(SRC:%.c=%.o)

# Build settings
CC=gcc
# SDL options
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