# define standard colors
BOLD 		:= \033[1m
YELLOW		:= \033[1;33m
LIGHT_RED 	:= \033[91m
LIGHT_GREEN := \033[92m
LIGHT_CYAN 	:= \033[96m
RESET 		:= \033[0m

DIR := $(shell pwd)
NAME := libft.a
CC := cc
CFLAGS := -Wall -Wextra -Werror

#source files (full path optional)
SRCS :=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_split.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strchr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	\
	ft_lstadd_back.c ft_lstadd_front.c \
	ft_lstclear.c ft_lstdelone.c ft_lstnew.c \
	ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstsize.c \
	\
	ft_printf.c \
	nest_putexa_fd.c \
	nest_putptr_fd.c \
	nest_putput_fd.c \
	nest_putuns_fd.c \
	west_putchar_fd.c \
	west_putnbr_fd.c \
	west_putstr_fd.c \
	\
	get_next_line.c \
	get_next_line_utils.c 

#folders containing source files [*.c]
VPATH = 

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))
OBJ_DIR := $(DIR)/obj
GIDEF =	"""$\
		\#default rules\n$\
		.gitignore\n$\
		.git\n$\
		.vscode\n$\
		**/temp\n$\
		**/obj\n$\
		**/resources\n$\
		**/a.out\n$\
		**/*.a\n$\
		**/tester.c\n$\
		\n$\
		\#added rules\n$\
		"""

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)/$(notdir $@) -I$(DIR)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJ_DIR)/*

.gitignore:
	@touch .gitignore
	@cat .gitignore | grep "#default rules" || \
		echo $(GIDEF)"$$(cat .gitignore)" > .gitignore

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re main .gitignore
