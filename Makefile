NAME = fdf
CC = gcc
CFLAGS	:= -Wall -Wextra -Werror

LIBS := MLX42/libmlx42.a MLX42/libglfw3.a -ldl -pthread -lm -Iinclude -framework Cocoa -framework OpenGL -framework IOKit

HEADERS = fdf.h
SRC = fdf.c draw_line.c read_grid.c draw_grid.c color.c\
	interface.c control.c control2.c\
	utils/get_next_line.c utils/get_next_line_utils.c utils/ft_itoa.c utils/ft_atoi.c utils/ft_strlen.c

OBJ = ${SRC:.c=.o}

FMW = "\033[31m\
	___________    .__  .__       _____          __         .__     __      __.__                \n\
	\_   _____/_ __|  | |  |     /     \   _____/  |______  |  |   /  \    /  \__|______   ____  \n\
    -|    __)|  |  \  | |  |    /  \ /  \_/ __ \   __\__  \ |  |   \   \/\/   /  \_  __ \_/ __ \ \n\
    -|     \ |  |  /  |_|  |__ /    Y    \  ___/|  |  / __ \|  |__  \        /|  ||  | \/\  ___/ \n\
    -\___  / |____/|____/____/ \____|__  /\___  >__| (____  /____/   \__/\  / |__||__|    \___  >\n\
    -----\/                            \/     \/          \/              \/                  \/ "

all: $(NAME)
	@echo $(FMW)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(OBJ) $(LIBS) -o $(NAME)

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(UTILS) 

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: all clean re
