# define standard colors
BOLD			= \033[1m
BLACK    		= \033[30m    # Black
RED      		= \033[31m    # Red
GREEN    		= \033[32m    # Green
YELLOW   		= \033[33m    # Yellow
BLUE     		= \033[34m    # Blue
MAGENTA  		= \033[35m    # Magenta
CYAN     		= \033[36m    # Cyan
WHITE    		= \033[37m    # White
LIGHT_RED		= \033[91m
LIGHT_GREEN		= \033[92m
LIGHT_CYAN		= \033[96m
RESET			= \033[0m

NAME			= minilibft.a
CC				= cc
CFLAGS			= -Wall -Wextra -Werror

#source files (full path optional)
SRCS_DIR		=
SRC_FILES		= ft_atoi.c \
				ft_isdigit.c ft_isspace.c \
				ft_strncmp.c ft_strchr.c
SRCS			= $(addprefix $(SRCS_DIR), $(SRC_FILES))


#folders containing source files [*.c]
VPATH			= 

# Objects
OBJS_DIR		= obj/
OBJ_FILES		= $(SRCS:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJ_FILES))
GIDEF			=	"""$\
					\#default rules\n$\
					.gitignore\n$\
					.git\n$\
					.vscode\n$\
					**/temp\n$\
					**/$(OBJS_DIR)\n$\
					**/resources\n$\
					**/a.out\n$\
					**/*.a\n$\
					**/tester.c\n$\
					\n$\
					\#added rules\n$\
					"""

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR) 
	@$(CC) $(CFLAGS) $(INK) $(DEFS) -c $< -o $@

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS_DIR)*

.gitignore:
	@touch .gitignore
	@cat .gitignore | grep "#default rules" || \
		echo $(GIDEF)"$$(cat .gitignore)" > .gitignore

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re main .gitignore
