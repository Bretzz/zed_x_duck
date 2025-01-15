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

#source files (full path optional)
SRCS := main.c input_handling.c \
		math_sidekicks.c \
		easy_startup_functions.c \
		checky_funtions.c

#archive file names
ARS	:= libft/libft.a minilibx-linux/libmlx.a #libmlx_Linux.a

#folders containing source files [*.c] 
VPATH =

EXE = nyaa
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))
OBJ_DIR := $(DIR)/obj
LIBFT_DIR = libft
MINILX_DIR := minilibx-linux
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
		$(NAME)*\n$\
		$(MINILX_DIR)*\n$\
		data$\
		"""

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@if [ $(OS) = "Darwin" ]; then\
		$(CC) $(CFLAGS) -I/usr/include -I/usr/X11/include -I$(MINILX_DIR) -I$(LIBFT_DIR) -O3 -c $< -o $(OBJ_DIR)/$(notdir $@);\
	elif [ $(OS) = "Linux" ]; then\
		$(CC) $(CFLAGS) -I/usr/include -I$(MINILX_DIR) -I$(LIBFT_DIR) -O3 -c $< -o $(OBJ_DIR)/$(notdir $@);\
    else \
		echo "Error, incompatible OS." && false;\
	fi

data:
	@echo "${BOLD}extracting data...${RESET}"
	@ls -F | grep -q "data/" \
	&& echo "${YELLOW}data already exctracted.${RESET}" \
	|| (mkdir data \
	&& unzip -q Archive.zip -d data)

$(MINILX_DIR):
	@echo "${BOLD}creating $(MINILX_DIR)...${RESET}"
	@ls | grep -q "$(MINILX_DIR)" \
	&& echo "${YELLOW}$(MINILX_DIR) is up to date.${RESET}" \
	|| (curl https://cdn.intra.42.fr/document/document/28085/$(MINILX_DIR).tgz --output $(MINILX_DIR).tgz \
	&& tar -xf $(MINILX_DIR).tgz \
	&& rm -f $(MINILX_DIR).tgz \
	&& $(MAKE) -C $(MINILX_DIR) --quiet)

$(LIBFT_DIR):
	@echo "${BOLD}creating libft...${RESET}"
	@$(MAKE) -C $(LIBFT_DIR) | grep -q "Nothing to be done for" \
		&& echo "${YELLOW}libft is up to date.${RESET}" \
		|| true

$(NAME): $(MINILX_DIR) $(LIBFT_DIR) $(OBJS) data
	@echo "${BOLD}compiling $(NAME)...${RESET}"
	@if [ $(OS) = "Darwin" ]; then\
		$(CC) $(CFLAGS) $(OBJ_DIR)/* $(ARS) -L$(MINILX_DIR) -L/usr/lib -I$(MINILX_DIR) -lm -lz -o $(NAME) \
		&& echo "${LIGHT_GREEN}DONE${RESET}";\
	elif [ $(OS) = "Linux" ]; then\
		$(CC) $(CFLAGS) $(OBJ_DIR)/* $(ARS) -L$(MINILX_DIR) -lmlx_Linux -L/usr/lib -I$(MINILX_DIR) -lXext -lX11 -lm -lz -o $(NAME) \
		&& echo "${LIGHT_GREEN}DONE${RESET}";\
    else \
		echo "Error, incompatible OS." && false;\
	fi

$(EXE):
	@echo "${BOLD}compiling main.c...${RESET}"
	@$(CC) main.c $(ARS) -L$(MINILX_DIR) -lmlx_Linux -L/usr/lib -I$(MINILX_DIR) -I$(LIBFT_DIR) -lXext -lX11 -lm -lz -o $(EXE)
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
	@printf "LIBFT		: $(DIR)/$(LIBFT_DIR)\n"
	@printf "MINILX		: $(DIR)/$(MINILX_DIR)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "SRCS		:\n	$(SRCS)\n"
	@printf "OBJS		:\n	$(OBJS)\n"

clean:
	@rm -rf $(OBJ_DIR) $(NAME).tar
	@$(MAKE) clean -C $(LIBFT_DIR) --quiet
	@echo "${BOLD}removed:${RESET}\n\tobjects (.o) and archives (.tar)"

fclean: clean
	@rm -rf $(NAME) $(EXE) $(MINILX_DIR) data
	@$(MAKE) fclean -C $(LIBFT_DIR) --quiet
	@echo "\texecutable ($(NAME), $(EXE)),\n\t$(MINILX_DIR),\n\tdata extracted,\n\tarchives (.a)"

re: fclean all

.PHONY: all clean fclean re nyaa $(LIBFT_DIR) $(MINILX_DIR) data tar .gitignore show
