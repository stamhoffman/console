#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

int main(int argc, char **argv)
{
	#define pointer_adrr const struct sockaddr
	#define PORT 54321

	if(argc < 2)
	{
		std::cout << "Ошибка в формате команды, не введен адрес сервера\n"<< std::endl;
		std::cout << "Используйте ключ -h для получения справки \n" << std::endl;
		return -1;
	}

	const char helpstr[3] = "-h";

  if(strncmp(argv[1], helpstr, 2) == 0)
	{
		std::cout<<"Формат команды "<<argv[0]<<" 127.1.1.1"<<std::endl;
		return 0;
	}

	int socket_descriptor;

	if((socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		std::cout << "Error socket():" <<strerror(errno) << std::endl;
		return -1;
	}

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0 ,sizeof(serv_addr));

	serv_addr. sin_family = AF_INET;
	serv_addr. sin_port = htons(PORT);

	if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) == -1)
	{
		std::cout << "Error inet_pton():"<< strerror(errno) << std::endl;
		return -1;
	}

	if(connect(socket_descriptor, (pointer_adrr *)&serv_addr, sizeof(serv_addr)) == -1)
	{
		std::cout << "Error connect:" << strerror(errno) << std::endl;
	}

	#define MAXLINE 50
	char buffer[MAXLINE];

	while(1)
	{
		scanf("%s\n",buffer);

		if(strcmp(buffer,"exit") == 1)
		{
			close(socket_descriptor);
			break;
		}
		write(socket_descriptor,buffer, sizeof(buffer));
	}

	return 0;
}
