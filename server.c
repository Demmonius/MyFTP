/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Main client C file
*/

/*!
 * @file server.c
 */

#include "client.h"
#include "server.h"

/*!
 * @brief Get command input from the client socket
 * 
 * @param client Use the client to open his file descriptor
 * @return char* Return the command with a \0 at the end
 */

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

/*!
 * @brief Function called when a client is accepted
 * 
 * @param client Pointer to the new client
 * @return int Return status
 */
int    handle_client(t_client *client)
{
	char *command = NULL;

	client->is_log = false;
	client->have_to_quit = false;
	if (write(client->client_fd, commands_infos[5], strlen(commands_infos[5])) == -1 ||
		write(client->client_fd, "\n", 1) == -1)
		return 84;
	while (!client->have_to_quit) {
		command = get_command(client);
		if (!command)
			return 0;
		manage_commands(command, client);
	}
	return 0;
}


/*!
 * @brief Manage accept connection
 * 
 * @param server Host struct to accept connection
 * @param client Setup new FD to the client
 * @return int Return status
 */
int	accept_connection(int fd, t_client *client)
{
	int new_fd  = accept(fd, (struct sockaddr *) &client->s_in_client, &client->s_in_size);

	if (new_fd == -1)
		return 84;
	return (new_fd);
}

pid_t	make_socket(int *port)
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

	} while(bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1);
	if (listen(fd, 42) == -1)
		return 84;
	*port = (255 * 256) + p2;
	return fd;
}

/*!
 * @brief This function alloc a t_client struct and init it
 * @param server
 * @see t_client
 * @return t_client*
 */
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
	return client;
}

/*!
 * @brief Main function that call forks, etc...
 * 
 * @param ac To check len of args
 * @param av Use to define port and Anonymous home's directory
 * @return int Return status
 */
int main (int ac, char **av)
{
	t_client	*client = malloc(sizeof(t_client));
	t_host		*server = malloc(sizeof(t_host));
	pid_t		pid;

	if (ac != 3)
		return (84);
	srand(time(NULL));
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
		new->client_fd = accept_connection(server->server_fd, new);
		if (new->client_fd == 84)
			return (84);
		pid = fork();
		if (pid == 0) {
			handle_client(new);
			close(new->client_fd);
			free(new);
			return 0;
		}
		else if (pid > 0)
			close(new->client_fd);
		else if (pid == -1)
			return (84);
	}
	if (close(server->server_fd) == -1 || close(client->client_fd) == -1)
		return 84;
	return 0;
}