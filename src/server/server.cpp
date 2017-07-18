#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <iostream>

int client_connect(int);

int main(int argc, char **argv)
{
	#define pointer_socket struct sockaddr
	#define PORT 54321


	int socket_descriptor, socket_accept;

	if((socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("Error socket():%s\n", strerror(errno));
		return -1;
	}

	struct sockaddr_in address_clienta;
	struct sockaddr_in address_accept;
	memset(&address_clienta, 0, sizeof(address_clienta));
	memset(&address_accept, 0, sizeof(address_accept));

	address_clienta.sin_family = AF_INET;
	address_clienta.sin_port = htons(PORT);
	address_clienta.sin_addr.s_addr = htonl(INADDR_ANY);

	if((bind(socket_descriptor, (pointer_socket *)&address_clienta, sizeof(address_clienta))) == -1)
	{
		printf("Error bind():%s\n", strerror(errno));
		return -1;
	}


	if((listen(socket_descriptor, 3)) == -1)
	{
		printf("Error listen()%s\n",strerror(errno));
	}

	while(1)
	{
		socklen_t len = sizeof(address_accept);

		if((socket_accept = accept(socket_descriptor, (pointer_socket *)&address_accept, &len)) == -1)
		{
			printf("Errorr accept():%s\n",strerror(errno));
		}

		char addr_clients[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(address_accept.sin_addr),addr_clients,INET_ADDRSTRLEN);
		printf("connection from: %s\n", addr_clients);

		std::thread thr(client_connect, std::ref(socket_accept));
	 	thr.detach();
		}

	close(socket_descriptor);
	close(socket_accept);

	return 0;
}

int client_connect(int socket_accept)
{
	std::cout << "/* client_connect start */" << '\n';

	#define MAXLINE 50
	char buffer[MAXLINE];
	int n;

	while(1)
	{
		while((n = read(socket_accept, buffer, MAXLINE)) > 0)
		{
			std::cout << buffer << std::endl;

			if(strncmp(buffer,"ls",2) == 1)
			{
				write(socket_accept, "buffer", sizeof("buffer"));
			}

			if(strncmp(buffer,"exit",4) == 1)
			{
				close(socket_accept);
				return 0;
			}
		}
	}

}
