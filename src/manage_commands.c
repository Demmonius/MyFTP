/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

/*!
 * @brief Commands manage file
 * 
 * @file manage_commands.c
 */

#define _GNU_SOURCE
#include "server.h"

/*!
 * @brief Command quit
 * Quit FTP connection
 * @param client Client struct
 * @param command command send
 */

void commands_quit(t_client *client, char *command)
{
	command = command;
	dprintf(client->client_fd, commands_infos[6]);
	client->have_to_quit = true;
}

/*!
 * @brief Command user
 * Connect with an ID
 * @param client Client struct
 * @param command command send
 */
void commands_user(t_client *client, char *command)
{
	client->user = parse_command(command, ' ', 1);
	dprintf(client->client_fd, "331 Please specify the password\r\n");
}

/*!
 * @brief Command pass
 * Connect with a password
 * @param client Client struct
 * @param command command send
 */
void commands_pass(t_client *client, char *command)
{
	command = command;
	if (!client->user)
		return ;
	if (strcmp(client->user, "Anonymous") == 0) {
		client->is_log = true;
		dprintf(client->client_fd, "230 Login seccessful\n");
	}
	else
		dprintf(client->client_fd, "530 Login incorrect\n");
}

/*!
 * @brief Command cdup
 * Get to parent directory
 * @param client Client struct
 * @param command command send
 */
void commands_cdup(t_client *client, char *command)
{
	char *str = parse_command(command, ' ', 1);

	free(client->path);
	if (strlen(str) == 1) {
		client->path = strdup("/");
		return ;
	}
	if (str[strlen(str) - 1] == '/')
		str[strlen(str)-1] = '\0';
	for (int i = strlen(str); str[i] != '/'; i--)
		str[i] = '\0';
	client->path = realloc(str, sizeof(char) * (strlen(str) + 1));
}