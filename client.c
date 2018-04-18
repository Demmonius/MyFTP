/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Main server C file
*/

#include "server.h"

int	read_socket(t_client *client)
{
    char * line = NULL;
	size_t len = 0;
    ssize_t read;

    if (read = getline(&line, &len, stdin) == -1) {
        printf("No line\n");
    } else {
        printf("Réception d'une ligne de longueur %zu :\n", read);
        printf("%s", line);
    }

	if (line)
		free(line);
	return (0);
}

int main(int ac, char **av)
{
    t_client *client = malloc(sizeof(t_client));
    if (ac != 3)
        return 84;
    client->ip = av[1];
    client->port = atoi(av[2]);
    client->pe = getprotobyname("TCP");
    if (!client->pe)
        return 84;
    client->client_fd = socket(AF_INET, SOCK_STREAM, client->pe->p_proto);
    if (client->client_fd == -1)
        return 84;
    client->s_in_client.sin_family = AF_INET;
    client->s_in_client.sin_port = htons(client->port);
    client->s_in_client.sin_addr.s_addr = inet_addr(client->ip);
    if (connect(client->client_fd, (struct sockaddr *) &client->s_in_client, sizeof(client->s_in_client)) == -1) {
        write(2, "Can't connect\n", strlen("Can't connect\n"));
        if (close(client->client_fd) == -1)
            write(2, "Can't close\n", strlen("Can't close\n"));
        return 84;
    }
    read_socket(client);
    if (close(client->client_fd) == -1)
        return 84;
    return 0;
};