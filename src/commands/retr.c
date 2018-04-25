/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

#define _GNU_SOURCE
#include "server.h"

void commands_retr(t_client *client, char *command)
{
	char *arg = parse_command(command, ' ', 1);
	int c;
	FILE *file;
	char	*filename;

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
	asprintf(&filename, "%s%s%s", client->base_path, client->path, arg);
	file = fopen(filename, "r");
	if (file) {
		do {
			c = getc(file);
			if (c == EOF)
				break ;
			write(client->second_fd, &c, 1);
		} while (42);
	        putchar(c);
	    fclose(file);
	}
	else {
		dprintf(client->client_fd, commands_infos[16]);
		printf("Tried access to |%s|\n", filename);
	}
	free(filename);
	close(client->second_fd);
	dprintf(client->client_fd, commands_infos[7]);
	client->second_fd = -1;
	client->client_status = UNSET;
}