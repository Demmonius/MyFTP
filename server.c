/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Main client C file
*/

#include "client.h"
#include "server.h"

int    handle_client(t_client *client)
{
	static const char *const welcome = "Welcome, your IP address is: ";
	if (write(client->client_fd, welcome, strlen(welcome)) == -1 ||
		write(client->client_fd, client->client_ip, strlen(client->client_ip)) == -1 ||
		write(client->client_fd, "\n", 1) == -1)
		return 84;
    return 0;
}

int main (int ac, char **av)
{
	t_client    *client = malloc(sizeof(t_client));
	t_host    *server = malloc(sizeof(t_host));

	if (ac != 2)
		return (84);
	server->port = atoi(av[1]);
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
	write(1, client->client_ip, strlen(client->client_ip));
	if (handle_client(client) == 84)
	    return 84;
	if (close(server->server_fd) == -1 || close(client->client_fd) == -1)
	    return 84;
	return 0;
}