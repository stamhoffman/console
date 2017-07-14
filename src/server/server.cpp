#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <iostream>

#define pointer_socket struct sockaddr
void 		new_client_connect(void);

int main(int argc, char **argv)
{
	int       socket_descriptor, socket_accept;
	socklen_t len;

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
	address_clienta.sin_port = htons(54321);
	address_clienta.sin_addr.s_addr = htonl(INADDR_ANY);

	if((bind(socket_descriptor, (pointer_socket *)&address_clienta, sizeof(address_clienta))) == -1)
	{
		printf("Error bind():%s\n", strerror(errno));
		return -1;
	}

	len = sizeof(socket_accept);
	char addr_clients[INET_ADDRSTRLEN];
	const char *res;
	len = sizeof(socket_accept);

	if((listen(socket_descriptor, 3)) == -1)
	{
		printf("Error listen()%s\n",strerror(errno));
	}

	while(1)
	{
		if((socket_accept = accept(socket_descriptor, (pointer_socket *)&address_accept, &len)) == -1)
		{
			printf("Errorr accept():%s\n",strerror(errno));
		}
		if((res = inet_ntop(AF_INET, (pointer_socket *)&address_accept,	addr_clients,
		sizeof(addr_clients))) == NULL)
		{
			printf("Error inet_ntop():%s\n",strerror(errno));
		}
		else printf("connection from: %s\n", addr_clients);


		std::thread new_client_connect();
		std::thread detach;

		}

	close(socket_descriptor);
	close(socket_accept);
	return 0;
}



void new_client_connect(void)
{
while(1)
{
	std::cout << "/* message */" << '\n';
}

}
