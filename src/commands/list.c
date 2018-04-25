/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

#define _GNU_SOURCE
#include "server.h"

void	commands_list(t_client *client, char *command)
{
	const char	*const cmd = "ls -l %s%s | sed 1d";
	const int	save = dup(1);
	char		*full_cmd;

	if (client->client_status == UNSET) {
		dprintf(client->client_fd, commands_infos[14]);
		return ;
	}
	dprintf(client->client_fd, commands_infos[2]);
	client->second_fd = (client->client_status == PASV ? accept_connection(client->second_fd, client) : connect_to_client(client));
	if (client->second_fd == 84) {
		perror("Fd accept or connection: ");
		return ;
	}
	if (dup2(client->second_fd, 1) == -1) {
		fprintf(stderr, "Dup2 failed\n");
		return ;
	}
	asprintf(&full_cmd, cmd, client->base_path, client->path);
	if (system(full_cmd) == -1) {
		dup2(save, 1);
		close(client->second_fd);
		return ;
	}
	dup2(save, 1);
	close(client->second_fd);
	dprintf(client->client_fd, commands_infos[7]);
	client->second_fd = -1;
	client->client_status = UNSET;
}