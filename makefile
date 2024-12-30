NAME = cub3D
HEADER = ./Headers/cub3d.h
CCF = cc -Wall -Wextra -Werror -O3 -I./Headers -I./libft -I./minilibx-linux
SRC = 	Srcs/main.c Srcs/get_next_line.c Srcs/parse_file.c Srcs/utils_1.c
OBJ_DIR = ./Obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
LIBFT = ./libft/libft.a
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
