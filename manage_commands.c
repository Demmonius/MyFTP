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

void commands_quit(t_client *client)
{
	(t_client *)client;
	client->have_to_quit = true;
}