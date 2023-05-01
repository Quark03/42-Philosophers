NAME = philo

CC = cc
FLAGS = -Wall -Wextra -Werror -g -O3 # -fsanitize=thread
INCLUDE = -lpthread

SRCS = init.c \
	   main.c \
	   philo.c \
	   utils.c \
	   utils2.c

OBJS = $(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(INCLUDE)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY:	clean fclean re
