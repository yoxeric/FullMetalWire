
NAME = fdf
BONUS = fdf_bonus
CC = gcc
CFLAGS	:= -Wall -Wextra -Werror

SRC = fdf.c draw_line.c init_grid.c draw_grid.c color.c
SRC_B = fdf_bonus.c bonus/draw_line_bonus.c bonus/init_grid_bonus.c bonus/draw_grid_bonus.c bonus/color_bonus.c\
		interface.c	control.c control2.c
UTILS =	utils/get_next_line.c utils/get_next_line_utils.c utils/ft_itoa.c utils/ft_atoi.c
# SRC = test/moving_wire.c draw_line.c color.c

OBJ = ${SRC:.c=.o}
OBJ_B = ${SRC_B:.c=.o}
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
FMW_B = "\033[31m\
	___________    .__  .__       _____          __         .__     __      __.__                \n\
	\_   _____/_ __|  | |  |     /     \   _____/  |______  |  |   /  \    /  \__|______   ____  \n\
    -|    __)|  |  \  | |  |    /  \ /  \_/ __ \   __\__  \ |  |   \   \/\/   /  \_  __ \_/ __ \ \n\
    -|     \ |  |  /  |_|  |__ /    Y    \  ___/|  |  / __ \|  |__  \        /|  ||  | \/\  ___/ \n\
    -\___  / |____/|____/____/ \____|__  /\___  >__| (____  /____/   \__/\  / |__||__|    \___  >\n\
    -----\/                            \/     \/          \/              \/                  \/ BONUS"


all: $(NAME)
	@echo $(FMW)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(UTILS) $(LIBS) -o $(NAME)

bonus: $(BONUS)
	@echo $(FMW_B)

$(BONUS): $(OBJ_B)
	$(CC) $(OBJ_B) $(UTILS) $(LIBS) -o $(BONUS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_B)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

# $(VERBOSE).SILENT:

.PHONY: all clean re
