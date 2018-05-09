/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

/*!
 * @brief Help command
 * 
 * @file help.c
 */

#define _GNU_SOURCE
#include "server.h"

/*!
 * @brief Help command
 * 
 * @param client Client struct
 * @param command command send
 */
void commands_help(t_client *client, char *command)
{
	(void)client;
	(void)command;
	dprintf(client->client_fd, commands_infos[4]);
}