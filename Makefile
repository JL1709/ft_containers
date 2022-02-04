# Name of the program
NAME_FT  = ft_containers
NAME_STD = std_containers

# Color codes
RESET	= \033[0m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m

# Compiler
CC = clang++

# Compiling flags
FLAGS = -Wall -Wextra -Werror -std=c++98

# Sources
SRC_FT  =	main_ft.cpp
SRC_STD =	main_std.cpp

OBJ_FT = $(patsubst %.cpp,%.o, $(SRC_FT))
OBJ_STD = $(patsubst %.cpp,%.o, $(SRC_STD))

all: $(NAME_FT) $(NAME_STD)

%.o : %.cpp
	@$(CC) -c $(FLAGS) $< -o $@

$(NAME_FT): $(OBJ_FT)
	@echo "$(YELLOW)\n      -> Building $(NAME_FT) ...$(RESET)"
	@$(CC) $(FLAGS) $(OBJ_FT) -o $(NAME_FT)
	@echo "$(GREEN)***   Project $(NAME_FT) successfully compiled   ***\n$(RESET)"
	@rm -f ./*.o

$(NAME_STD): $(OBJ_STD)
	@echo "$(YELLOW)\n      -> Building $(NAME_STD) ...$(RESET)"
	@$(CC) $(FLAGS) $(OBJ_STD) -o $(NAME_STD)
	@echo "$(GREEN)***   Project $(NAME_STD) successfully compiled   ***\n$(RESET)"
	@rm -f ./*.o

clean:
	@echo "$(BLUE)***   Deleting objects  ...   ***$(RESET)"
	@rm -f ./*.o

fclean: clean
	@echo "$(BLUE)***   Deleting executables   ...   ***$(RESET)"
	@rm -f ./$(NAME_FT)
	@rm -f ./$(NAME_STD)

re: fclean all