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
#include <dirent.h>
#include "client.h"

typedef struct s_host
{
	struct protoent			*pe;
	struct sockaddr_in		s_in;
	int				port;
	int				server_fd;
	char				*path;
}					t_host;
char	*parse_command(char *command, char c, int nb);
int	manage_commands(char *command, t_client *client);
void	commands_list(t_client *client, char *command);
void	commands_quit(t_client *client, char *command);
void	commands_pwd(t_client *client, char *command);
void	commands_retr(t_client *client, char *command);
void	commands_user(t_client *client, char *command);

#define LEN_FUNCS 4

extern void (*const commands[LEN_FUNCS])(t_client *, char *);
extern const char commands_name[LEN_FUNCS][64];
extern const char commands_infos[14][256];

#endif /* !SERVER_H_ */
