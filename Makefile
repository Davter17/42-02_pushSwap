# Standard
NAME				= push_swap

# Directories
LIBFT				= ./libft/libft.a
INC					= inc/
SRC_DIR				= srcs/
OBJ_DIR				= obj/

# Compiler and CFlags
CC					= cc
CFLAGS				= -Wall -Werror -Wextra -I
RM					= rm -f

# Source Files
COMMANDS_DIR		=	$(SRC_DIR)commands/alg_push.c \
						$(SRC_DIR)commands/alg_reverse_rotate.c \
						$(SRC_DIR)commands/alg_rotate.c \
						$(SRC_DIR)commands/alg_swap.c \
						$(SRC_DIR)commands/turk_algorithm.c \
						$(SRC_DIR)commands/sort_three.c

PUSH_SWAP_DIR		=	$(SRC_DIR)push_swap/check_errors.c \
						$(SRC_DIR)push_swap/init_a_to_b.c \
						$(SRC_DIR)push_swap/main.c \
						$(SRC_DIR)push_swap/generate_slot.c \
						$(SRC_DIR)push_swap/slot_utils.c

# Concatenate all source files
SRCS 				= $(COMMANDS_DIR) $(PUSH_SWAP_DIR)

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build rules
start:				
					@make all

$(LIBFT):
					@make -C ./libft

all: 				$(NAME)

$(NAME): 			$(OBJ) $(LIBFT)
					@$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) -o $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
					@$(RM) -r $(OBJ_DIR)
					@make clean -C ./libft

fclean: 			clean
					@$(RM) $(NAME)
					@$(RM) $(LIBFT)

re: 				fclean all

# Phony targets represent actions not files
.PHONY: 			start all clean fclean re