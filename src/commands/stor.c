/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

/*!
 * @brief Stor command file
 * 
 * @file stor.c
 */
#define _GNU_SOURCE
#include "server.h"

/*!
 * @brief Read a file
 * 
 * @param filename path to file
 * @return char* Return file with one char *
 */
char	*read_file(char *filename)
{
	FILE *file = fopen(filename, "r");
	char *buff;
	char c;
	int i = 0;

	if (file) {
		do {
			c = getc(file);
			buff = realloc(buff, i + 1);
			buff[i] = c;
			if (c == EOF)
				break ;
			i++;
		} while (42);
		putchar(c);
		fclose(file);
		buff[i] = '\0';
	}
	else
		return NULL;
	return buff;
}

/*!
 * @brief Command that manage stor command
 * 
 * @param client Client struct
 * @param command command send
 */
void commands_stor(t_client *client, char *command)
{
	char *filename;
	char *arg;

	if (client->client_status == UNSET) {
		dprintf(client->client_fd, commands_infos[14]);
		return ;
	}
	dprintf(client->client_fd, commands_infos[2]);
	client->second_fd = (client->client_status == PASV ?
		accept_connection(client->second_fd, client) :
		connect_to_client(client));
	if (client->second_fd == 84) {
		return ;
	}
	arg = parse_command(command, ' ', 1);
	asprintf(&filename, "%s%s%s", client->base_path, client->path, arg);
	free(filename);
	free(arg);
}