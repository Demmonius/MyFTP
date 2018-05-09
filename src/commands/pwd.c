/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

/*!
 * @brief Manage pwd command
 * 
 * @file pwd.c
 */

#include "server.h"

/*!
 * @brief Manage pwd command
 * 
 * @param client Client struct
 * @param command command send
 */
void	commands_pwd(t_client *client, char *command)
{
	command = command;
	client = client;
	dprintf(client->client_fd, "257 \"");
	dprintf(client->client_fd, client->path);
	dprintf(client->client_fd, "\"\r\n");
}