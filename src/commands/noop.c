/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

/*!
 * @brief Manage noop command
 * 
 * @file noop.c
 * @author your name
 * @date 09-05-2018
 */
#define _GNU_SOURCE
#include "server.h"

/*!
 * @brief Noop command
 * 
 * @param client Client struct
 * @param command command send
 */
void commands_noop(t_client *client, char *command)
{
	(void)client;
	(void)command;
	dprintf(client->client_fd, commands_infos[3]);
}