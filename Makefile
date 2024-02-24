NAME		= cub3d

CC			=	cc -g
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf
LIBFTPATH	=	./libft
MLXPATH		=	./minilibx
LIBA		=	$(LIBFTPATH)/libft.a
LIBMLXA		=	$(MLXPATH)/libmlx.a
MLXFLAG		=	-framework OpenGL -framework AppKit

OBJDIR		=	.objFiles

SRC			=	src/main			\
				src/check			\
				src/exit			\
				src/extra			\
				src/map_init		\
				src/ray_init		\
				src/mlx_utils		\
				src/move			\
				src/ray_manager		\
				src/ray				\
				src/read_map		\
				src/utils

OBJ			= $(addprefix $(OBJDIR)/, $(SRC:=.o))

all: $(NAME)

$(NAME): $(OBJ)
	clear
	@echo "\033[95m    - Compiling $(NAME)...\033[0m\n"
	@make -C $(LIBFTPATH)
	@make -C $(MLXPATH)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBA) $(LIBMLXA) $(MLXFLAG)
	clear
	@echo "\033[92m    - Compilation Over.✅\033[0m"


$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	clear
	@make clean -C $(LIBFTPATH)
	@make clean -C $(MLXPATH)
	@$(RM) $(OBJDIR) $(OBJ)
	clear
	@echo "\033[95m    - ⛔️ Executable removed-> $(NAME)\033[0m\n"
	@sleep 0.3
	clear

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFTPATH)
	@echo "\033[92m    - Cleanup Over.✅\033[0m"
	@sleep 0.5
	clear


re: fclean all

.PHONY: all clean fclean re

#valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes
