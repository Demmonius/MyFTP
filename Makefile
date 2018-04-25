##
## EPITECH PROJECT, 2018
## MyFTP
## File description:
## Makefile
##

NAME	= server

CC	= gcc

RM	= rm -f

SRCS	= ./src/commands/cwd.c \
	  ./src/commands/list.c \
	  ./src/commands/modes.c \
	  ./src/commands/pwd.c \
	  ./src/commands/retr.c \
	  ./src/commands/stor.c \
	  ./src/commands.c \
	  ./src/manage_commands.c \
	  ./src/server.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./inc/
CFLAGS += -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
