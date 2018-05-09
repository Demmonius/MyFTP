/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/


/*!
 * @brief Delete command
 * @file del.c
 */
#define _GNU_SOURCE
#include "server.h"

/*!
 * @brief Delete command
 * 
 * @param client Client struct
 * @param command command send
 */
void commands_del(t_client *client, char *command)
{
	char	*arg = parse_command(command, ' ', 1);
	char	*cmd;
	int status;

	(void)client;
	if (arg[0] == '/') {
		asprintf(&cmd, "%s/%s", client->base_path, arg);
		printf("%s\n", cmd);
		status = remove(cmd);
		free(cmd);
	}
	else {
		status = remove(arg);
	}
	dprintf(client->client_fd, (status == 0 ?
	commands_infos[10] : commands_infos[16]));
	free(arg);
}