/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

#include "server.h"

void	commands_ls(t_client *client, char *command)
{
	printf("LS started\n");
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
                fprintf(stderr, "Error opening file --> %s", strerror(errno));
		return ;
        }
        if (fstat(fd, &file_stat) < 0)
        {
                fprintf(stderr, "Error fstat --> %s", strerror(errno));
		return ;
        }
        /* Sending file size */
        len = send(client->client_fd, file_size, sizeof(file_size), 0);
        if (len < 0)
        {
              fprintf(stderr, "Error on sending greetings --> %s", strerror(errno));
	      return ;
        }

        offset = 0;
        remain_data = file_stat.st_size;
        /* Sending file data */
        while (((sent_bytes = sendfile(client->client_fd, fd, &offset, BUFSIZ)) > 0) && (remain_data > 0))
        {
                remain_data -= sent_bytes;
        }
}