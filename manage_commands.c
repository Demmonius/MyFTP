/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

#include "server.h"

void	commands_list(t_client *client, char *command)
{
	pid_t	pid = fork();
	int	status;

	command = command;
  	if (pid == 0) {
		if (dup2(client->client_fd, 1) == -1) {
			fprintf(stderr, "Dup2 failed\n");
			return ;
		}
		if (execl("/bin/ls", "/bin/ls", "-l",
			strcat(client->base_path, client->path), NULL) == -1) {
			fprintf(stderr, "Execl failed\n");
			return ;
		}
	}
  	else if (pid > 0)
		wait(&status);
	else
		return ;
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
	char *arg = parse_command(command, ' ', 0);
	int fd;

	fd = open(arg, O_RDONLY);
        if (fd == -1)
        {
                fprintf(stderr, "Error opening file --> %s\n", strerror(errno));
		return ;
        }
	dprintf(client->client_fd, "Hello, pls pass later !\r\n");
	close(fd);
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
	printf("%s\n", client->user);
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