# Name of the program
NAME = ft_containers

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
SRC =	main_std.cpp

OBJ = $(patsubst %.cpp,%.o, $(SRC))

all: $(NAME)

%.o : %.cpp
	@$(CC) -c $(FLAGS) $< -o $@

$(NAME): $(OBJ)
	@echo "$(YELLOW)\n      -> Building $(NAME) ...$(RESET)"
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"
	@rm -f ./*.o

clean:
	@echo "$(BLUE)***   Deleting all objects from $(NAME)   ...   ***$(RESET)"
	@rm -f ./*.o

fclean: clean
	@echo "$(BLUE)***   Deleting executable file from $(NAME)   ...   ***$(RESET)"
	@rm -f ./$(NAME)

re: fclean all