
CC	= gcc

RM	= rm -f

NAME_SERVER	= server

SRCS_SERVER	= ./sever.c

OBJS_SERVER	= $(SRCS_SERVER:.c=.o)

NAME_CLIENT	= client

SRCS_CLIENT	= ./client.c

OBJS_CLIENT	= $(SRCS_CLIENT:.c=.o)

CFLAGS = -I ./inc/
CFLAGS += -W -Wall -Wextra

all: server client


server: $(OBJS_SERVER)
	 $(CC) $(OBJS_SERVER) -o $(NAME_SERVER) $(LDFLAGS)

client: $(OBJS_CLIENT)
	 $(CC) $(OBJS_CLIENT) -o $(NAME_CLIENT) $(LDFLAGS)

clean:
	$(RM) $(OBJS_CLIENT) $(OBJS_SERVER)

fclean: clean
	$(RM) $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all

.PHONY: all clean fclean re
