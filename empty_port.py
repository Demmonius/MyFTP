#!/bin/env python3

from socket import socket, AF_INET, SOCK_STREAM
from contextlib import closing

with closing(socket(AF_INET, SOCK_STREAM)) as sock:
	sock.bind(('', 0))
	print(sock.getsockname()[1])
