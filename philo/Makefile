CC = cc

NAME = philo

CFLAGS = -g -pthread -Wall -Werror -Wextra

SRCS = basic_functions.c philosopher.c takingcare.c everyday_routine.c init_data.c

OBJS = ${SRCS:.c=.o}

RM = rm -f

all: $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS) $(B_OBJS)

fclean: clean
		$(RM) $(NAME) $(B_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
