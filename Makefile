# Name of the programs
NAME_FT = ft_containers
NAME_STD = std_containers

# Color codes
RESET	= \033[0m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m

# Compiler
CC = clang++

# Compiling flags
CFLAGS = -Wall -Wextra -Werror -std=c++98

# Sources
SRC = main.cpp

HDIR = includes
ODIR = objects
SDIR = sources
INCLUDES = -I../$(HDIR)
BINARIES = $(NAME_FT) $(NAME_STD)

project: $(BINARIES)

$(NAME_FT): $(ODIR)/main.o
	@$(CC) -o $@ $^
	@echo "$(GREEN)***   Project $(NAME_FT) successfully compiled   ***\n$(RESET)"
$(ODIR)/main.o: $(SDIR)/main.cpp $(HDIR)/*.hpp
	@echo "$(YELLOW)\n      -> Building $(NAME_FT) ...$(RESET)"
	@cd $(ODIR) && $(CC) $(INCLUDES) $(CFLAGS) -c ../$< -o main.o

$(NAME_STD): $(ODIR)/main2.o
	@$(CC) -o $@ $^
	@echo "$(GREEN)***   Project $(NAME_STD) successfully compiled   ***\n$(RESET)"
$(ODIR)/main2.o: $(SDIR)/main.cpp $(HDIR)/*.hpp
	@echo "$(YELLOW)\n      -> Building $(NAME_STD) ...$(RESET)"	
	@cd $(ODIR) && $(CC) -D STD $(INCLUDES) $(CFLAGS) -c ../$< -o main2.o

.PHONY: clean fclean re bonus all

all:
	make

clean:
	@rm -f $(ODIR)/*.o

fclean: clean
	@echo "$(BLUE)***   Deleting objects  ...   ***$(RESET)"
	@rm -f $(BINARIES)

re:
	@echo "$(BLUE)***   Deleting executables   ...   ***$(RESET)"
	@make fclean
	@make project

bonus:
	make
