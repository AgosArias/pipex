NAME = pipex

CC = cc
CFLAGS = -Wall -Wall -Werror -Iincludes 

SRC_DIR = src

SRC = $(SRC_DIR)/pipex.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "✅ Compilación completa: $(NAME)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all 
