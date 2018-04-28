/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

#define _GNU_SOURCE
#include "server.h"

void commands_noop(t_client *client, char *command)
{
	(void)client;
	(void)command;
	dprintf(client->client_fd, commands_infos[3]);
}