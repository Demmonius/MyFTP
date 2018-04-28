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
#include <sys/wait.h>
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
int	accept_connection(int fd, t_client *client);
int	connect_to_client(t_client *client);
char	*to_lowcase(char *str);
t_host	*init_host(char **av);
t_host	*listen_sock(t_host *server);
int	handle_client(t_client *client);
int	make_socket(int *port);
t_client	*make_client(t_host *server);
void	commands_list(t_client *client, char *command);
void	commands_quit(t_client *client, char *command);
void	commands_pwd(t_client *client, char *command);
void	commands_retr(t_client *client, char *command);
void	commands_user(t_client *client, char *command);
void	commands_pass(t_client *client, char *command);
void	commands_cwd(t_client *client, char *command);
void	commands_pasv(t_client *client, char *command);
void 	commands_port(t_client *client, char *command);
void	commands_stor(t_client *client, char *command);
void	commands_cdup(t_client *client, char *command);
void	commands_help(t_client *client, char *command);
void	commands_noop(t_client *client, char *command);
void	commands_del(t_client *client, char *command);

#define LEN_FUNCS 13

extern void (*const commands[LEN_FUNCS])(t_client *, char *);
extern const char commands_name[LEN_FUNCS][64];
extern const char commands_infos[18][256];

#endif /* !SERVER_H_ */
