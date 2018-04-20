/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

#include "server.h"

void	commands_list(t_client *client, char *command)
{
	if (dup2(client->client_fd, 1) == -1) {
		fprintf(stderr, "Dup2 failed\n");
		return ;
	}
	if (execl("/bin/ls", "/bin/ls", "-l", client->path, NULL) == -1) {
		fprintf(stderr, "Execl failed\n");
		return ;
	}
}

void	commands_pwd(t_client *client, char *command)
{
	char	cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		write(client->client_fd, cwd, strlen(cwd));
		write(client->client_fd, "\n", 1);
	}
	else
		write(2, "Error while write cwd on client\n", strlen("Error while write cwd on client\n"));
}

void commands_quit(t_client *client, char *command)
{
	client->have_to_quit = true;
}

void commands_retr(t_client *client, char *command)
{
	char *arg = parse_command(command, ' ', 0);
	struct stat file_stat;
	ssize_t len;
	int peer_socket;
	int fd;
	off_t offset;
	char file_size[256];
	int remain_data;
	int sent_bytes = 0;

	fd = open(arg, O_RDONLY);
        if (fd == -1)
        {
                fprintf(stderr, "Error opening file --> %s\n", strerror(errno));
		return ;
        }
        if (fstat(fd, &file_stat) < 0)
        {
                fprintf(stderr, "Error fstat --> %s\n", strerror(errno));
		return ;
        }
}

void commands_user(t_client *client, char *command)
{
	parse_command(command, ' ', 1);
	client->is_log = true;
}