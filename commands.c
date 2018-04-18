/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

#include "server.h"

void	commands_ls(t_client *client)
{
	printf("LS started\n");
}

void (*const commands_func[])(t_client *) = {
	commands_ls,
};

const char commands_name[][64] = {
	"ls"
};

int manage_commands(char *command, t_client *client)
{
	printf("Command: %s\n", command);
	for (int i = 0; i < LEN_FUNCS; i++) {
		printf("%s => %s\n", command, commands_name[i]);
		if (strcmp(commands_name[i], command) == 0)
			commands_func[i](client);
	}
	return (0);
}