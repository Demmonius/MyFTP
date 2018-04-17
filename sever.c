/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Main server C file
*/

#include "server.h"

int main()
{
    t_client *client = malloc(sizeof(t_client));
    client->port = 8080;
    client->ip = "127.0.0.1";
    client->pe = getprotobyname("TCP");
    if (!client->pe)
        return 84;
    client->client_fd = socket(AF_INET, SOCK_STREAM, client->pe->p_proto);
    if (client->client_fd == -1)
        return 84;
    client->s_in_client.sin_family = AF_INET;
    client->s_in_client.sin_port = htons(client->port);
    client->s_in_client.sin_addr.s_addr = inet_addr(client->ip);
    if (connect(client->client_fd, (struct sockaddr *) &client->s_in_client, sizeof(client->s_in_client)) == -1)
        return 84;
    write(1, "Salut\n", strlen("salut"));
    if (close(client->client_fd) == -1)
        return 84;
    return 0;
};