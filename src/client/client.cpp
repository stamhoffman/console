#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#define pointer_adrr const struct sockaddr

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("Ошибка в формате команды, не введен адрес сервера\n");
		printf("Используйте ключ -h для получения справки \n");
		return -1;
	}

	const char helpstr[3] = {'-','h','\0'};

  if(strncmp(argv[1], helpstr, 2) == 0)
	{
		printf("формат команды ./client xxx.xxx.xxx.xxx\n Например ./client 127.1.1.1\n");
		return -1;
	}

	int socket_descriptor;

	if((socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("Error socket():%s\n", strerror(errno));
		return -1;
	}

	struct sockaddr_in servaddr_options;

	memset(&servaddr_options, 0 ,sizeof(servaddr_options));

	servaddr_options. sin_family = AF_INET;
	servaddr_options. sin_port = htons(54321);

	if(inet_pton(AF_INET, argv[1], &servaddr_options.sin_addr) == -1)
	{
		printf("Error inet_pton():%s\n", strerror(errno));
		return -1;
	}

	connect(socket_descriptor, (pointer_adrr *)&servaddr_options, sizeof(servaddr_options));

	#define MAXLINE 50
	char buffer[MAXLINE];

	int n;

	while((n = read(socket_descriptor, buffer, MAXLINE)) > 0)
	{

		buffer[n] = 0;

		if(fputs(buffer, stdout) == EOF)
		{
			printf("END SEND%s\n",strerror(errno));
		}
	}

	close(socket_descriptor);

	return 0;
}
