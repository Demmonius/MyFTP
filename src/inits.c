/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Main client C file
*/

#include "client.h"
#include "server.h"

int	accept_connection(int fd, t_client *client)
{
	int new_fd  = accept(fd, (struct sockaddr *) &client->s_in_client,
			&client->s_in_size);

	if (new_fd == -1)
		return 84;
	return (new_fd);
}

int	make_socket(int *port)
{
	struct protoent *pe = getprotobyname("TCP");
	int fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	int p2;
	struct sockaddr_in	s_in;

	do {
	p2 = rand() % 255;
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons((255 * 256) + p2);
	s_in.sin_addr.s_addr = INADDR_ANY;

	} while (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1);
	if (listen(fd, 1) == -1) {
		perror("Listen: ");
		return 84;
	}
	*port = (255 * 256) + p2;
	return fd;
}

t_client	*make_client(t_host *server)
{
	t_client	*client = malloc(sizeof(t_client));

	if (client == NULL)
		return NULL;
	client->path = strdup("/");
	client->base_path = server->path;
	client->s_in_size = sizeof(client->s_in_client);
	client->is_log = false;
	client->second_fd = -1;
	client->client_ip = NULL;
	client->client_port = -1;
	client->client_status = UNSET;
	return client;
}

t_host	*init_host(char **av)
{
	t_host		*server = malloc(sizeof(t_host));

	server->port = atoi(av[1]);
	server->path = av[2];
	server->pe = getprotobyname("TCP");
	server->s_in.sin_family = AF_INET;
	server->s_in.sin_port = htons(server->port);
	server->s_in.sin_addr.s_addr = INADDR_ANY;
	if (!server->pe)
		return NULL;
	server->server_fd = socket(AF_INET, SOCK_STREAM, server->pe->p_proto);
	if (server->server_fd == -1)
		return NULL;
	if (bind(server->server_fd, (const struct sockaddr *)&server->s_in,
		sizeof(server->s_in))) {
		return NULL;
	}
	return server;
}

t_host	*listen_sock(t_host *server)
{
	if (listen(server->server_fd, 42) == -1)
		return NULL;
	return server;
}