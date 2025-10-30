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

NAME			:= ducklib.a
UNAME			:= $(shell uname)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror

# Libs
MINIFT_DIR		:= minilibft
MINIFT_H		= minilibft.h
MINIFT			= $(MINIFT_DIR)/minilibft.a

#Linkers
LINKS 	 	   = -lm -lpthread

# Includes
INKS			= -I$(CURDIR) -I$(MINIFT_DIR)

#source files (expected in the root folder)
SRCS_DIR		=
SRC_FILES		= point_masters.c shapemakers.c \
				thread_plotting.c base_plotting.c \
				\
				math_stuff.c math_utils.c math_sidekicks.c \
				\
				pid_lst_utils.c obj_list_utils.c \
				\
				free_stuff.c
SRCS			= $(addprefix $(SRCS_DIR), $(SRC_FILES))

# Objects
OBJS_DIR		= obj/
OBJ_FILES		= $(SRCS:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJ_FILES))

#folders containing source files [*.c] 
VPATH = list_fuctions math_functions

GIDEF			= """$\
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
				$(NAME)\n$\
				$(NAME).tar\n$\
				$(MINIFT_H)\n$\
				"""

all: $(NAME)

UNAME:
ifeq ($(UNAME),Error)
	$(error incompatible OS)
endif

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR) 
	@$(CC) $(CFLAGS) $(INKS) $(DEFS) -c $< -o $@

$(MINIFT):
	@$(MAKE) -C $(MINIFT_DIR) --quiet
	@cp $(MINIFT_DIR)/$(MINIFT_H) $(MINIFT_H)

$(NAME): $(MINIFT) $(OBJS)
	@cp $(MINIFT) $(NAME)
	@ar rcs $(NAME) $(OBJS_DIR)* \

tar: UNAME
	@ls | grep -q "$(NAME).tar" && rm -f $(NAME).tar || true
	@tar -cf $(NAME).tar --exclude=".git" --exclude="$(NAME)" --exclude="$(OBJS_DIR)" --exclude="$(MINIFT_DIR)/obj" ./*

.gitignore:
	@touch .gitignore
	@cat .gitignore | grep -q "#default rules" || \
		echo $(GIDEF)"$$(cat .gitignore)" > .gitignore

show:
	@printf "NAME  		: $(NAME)\n"
	@printf "UNAME		: $(UNAME)\n"
	@printf "MINIFT		: $(MINIFT)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "LINKS		: $(LINKS)\n"
	@printf "INCLUDES	: $(INKS)\n"
	@printf "SRCS		: $(SRCS)\n"
	@printf "OBJS		:\n$(OBJS)\n"

clean:
	@rm -rf $(OBJS_DIR) $(NAME).tar
	@$(MAKE) clean -C $(MINIFT_DIR) --quiet

fclean: clean
	@rm -rf $(NAME) $(MINIFT_H)
	@$(MAKE) fclean -C $(MINIFT_DIR) --quiet

lre: clean all

re: fclean all

.PHONY: UNAME all clean fclean re lre tar show .gitignore
