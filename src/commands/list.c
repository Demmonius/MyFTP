/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

/*!
 * @brief List command
 * 
 * @file list.c
 */
#define _GNU_SOURCE
#include "server.h"

/*!
 * @brief Execute ls with sed
 * 
 * @param client Client struct
 * @param save int to initial fd, to recover after dup2
 */
static void	main_list(t_client *client, int save)
{
	const char	*const cmd = "ls -l %s%s | sed 1d";
	char		*full_cmd;

	dprintf(client->client_fd, commands_infos[2]);
	client->second_fd = (client->client_status == PASV ?
		accept_connection(client->second_fd, client) :
			connect_to_client(client));
	if (client->second_fd == 84)
		return ;
	if (dup2(client->second_fd, 1) == -1)
		return ;
	asprintf(&full_cmd, cmd, client->base_path, client->path);
	if (system(full_cmd) == -1) {
		dup2(save, 1);
		close(client->second_fd);
		return ;
	}
}

/*!
 * @brief Command list
 * 
 * @param client Client struct
 * @param command command send
 */
void	commands_list(t_client *client, char *command)
{
	const int	save = dup(1);

	if (client->client_status == UNSET) {
		dprintf(client->client_fd, commands_infos[14]);
		return ;
	}
	(void)command;
	main_list(client, save);
	dup2(save, 1);
	close(client->second_fd);
	dprintf(client->client_fd, commands_infos[7]);
	client->second_fd = -1;
	client->client_status = UNSET;
}