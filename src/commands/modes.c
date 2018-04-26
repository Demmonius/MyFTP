/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

#define _GNU_SOURCE
#include "server.h"

void commands_pasv(t_client *client, char *command)
{
	int	port = -1;

	client->second_fd = make_socket(&port);
	command = command;
	port -= (256 * 255);
	dprintf(client->client_fd, commands_infos[8], "127,0,0,1", port);
	client->client_status = PASV;
}

int connect_to_client(t_client *client)
{
	struct protoent *pe = getprotobyname("TCP");
	int fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	struct sockaddr_in	s_in;

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(client->client_port);
	s_in.sin_addr.s_addr = inet_addr(client->client_ip);
	if (connect(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1) {
		perror("Connect: ");
		return 84;
	}
	return fd;
}

void make_port(t_client *client, char **ips, char **ps)
{
	asprintf(&client->client_ip, "%s.%s.%s.%s", ips[0], ips[1],
		ips[2], ips[3]);
	client->client_port = (atoi(ps[0]) * 256) + atoi(ps[1]);
	dprintf(client->client_fd, commands_infos[3]);
	client->client_status = ACTIV;
}

void commands_port(t_client *client, char *command)
{
	char	*arg = parse_command(command, ' ', 1);
	char	*ips[] = {
		parse_command(arg, ',', 0),
		parse_command(arg, ',', 1),
		parse_command(arg, ',', 2),
		parse_command(arg, ',', 3)
	};
	char	*ps[] = {
		parse_command(arg, ',', 4),
		parse_command(arg, ',', 5)
	};

	if (!client->client_ip)
		free(client->client_ip);
	make_port(client, ips, ps);
	for (int i = 0; i < 4; i++)
		free(ips[i]);
	for (int i = 0; i < 2; i++)
		free(ps[i]);
	free(arg);
}