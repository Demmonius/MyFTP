/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

#include "server.h"

void	commands_list(t_client *client)
{
	DIR *rep = NULL;
	struct dirent *file = NULL;

	write(1, client->path, strlen(client->path));
	rep = opendir(client->path);
	if (rep == NULL)
	  return ;
	while ((file = readdir(rep)) != NULL) {
	  write(client->client_fd, file->d_name, strlen(file->d_name));
	  write(client->client_fd, "\t", 1);
	}
	write(client->client_fd, "\n", 1);
	if (closedir(rep) == -1)
	        return ;
}

void	commands_pwd(t_client *client)
{
	char	cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		write(client->client_fd, cwd, strlen(cwd));
		write(client->client_fd, "\n", 1);
	}
	else
		write(2, "Error while write cwd on client\n", strlen("Error while write cwd on client\n"));
}

void commands_quit(t_client *client)
{
	(t_client *)client;
	client->have_to_quit = true;
}