NAME = philo
SRC = philo.c utils.c

OBJ = $(SRC:%.c=%.o)

INCLUDE = philo.h

CC = CC

CFALGS =  -Wall -Wextra -Werror 

FSANITIZE = -fsanitize=thread

all : $(NAME)


$(NAME) : $(OBJ)

%.o : %.c $(INCLUDEB)
	$(CC) $(CFALGS)  -c $< -o $@

clean:
	rm -rf $(OBJ) 

fclean: clean
	rm -rf $(NAME)

re: fclean all