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
		manage_commands(command, client);
	}
	return 0;
}

int	accept_connection(t_host *server, t_client *client)
{
	client->client_fd = accept(server->server_fd, (struct sockaddr *) &client->s_in_client, &client->s_in_size);
	if (client->client_fd == -1)
	{
		close(server->server_fd);
		return 84;
	}
	return (0);
}

/*pid_t	make_socket(t_host *server, int *port)
{
	int fd = socket(AF_INET, SOCK_STREAM, server->pe->p_proto);
	struct sockaddr_in	s_in;
	int	p = (!port ? *port : )

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons();
	s_in.sin_addr.s_addr = INADDR_ANY;
	if (fd == -1)
		return -1;
	if (bind(fd, (const struct sockaddr *)&server->s_in, sizeof(server->s_in)))
	{
		if (close(fd) == -1)
			write(2, "Can't close bind\n", strlen("Can't close bind\n"));
		return 84;
	}
	if (listen(fd, 42) == -1)
	{
		if (close(server->server_fd) == -1)
			write(2, "Can't close listen\n", strlen("Can't close listen\n"));
		return 84;
	}
	return fd;
}*/

t_client	*make_client(t_host *server)
{
	t_client	*client = malloc(sizeof(t_client));

	if (client == NULL)
		return NULL;
	client->path = server->path;
	client->s_in_size = sizeof(client->s_in_client);
	client->is_log = false;
}

int main (int ac, char **av)
{
	t_client	*client = malloc(sizeof(t_client));
	t_host		*server = malloc(sizeof(t_host));
	pid_t		pid;

	if (ac != 3)
		return (84);
	server->port = atoi(av[1]);
	server->path = av[2];
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
	while (42) {
		t_client *new = make_client(server);
		if (accept_connection(server, new) == 84)
			return (84);
		pid = fork();
		if (pid == 0)
			handle_client(new);
		else if (pid > 0)
			close(new->client_fd);
		else if (pid == -1)
			return (84);
	}
	if (close(server->server_fd) == -1 || close(client->client_fd) == -1)
		return 84;
	return 0;
}