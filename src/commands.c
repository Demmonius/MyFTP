/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Command gestion C file
*/

#include "server.h"

void (*const commands_func[])(t_client *, char *) = {
	commands_list,
	commands_quit,
	commands_pwd,
	commands_retr,
	commands_user,
	commands_pass,
	commands_cwd,
	commands_pasv,
	commands_port,
	commands_stor,
	commands_help,
	
};

const char commands_name[][64] = {
	"list",
	"quit",
	"pwd",
	"retr",
	"user",
	"pass",
	"cwd",
	"pasv",
	"port",
	"stor",
	"help"
};

const char commands_infos[][256] = {
	"120 Service ready in nnn minutes.",
        "125 Data connection already open; transfer starting.",
        "150 File status okay; about to open data connection.\n",
        "200 Command okay.\n",
        "214 Help message.\n\
        On how to use the server or the meaning of a particular\n\
        non-standard command.  This reply is useful only to the\n\
        human user.\n",
        "220 Service ready for new user.\n",
        "221 Service closing control connection. \
            Logged out if appropriate.",
        "226 Directory send OK.\n",
        "227 Entering Passive Mode (%s,255,%d).\n",
        "230 User logged in, proceed.",
        "250 Requested file action okay, completed.",
        "257 %s created.",
        "331 User name okay, need password.",
        "332 Need account for login.",
	"425 Use PORT or PASV first.\n",
	"500 Unknown command.\n",
	"550 Failed to open file\n",
	"530 Please login with USER and PASS\n"
};

char *to_lowcase(char *str)
{
	for (int i = 0; str[i]; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
	}
	return (str);
}

int	c_count(char *str, char c)
{
	int n = 0;

	for(int i = 0; str[i]; i++)
		if (str[i] == c)
			n++;
	return n;
}

char	*parse_command(char *command, char c, int nb)
{
	int count = 0;
	int size = 2;
	char *new = malloc(sizeof(char) * size);

	if (c_count(command, c) < nb)
		return NULL;
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
	new[size - 1] = '\0';
	return new;
}

int manage_log(t_client *client, char *new, char *command)
{
	if (!client->is_log) {
		if (strcmp("user", new) == 0)
			commands_user(client, command);
		else if (strcmp("pass", new) == 0)
			commands_pass(client, command);
		else
			dprintf(client->client_fd, commands_infos[17]);
		return 1;
	}
	return 0;
}

int	manage_commands(char *command, t_client *client)
{
	char * new = to_lowcase(parse_command(command, ' ', 0));
	bool status = false;

	printf("[%d]: %s\n", client->client_fd, command);
	if (manage_log(client, new, command) == 1)
		return 84;
	for (int i = 0; i < LEN_FUNCS && status == 0; i++) {
		if (strcmp(commands_name[i], new) == 0) {
			commands_func[i](client, command);
			status = true;
		}
	}
	if (!status)
		dprintf(client->client_fd, commands_infos[15]);
	free(new);
	return (0);
}