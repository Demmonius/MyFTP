/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

#include "server.h"

void (*const commands_func[])(t_client *) = {
	commands_list,
	commands_quit,
	commands_pwd,
};

const char commands_name[][64] = {
	"list",
	"quit",
	"pwd"
};

int manage_commands(char *command, t_client *client)
{
	for (int i = 0; i < LEN_FUNCS; i++) {
		if (strcmp(commands_name[i], command) == 0)
			commands_func[i](client);
	}
	return (0);
}