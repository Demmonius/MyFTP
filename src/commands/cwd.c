/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

/*!
 * @brief Cwd command
 * 
 * @file cwd.c
 */

#define _GNU_SOURCE
#include "server.h"

/*!
 * @brief Command CWD
 * 
 * @param client Client struct
 * @param command command send
 */
void commands_cwd(t_client *client, char *command)
{
	char	*dir = parse_command(command, ' ', 1);
	char	*tmp = calloc(1, sizeof(char) *
		(strlen(client->path) + strlen(dir) + 2));

	strcpy(tmp, client->path);
	strcat(tmp, dir);
	free(client->path);
	if (dir[strlen(dir)] != '/')
		tmp[strlen(tmp)] = '/';
	client->path = tmp;
	dprintf(client->client_fd, "%s\n", commands_infos[10]);
}