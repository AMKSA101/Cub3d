NAME = cub3D
HEADER = ./Headers/cub3d.h
CCF = cc  -g  -I./Headers -I./libft -I./minilibx-linux #-fsanitize=address
SRC = 	Srcs/main.c Srcs/get_next_line.c Srcs/utils_1.c \
		Srcs/map_parse.c Srcs/map_parse_help.c Srcs/helper_funcs.c Srcs/texture_parse.c Srcs/color_parse.c Srcs/parsing.c Srcs/ft_parse_help.c\
		ray_casting/draw.c ray_casting/draw_getters.c ray_casting/draw_help.c ray_casting/extra_utils.c ray_casting/init.c ray_casting/moves.c  ray_casting/utils.c
SRC += Srcs/color_parse_utils.c Srcs/ft_parse_help2.c Srcs/extra_utils.c
OBJ_DIR = ./Obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
LIBFT = ./libft/libft.a #-Wall -Wextra -Werror
MLX = ./minilibx-linux/libmlx.a
LIBS = -L./libft -lft -L./minilibx-linux -lmlx -lXext -lX11 -lm

all: $(NAME)

$(OBJ_DIR)%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CCF) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CCF) $(OBJ) $(LIBS) -o $(NAME)

$(LIBFT):
	@make -C ./libft

$(MLX):
	@make -C ./minilibx-linux

clean:
	@make -C ./libft clean
	@make -C ./minilibx-linux clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C ./libft fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY:
