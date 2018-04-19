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

typedef struct			s_client
{
    char		*ip;
    char            	*path;
    int			client_fd;
    char		*client_ip;
    int			port;
    socklen_t		s_in_size;
    struct protoent	*pe;
    struct sockaddr_in	s_in_client;
    bool		have_to_quit;
    bool                is_log;
}    			t_client;

#endif /* !CLIENT_H_ */
