/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Second main Header file
*/

#ifndef CLIENT_H_
	#define CLIENT_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>


enum port_status {
	ACTIV,
	PASV,
	UNSET
};

typedef struct			s_client
{
	char            	*path;
	char			*base_path;
	int			second_fd;
	char			*client_ip;
	int			client_port;
	enum port_status	client_status;
	int			client_fd;
	int			port;
	socklen_t		s_in_size;
	struct protoent		*pe;
	struct sockaddr_in	s_in_client;
	bool			have_to_quit;
	bool			is_log;
	char			*user;
}    			t_client;

#endif /* !CLIENT_H_ */
