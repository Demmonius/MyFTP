/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Main Header file
*/

#ifndef SERVER_H_
	#define SERVER_H_
	
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include "client.h"

typedef struct s_host
{
	struct protoent			*pe;
	struct sockaddr_in		s_in;
	int				port;
	int				server_fd;
	char				*path;
}					t_host;

int	manage_commands(char *command, t_client *client);
void	commands_list(t_client *client);
void	commands_quit(t_client *client);
void	commands_pwd(t_client *client);

#define LEN_FUNCS 4

extern void (*const commands[LEN_FUNCS])(t_client *, char *);
extern const char commands_name[LEN_FUNCS][64];

#endif /* !SERVER_H_ */
