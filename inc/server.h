/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Main Header file
*/

#ifndef SERVER_H_
	#define SERVER_H_
	
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "client.h"

typedef struct s_host
{
	struct protoent			*pe;
	struct sockaddr_in		s_in;
	int				port;
	int				server_fd;
}					t_host;

#endif /* !SERVER_H_ */
