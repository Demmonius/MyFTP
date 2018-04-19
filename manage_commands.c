/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

#include "server.h"

void	commands_list(t_client *client, char *command)
{
	DIR *rep = NULL;
	struct dirent *file = NULL;

	write(1, client->path, strlen(client->path));
	rep = opendir(client->path);
	if (rep == NULL)
	  return ;
	while ((file = readdir(rep)) != NULL) {
	  write(client->client_fd, file->d_name, strlen(file->d_name));
	  write(client->client_fd, "\t", 1);
	}
	write(client->client_fd, "\n", 1);
	if (closedir(rep) == -1)
	        return ;
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