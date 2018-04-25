/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

#define _GNU_SOURCE
#include "server.h"

void	commands_list(t_client *client, char *command)
{
	const char	*const cmd = " ls -l %s%s | sed 1d";
	const int	save = dup(1);
	char		*full_cmd;

	if (client->client_status == UNSET) {
		dprintf(client->client_fd, commands_infos[14]);
		return ;
	}
	dprintf(client->client_fd, commands_infos[2]);
	client->second_fd = (client->client_status == PASV ? accept_connection(client->second_fd, client) : connect_to_client(client));
	if (client->second_fd == 84) {
		perror("Fd accept or connection: ");
		return ;
	}
	if (dup2(client->second_fd, 1) == -1) {
		fprintf(stderr, "Dup2 failed\n");
		return ;
	}
	asprintf(&full_cmd, cmd, client->base_path, client->path);
	if (system(full_cmd) == -1) {
		dup2(save, 1);
		close(client->second_fd);
		return ;
	}
	dup2(save, 1);
	close(client->second_fd);
	dprintf(client->client_fd, commands_infos[7]);
	client->second_fd = -1;
	client->client_status = UNSET;
}

void	commands_pwd(t_client *client, char *command)
{
	command = command;
	client = client;
	dprintf(client->client_fd, "257 \"");
	dprintf(client->client_fd, client->path);
	dprintf(client->client_fd, "\"\r\n");
}

void commands_quit(t_client *client, char *command)
{
	command = command;
	client->have_to_quit = true;
}

void commands_retr(t_client *client, char *command)
{
	char *arg = parse_command(command, ' ', 1);
	int c;
	FILE *file;
	char	*filename;

	if (client->client_status == UNSET) {
		dprintf(client->client_fd, commands_infos[14]);
		return ;
	}
	dprintf(client->client_fd, commands_infos[2]);
	client->second_fd = (client->client_status == PASV ? accept_connection(client->second_fd, client) : connect_to_client(client));
	if (client->second_fd == 84) {
		perror("Fd accept or connection: ");
		return ;
	}
	asprintf(&filename, "%s%s%s", client->base_path, client->path, arg);
	file = fopen(filename, "r");
	if (file) {
		do {
			c = getc(file);
			if (c == EOF)
				break ;
			write(client->second_fd, &c, 1);
		} while (42);
	        putchar(c);
	    fclose(file);
	}
	else {
		dprintf(client->client_fd, commands_infos[16]);
		printf("Tried access to |%s|\n", filename);
	}
	free(filename);
	close(client->second_fd);
	dprintf(client->client_fd, commands_infos[7]);
	client->second_fd = -1;
	client->client_status = UNSET;
}

void commands_user(t_client *client, char *command)
{
	client->user = parse_command(command, ' ', 1);
	dprintf(client->client_fd, "331 Please specify the password\r\n");
}

void commands_pass(t_client *client, char *command)
{
	command = command;
	if (!client->user)
		return ;
	if (strcmp(client->user, "Anonymous") == 0) {
		client->is_log = true;
		dprintf(client->client_fd, "230 Login seccessful\n");
	}
	else
		dprintf(client->client_fd, "530 Login incorrect\n");
}

void commands_cwd(t_client *client, char *command)
{
	char	*dir = parse_command(command, ' ', 1);
	char	*tmp = malloc(sizeof(char) * (strlen(client->path) + strlen(dir) + 1));

	strcpy(tmp, client->path);
	strcat(tmp, dir);
	free(client->path);
	if (dir[strlen(dir)] != '/')
		tmp[strlen(tmp)] = '/';
	client->path = tmp;
	dprintf(client->client_fd, "%s\n", commands_infos[10]);
}

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
	fflush(stdout);
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
	asprintf(&client->client_ip, "%s.%s.%s.%s", ips[0], ips[1], ips[2], ips[3]);
	client->client_port = (atoi(ps[0]) * 256) + atoi(ps[1]);
	dprintf(client->client_fd, commands_infos[3]);
	client->client_status = ACTIV;
	for (int i = 0; i < 4; i++)
		free(ips[i]);
	for (int i = 0; i < 2; i++)
		free(ps[i]);
}

char	*read_file(char *filename)
{
	FILE *file = fopen(filename, "r");
	char *buff;
	char c;
	int i = 0;

	if (file) {
		do {
			c = getc(file);
			buff = realloc(buff, i + 1);
			buff[i] = c;
			if (c == EOF)
				break ;
			i++;
		} while (42);
	        putchar(c);
		fclose(file);
		buff[i] = '\0';
	}
	else
		return NULL;
	return buff;
}

void commands_stor(t_client *client, char *command)
{
	char *filename;
	char *arg;

	if (client->client_status == UNSET) {
		dprintf(client->client_fd, commands_infos[14]);
		return ;
	}
	dprintf(client->client_fd, commands_infos[2]);
	client->second_fd = (client->client_status == PASV ? accept_connection(client->second_fd, client) : connect_to_client(client));
	if (client->second_fd == 84) {
		perror("Fd accept or connection: ");
		return ;
	}
	arg = parse_command(command, ' ', 1);
	asprintf(&filename, "%s%s%s", client->base_path, client->path, arg);
	char *buff = read_file(filename);
	if (!buff) {
		perror("Read file: ");
		return ;
	}
	printf(buff);
	free(filename);
}