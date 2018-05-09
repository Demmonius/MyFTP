##
## EPITECH PROJECT, 2018
## MyFTP
## File description:
## Makefile
##

NAME	= server

DOC_CONFIG_FILE = documentation.conf

CC	= gcc

RM	= rm -f

SRCS	= ./src/commands/cwd.c \
	./src/commands/list.c \
	./src/commands/modes.c \
	./src/commands/pwd.c \
	./src/commands/retr.c \
	./src/commands/stor.c \
	./src/commands/help.c \
	./src/commands/noop.c \
	./src/commands/del.c \
	./src/commands.c \
	./src/manage_commands.c \
	./src/inits.c	\
	./src/server.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./inc/
CFLAGS += -Wall -Wextra -g3

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

doc:
	doxygen $(DOC_CONFIG_FILE)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) -r doc

re: fclean all

.PHONY: all clean fclean re
