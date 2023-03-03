
NAME = fdf
BONUS = fdf_bonus
CC = gcc
CFLAGS	:= -Wall -Wextra -Werror
SRC = draw_line.c init_grid.c draw_grid.c\
		interface.c	control.c control2.c color.c\
		utils/get_next_line.c utils/get_next_line_utils.c utils/ft_itoa.c utils/ft_atoi.c
# SRC = test/moving_wire.c draw_line.c color.c
OBJ = ${SRC:.c=.o}
LIBMLX	:= MLX42/libmlx42.a
LIBGLFW	:= MLX42/libglfw3.a 
LIBS	:= $(LIBMLX) $(LIBGLFW) -ldl -pthread -lm -Iinclude -framework Cocoa -framework OpenGL -framework IOKit

FMW = "\033[31m\
	___________    .__  .__       _____          __         .__     __      __.__                \n\
	\_   _____/_ __|  | |  |     /     \   _____/  |______  |  |   /  \    /  \__|______   ____  \n\
    -|    __)|  |  \  | |  |    /  \ /  \_/ __ \   __\__  \ |  |   \   \/\/   /  \_  __ \_/ __ \ \n\
    -|     \ |  |  /  |_|  |__ /    Y    \  ___/|  |  / __ \|  |__  \        /|  ||  | \/\  ___/ \n\
    -\___  / |____/|____/____/ \____|__  /\___  >__| (____  /____/   \__/\  / |__||__|    \___  >\n\
    -----\/                            \/     \/          \/              \/                  \/ "

all: $(NAME) $(BONUS)
	echo $(FMW)

$(NAME): $(OBJ)
	@$(CC) fdf.c $(OBJ) $(LIBS) -o $(NAME)

$(BONUS): $(OBJ)
	@$(CC) fdf_bonus.c $(OBJ) $(LIBS) -o $(BONUS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

$(VERBOSE).SILENT:

.PHONY: all clean re
