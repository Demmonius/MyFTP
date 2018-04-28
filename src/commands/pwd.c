/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

#include "server.h"

void	commands_pwd(t_client *client, char *command)
{
	command = command;
	client = client;
	dprintf(client->client_fd, "257 \"");
	dprintf(client->client_fd, client->path);
	dprintf(client->client_fd, "\"\r\n");
}