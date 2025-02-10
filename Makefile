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

NAME			:= print_zed
UNAME			:= $(shell uname)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror

# Libs
LIBFT_DIR		:= libft
LIBFT			= $(LIBFT_DIR)/libft.a
LINKS 	 	   = -L/usr/lib -L$(MLX_DIR) -lXext -lX11 -lm -lz

# Includes
INKS			= -I$(LIBFT_DIR) -I$(MLX_DIR) -O3

#source files (expected in the root folder)
SRCS_DIR		=
SRC_FILES		= main.c input_handling.c \
				parsing.c parse_minions.c \
				point_masters.c shapemakers.c \
				math_stuff.c math_utils.c math_sidekicks.c \
				easy_startup_functions.c \
				checky_funtions.c
SRCS			= $(addprefix $(SRCS_DIR), $(SRC_FILES))

# Objects
OBJS_DIR		= obj/
OBJ_FILES		= $(SRCS:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJ_FILES))

#LINKS = -I /opt/homebrew/include -I /usr/X11/include -L /opt/homebrew/lib -L /usr/X11/lib -lX11 -Lmlx -lXext -framework OpenGL -framework AppKit

ifeq ($(UNAME),Darwin)
	MLX_DIR		= minilibx_opengl
	MLX			= $(MLX_DIR)/libmlx_$(UNAME).a
	URL			= https://cdn.intra.42.fr/document/document/28086/minilibx_opengl.tgz
	DEFS		= -D ESC_KEY=53 -D MAX_WIN_X=1440 -D MAX_WIN_Y=840
	INKS		+= -I/usr/X11/include
	LINKS		+= I/opt/homebrew/include -I/usr/X11/include -L/usr/X11/lib -framework OpenGL -framework AppKit
	STAT		= stat -f %m
	DATE		= date +%Y-%m-%d\ %H:%M:%S
else ifeq ($(UNAME),Linux)
	MLX_DIR		= minilibx-linux
	MLX			= $(MLX_DIR)/libmlx_$(UNAME).a
	URL			= https://cdn.intra.42.fr/document/document/28085/minilibx-linux.tgz
	DEFS		=
	INKS		+= -I/usr/include
	LINKS		+= -lmlx_Linux -I $(MLX_DIR)
	LINKS		= -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm -lz
	STAT		= stat -c %Z
	DATE		= date +%Y-%m-%d\ %H:%M:%S
else
	UNAME = Error
endif

#folders containing source files [*.c] 
VPATH =

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
				$(MLX_DIR)*\n$\
				data$\
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

data:
	@echo "${BOLD}extracting data...${RESET}"
	@ls -F | grep -q "data/" \
	&& echo "${YELLOW}data already exctracted.${RESET}" \
	|| (mkdir data \
	&& unzip -q Archive.zip -d data)

$(MLX_DIR):
	echo "${BOLD}creating $(MLX_DIR)...${RESET}"
	@curl $(URL) --output $(MLX_DIR).tgz \
	&& tar -xf $(MLX_DIR).tgz \
	&& rm -f $(MLX_DIR).tgz \
	&& ls $(MLX_DIR) || mv `ls | grep $(MLX_DIR)` $(MLX_DIR) \
	&& $(MAKE) -C $(MLX_DIR)

$(MLX): $(MLX_DIR)
	@rm -f $(MLX_DIR)/libmlx.a
	@$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	@echo "${BOLD}creating libft...${RESET}"
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	@echo "${BOLD}compiling $(NAME)...${RESET}"
#	=========== just for sowing different versions
	@rm -f $(OBJS_DIR)main_*
#	===========
	@$(CC) $(CFLAGS) $(OBJS_DIR)* $(MLX) $(LIBFT) $(LINKS) -o $(NAME) \
	&& echo "${LIGHT_GREEN}DONE${RESET}"

v1: $(MLX) $(LIBFT) $(OBJS)
	@echo "${BOLD}compiling $(NAME)_v1...${RESET}"
	@rm -f $(OBJS_DIR)main*
	@$(CC) $(CFLAGS) main_v1.c -I$(LIBFT_DIR) $(OBJS_DIR)* $(ARS) $(LINKS) -o $(NAME)_v1 \
	&& echo "${LIGHT_GREEN}DONE${RESET}"

v2: $(MLX) $(LIBFT) $(OBJS)
	@echo "${BOLD}compiling $(NAME)_v2...${RESET}"
	@rm -f $(OBJS_DIR)main*
	@$(CC) $(CFLAGS) main_v2.c -I$(LIBFT_DIR) $(OBJS_DIR)* $(ARS) $(LINKS) -o $(NAME)_v2 \
	&& echo "${LIGHT_GREEN}DONE${RESET}"

rundata: $(NAME) data
	@ARG="$(shell ls data | awk '{print "data/" $$0 }')"; ./$(NAME) "$$ARG"

tar: UNAME
	@ls | grep -q "$(NAME).tar" && rm -f $(NAME).tar || true
	@tar -cf $(NAME).tar --exclude=".git" --exclude="$(NAME)" --exclude="$(MLX_DIR)" --exclude="$(OBJS_DIR)" --exclude="$(LIBFT_DIR)/obj" --exclude="data" ./*

#test commands
#make tar && mkdir ../test && cd ../test && mv ../print_zed/print_zed.tar . && tar -xf print_zed.tar && ls -a
#cd .. && rm -rf test/ && cd print_zed 

.gitignore:
	@touch .gitignore
	@cat .gitignore | grep -q "#default rules" || \
		echo $(GIDEF)"$$(cat .gitignore)" > .gitignore

show:
	@printf "NAME  		: $(NAME)\n"
	@printf "UNAME		: $(UNAME)\n"
	@printf "LIBFT		: $(LIBFT)\n"
	@printf "MINILIBX	: $(MLX)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "LINKS		: $(LINKS)\n"
	@printf "INCLUDES	: $(INKS)\n"
	@printf "SRCS		: $(SRCS)\n"
	@printf "OBJS		:\n$(OBJS)\n"

clean:
	@rm -rf $(OBJS) $(NAME).tar $(MLX_DIR).tgz
	@$(MAKE) clean -C $(LIBFT_DIR) --quiet
	@echo "${BOLD}removed:${RESET}\vobjects (.o) and archives (.tar, .tgz)"

fclean: clean
	@rm -rf $(NAME) $(MLX_DIR) data
	@$(MAKE) fclean -C $(LIBFT_DIR) --quiet
	@echo "\texecutable ($(NAME)),\n\t$(MLX_DIR),\n\tdata extracted,\n\tarchives (.a)"

lre: clean all

re: fclean all

.PHONY: UNAME all clean fclean re lre nyaa tar .gitignore show
