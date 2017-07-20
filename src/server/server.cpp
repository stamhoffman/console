#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>

int client_connect(int);

int main(int argc, char **argv) {
#define pointer_socket struct sockaddr
#define PORT 54321

  int listening_socket, client_socket;

  if ((listening_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    printf("Error socket():%s\n", strerror(errno));
    return -1;
  }

  struct sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  struct sockaddr_in client_address;
  memset(&client_address, 0, sizeof(client_address));

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);

  if ((bind(listening_socket, (pointer_socket *)&server_address,
            sizeof(server_address))) == -1) {
    printf("Error bind():%s\n", strerror(errno));
    return -1;
  }

  if ((listen(listening_socket, 3)) == -1) {
    printf("Error listen()%s\n", strerror(errno));
  }

  while (1) {
    socklen_t length = sizeof(client_address);

    if ((client_socket = accept(listening_socket,
                                (pointer_socket *)&client_address, &length)) ==
        -1) {
      printf("Errorr accept():%s\n", strerror(errno));
    }

    char addr_clients[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &(client_address.sin_addr), addr_clients,
              INET_ADDRSTRLEN);
    printf("connection from: %s\n", addr_clients);

    std::thread thr(client_connect, std::ref(client_socket));
    thr.detach();
  }

  close(listening_socket);
  close(client_socket);

  return 0;
}

int client_connect(int client_socket) {
  std::cout << "/* client_connect start */" << '\n';

#define MAXLINE 50
  char buffer[MAXLINE];
  int n;

  while (1) {
    while ((n = read(client_socket, buffer, MAXLINE)) > 0) {
      std::cout << buffer << std::endl;

      if (strncmp(buffer, "ls", 2) == 1) {
        write(client_socket, "buffer", sizeof("buffer"));
      }

      if (strncmp(buffer, "exit", 4) == 1) {
        close(client_socket);
        return 0;
      }
    }
  }
}
