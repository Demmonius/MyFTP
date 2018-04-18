/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

#include "server.h"

void	commands_ls(t_client *client)
{
	(t_client *)client;
	printf("LS started\n");
}

void	commands_pwd(t_client *client)
{
	char	cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		write(client->client_fd, cwd, strlen(cwd));
		write(client->client_fd, "\n", 1);
	}
	else
		write(2, "Error while write cwd on client\n", strlen("Error while write cwd on client\n"));
}

void commands_quit(t_client *client)
{
	(t_client *)client;
	client->have_to_quit = true;
}