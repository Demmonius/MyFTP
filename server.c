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

	if ((getline(&line, &size, fp) == -1))
		return NULL;
	else {
		line[strlen(line) - 1] = 0;
		return line;
	}
}

int    handle_client(t_client *client)
{
	char *command = NULL;
	pid_t	pid;
	int	status;

	client->is_log = false;
	client->have_to_quit = false;
	if (write(client->client_fd, commands_infos[5], strlen(commands_infos[5])) == -1 ||
		write(client->client_fd, "\n", 1) == -1)
		return 84;
	while (!client->have_to_quit) {
		command = get_command(client);
		if (!command)
			break ;
		pid = fork();
  		if (pid == 0)
			manage_commands(command, client);
  		else
	  		wait(&status);
		free(command);
	}
	return 0;
}

int main (int ac, char **av)
{
	t_client    *client = malloc(sizeof(t_client));
	t_host    *server = malloc(sizeof(t_host));

	if (ac != 3)
		return (84);
	server->port = atoi(av[1]);
	server->path = av[2];
	client->path = av[2];
	client->s_in_size = sizeof(client->s_in_client);
	server->pe = getprotobyname("TCP");
	server->s_in.sin_family = AF_INET;
	server->s_in.sin_port = htons(server->port);
	server->s_in.sin_addr.s_addr = INADDR_ANY;
	if (!server->pe)
		return 84;
	server->server_fd = socket(AF_INET, SOCK_STREAM, server->pe->p_proto);
	if (server->server_fd == -1)
		return 84;
	if (bind(server->server_fd, (const struct sockaddr *)&server->s_in, sizeof(server->s_in)))
	{
		if (close(server->server_fd) == -1)
			write(2, "Can't close bind\n", strlen("Can't close bind\n"));
		return 84;
	}
	if (listen(server->server_fd, 42) == -1)
	{
		if (close(server->server_fd) == -1)
			write(2, "Can't close listen\n", strlen("Can't close listen\n"));
		return 84;
	}
	client->client_fd = accept(server->server_fd, (struct sockaddr *) &client->s_in_client, &client->s_in_size);
	if (client->client_fd == -1)
	{
		close(server->server_fd);
		return 84;
	}
	client->client_ip = inet_ntoa(client->s_in_client.sin_addr);
	if (handle_client(client) == 84)
		return 84;
	if (close(server->server_fd) == -1 || close(client->client_fd) == -1)
		return 84;
	return 0;
}