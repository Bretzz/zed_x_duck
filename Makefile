# define standard colors
BOLD 		:= \033[1m
YELLOW		:= \033[1;33m
LIGHT_RED 	:= \033[91m
LIGHT_GREEN := \033[92m
LIGHT_CYAN 	:= \033[96m
RESET 		:= \033[0m

DIR := $(shell pwd)
OS := $(shell uname)
NAME := print_zed
CC := cc
CFLAGS := -Wall -Wextra -Werror

#LINKS = -I /opt/homebrew/include -I /usr/X11/include -L /opt/homebrew/lib -L /usr/X11/lib -lX11 -Lmlx -lXext -framework OpenGL -framework AppKit
ifeq ($(OS),Darwin)
	MINILX_DIR :=  minilibx_opengl
	URL = https://cdn.intra.42.fr/document/document/28086/minilibx_opengl.tgz
	INK = -D ESC_KEY=53 -D MAX_WIN_X=1440 -D MAX_WIN_Y=840 -I/usr/include -I/usr/X11/include -I$(MINILX_DIR) -I$(LIBFT_DIR) -O3
	LINKS = -I$(MINILX_DIR) -I$(DIR) -I/opt/homebrew/include -I/usr/X11/include -L$(MINILX_DIR) -L/usr/lib -L/usr/X11/lib -lX11 -lXext -lm -lz -framework OpenGL -framework AppKit
else ifeq ($(OS),Linux)
	MINILX_DIR := minilibx-linux
	URL = https://cdn.intra.42.fr/document/document/28085/minilibx-linux.tgz
	INK = -I/usr/include -I$(MINILX_DIR) -I$(LIBFT_DIR) -O3
	LINKS = -L$(MINILX_DIR) -lmlx_Linux -L/usr/lib -I$(MINILX_DIR) -lXext -lX11 -lm -lz
else
	MINILX_DIR = 
	URL = 
	INK = 
	LINKS = 
	@echo "Error, incompatible OS." && false;
endif

#source files (full path optional)
SRCS := main.c input_handling.c \
		math_sidekicks.c \
		easy_startup_functions.c \
		checky_funtions.c

#archive file names
ARS	= $(LIBFT_DIR)/libft.a $(MINILX_DIR)/libmlx.a #libmlx_Linux.a

#folders containing source files [*.c] 
VPATH =

EXE = nyaa
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))
OBJ_DIR := $(DIR)/obj
LIBFT_DIR := libft
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
		$(NAME)\n$\
		$(NAME).tar\n$\
		$(MINILX_DIR)*\n$\
		data$\
		"""

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) $(INK) -c $< -o $(OBJ_DIR)/$(notdir $@)

data:
	@echo "${BOLD}extracting data...${RESET}"
	@ls -F | grep -q "data/" \
	&& echo "${YELLOW}data already exctracted.${RESET}" \
	|| (mkdir data \
	&& unzip -q Archive.zip -d data)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(MINILX_DIR):
	@echo "${BOLD}creating $(MINILX_DIR)...${RESET}"
	@ls | grep -q "$(MINILX_DIR)" \
	&& echo "${YELLOW}$(MINILX_DIR) is up to date.${RESET}" \
	|| (curl $(URL) --output $(MINILX_DIR).tgz \
	&& tar -xf $(MINILX_DIR).tgz \
	&& rm -f $(MINILX_DIR).tgz \
	&& ls $(MINILX_DIR) || mv `ls | grep $(MINILX_DIR)` $(MINILX_DIR) \
	&& $(MAKE) -C $(MINILX_DIR) --quiet)

$(LIBFT_DIR):
	@echo "${BOLD}creating libft...${RESET}"
	@$(MAKE) -C $(LIBFT_DIR) | grep -q "Nothing to be done for" \
	&& echo "${YELLOW}libft is up to date.${RESET}" \
	|| true

$(NAME): $(MINILX_DIR) $(LIBFT_DIR) $(OBJS) data
	@echo "${BOLD}compiling $(NAME)...${RESET}"
	@echo "$(shell stat -c %Z $(OBJ_DIR)/*)" | grep -q "$(shell date +%s)" \
	&& ($(CC) $(CFLAGS) $(OBJ_DIR)/* $(ARS) $(LINKS) -o $(NAME) \
	&& echo "${LIGHT_GREEN}DONE${RESET}") \
	|| echo "${YELLOW}$(NAME) is up to date.${RESET}"

$(EXE):
	@echo "${BOLD}compiling main.c...${RESET}"
	@$(CC) main.c $(ARS) $(LINKS) -o $(EXE)
	@echo "${LIGHT_GREEN}DONE${RESET}"

tar:
	@ls | grep -q "$(NAME).tar" && rm -f $(NAME).tar || true
	@tar -cf $(NAME).tar --exclude=".git" --exclude="$(NAME)" --exclude="$(MINILX_DIR)" --exclude="obj" --exclude="$(LIBFT_DIR)/obj" --exclude="data" ./*

#test commands
#make tar && mkdir ../test && cd ../test && mv ../print_zed/print_zed.tar . && tar -xf print_zed.tar && ls -a
#cd .. && rm -rf test/ && cd print_zed 

.gitignore:
	@touch .gitignore
	@cat .gitignore | grep -q "#default rules" || \
		echo $(GIDEF)"$$(cat .gitignore)" > .gitignore

show:
	@printf "NAME  		: $(NAME)\n"
	@printf "OS		: $(OS)\n"
	@printf "LIBFT		: $(DIR)/$(LIBFT_DIR)\n"
	@printf "MINILIBX	: $(DIR)/$(MINILX_DIR)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "LINKS		: $(LINKS)\n"
	@printf "INCLUDES	: $(INK)\n"
	@printf "SRCS		:\n	$(SRCS)\n"
	@printf "OBJS		:\n	$(OBJS)\n"

clean:
	@rm -rf $(OBJ_DIR) $(NAME).tar $(MINILX_DIR).tgz
	@echo "${BOLD}removed:${RESET}\vobjects (.o) and archives (.tar, .tgz)"

fclean: clean
	@rm -rf $(NAME) $(EXE) $(MINILX_DIR)* data
	@$(MAKE) fclean -C $(LIBFT_DIR) --quiet
	@echo "\texecutable ($(NAME), $(EXE)),\n\t$(MINILX_DIR),\n\tdata extracted,\n\tarchives (.a)"

lre: clean all

re: fclean all

.PHONY: all clean fclean re lre nyaa $(LIBFT_DIR) $(MINILX_DIR) data tar .gitignore show
