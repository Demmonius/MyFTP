/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Main client C file
*/

#include "client.h"
#include "server.h"

char	*get_command(t_client *client)
{
	char *line = NULL;
	size_t size;
	FILE* fp = fdopen(client->client_fd, "r");

	if (getline(&line, &size, fp) == -1) {
		close(client->client_fd);
		return NULL;
	}
	for (int i = 0; line[i]; i++)
		if (line[i] == '\r' || line[i] == '\n')
			line[i] = '\0';
	return line;
}

int    handle_client(t_client *client)
{
	char *command = NULL;

	client->is_log = false;
	client->have_to_quit = false;
	if (dprintf(client->client_fd, commands_infos[5]) == 0)
		return 84;
	while (!client->have_to_quit) {
		command = get_command(client);
		if (!command)
			return 0;
		manage_commands(command, client);
	}
	return 0;
}

int	manage_child(t_host *server)
{
	t_client	*new = make_client(server);
	pid_t		pid;

	new->client_fd = accept_connection(server->server_fd, new);
	if (new->client_fd == 84)
		return (84);
	pid = fork();
	if (pid == 0) {
		handle_client(new);
		close(new->client_fd);
		free(new);
		exit(0);
	}
	else if (pid > 0)
		close(new->client_fd);
	else if (pid == -1)
		return (84);
	return 0;
}

int main (int ac, char **av)
{
	t_host		*server;

	if (ac != 3)
		return (84);
	srand(time(NULL));
	server = listen_sock(init_host(av));
	while (42)
		manage_child(server);
	if (close(server->server_fd) == -1)
		return 84;
	return 0;
}