/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Second main Header file
*/

/*!
 * @brief Client header file
 * 
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
 * @brief Enumeration for the status of port
 * @enum port_status
 */
enum port_status {
	ACTIV, /**< Active mode, client_port is fill */
	PASV, /**< Passiv mode, client_port is fill */
	UNSET /**< No mode is set, client_port is empty */
};

/*!
 * @brief Client struct
 * @typedef t_client s_client
 * @struct s_client
 */
typedef struct			s_client
{
	char            	*path; /**< Actual path */
	char			*base_path; /**< Anonymous home path */
	int			second_fd; /**< File Descriptor for the second socket */
	char			*client_ip; /**< Actual IP address */
	int			client_port; /**< Port for active mode */
	enum port_status	client_status; /**< Status of client_port */
	int			client_fd; /**< Main File Descriptor */
	int			port; /**< Main port */
	socklen_t		s_in_size; /**< socklen struct */
	struct protoent		*pe; /**< protoent struct */
	struct sockaddr_in	s_in_client; /**< Socket struct */
	bool			have_to_quit; /**< To know if the client have to quit */
	bool			is_log; /**< To know if the client is connected */
	char			*user; /**< Name of the client */
}    			t_client;

#endif /* !CLIENT_H_ */
