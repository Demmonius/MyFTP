/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Second main Header file
*/

/*!
 * @file client.h
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

/*!
 * @brief Typedef from s_client to t_client
 * @typedef t_client
 * @struct s_client
 * @brief Client data
 */
typedef struct			s_client
{
	char            	*path; //! Actual client PATH
	char			*base_path; //! Base from server
	int			second_fd; //! Second socket open
	int			client_fd; //! Client file descriptor
	char			*client_ip; //! Client IP address
	int			port; //! Actual port to use
	socklen_t		s_in_size; //! Connection struct
	struct protoent		*pe; //! Accept struct
	struct sockaddr_in	s_in_client; //! Socket struct
	bool			have_to_quit; //! Bool to know if user typed QUIT
	bool			is_log; //! Know if the user is login
	char			*user; //! Name of user use
}    			t_client;

#endif /* !CLIENT_H_ */
