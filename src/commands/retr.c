/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

/*!
 * @brief Manage retr command
 * 
 * @file retr.c
 */
#define _GNU_SOURCE
#include "server.h"

/*!
 * @brief Opening file
 * 
 * @param client Client sturct
 * @param filename File to open
 */
static void main_retr(t_client *client, char *filename)
{
	FILE *file;
	int c;

	file = fopen(filename, "r");
	if (file) {
		dprintf(client->client_fd, commands_infos[2]);
		do {
			c = getc(file);
			if (c == EOF)
				break ;
			write(client->second_fd, &c, 1);
		} while (42);
		putchar(c);
		fclose(file);
	}
	else
		dprintf(client->client_fd, commands_infos[16]);
}

/*!
 * @brief Manage retr command
 * 
 * @param client Client struct
 * @param command command send
 */
void commands_retr(t_client *client, char *command)
{
	char	*filename;
	char	*arg = parse_command(command, ' ', 1);

	if (client->client_status == UNSET) {
		dprintf(client->client_fd, commands_infos[14]);
		return ;
	}
	client->second_fd = (client->client_status == PASV ?
		accept_connection(client->second_fd, client) :
		connect_to_client(client));
	if (client->second_fd == 84)
		return ;
	asprintf(&filename, "%s%s%s", client->base_path, client->path, arg);
	main_retr(client, filename);
	close(client->second_fd);
	dprintf(client->client_fd, commands_infos[7]);
	client->second_fd = -1;
	client->client_status = UNSET;
	free(filename);
}