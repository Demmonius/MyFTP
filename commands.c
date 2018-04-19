/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

#include "server.h"

void (*const commands_func[])(t_client *, char *) = {
	commands_ls,
	commands_quit,
	commands_pwd,
	commands_retr,
};

const char commands_name[][64] = {
	"list",
	"quit",
	"pwd",
	"retr"
};

char	*parse_command(char *command, char c, int nb)
{
	int count = 0;
	int size = 2;
	char *new = malloc(sizeof(char) * size);

	while (command && nb > count) {
		if (*command == c)
			count++;
		command++;
	}
	for (int i = 0; *command && *command != c; i++) {
		new[i] = *command;
		new = realloc(new, sizeof(char) * ++size);
		command++;
	}
	new[size - 2] = '\0';
	return new;
}

int manage_commands(char *command, t_client *client)
{
	char * new = parse_command(command, ' ', 0);

	for (int i = 0; i < LEN_FUNCS; i++) {
		if (strcmp(commands_name[i], new) == 0)
			commands_func[i](client, command);
	}
	free(new);
	return (0);
}