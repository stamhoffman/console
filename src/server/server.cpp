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
#define ps struct sockaddr
#define PORT 54321

  int list_socket, client_socket;

  list_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (list_socket == -1) {
    printf("Error socket():%s\n", strerror(errno));
    return -1;
  }

  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  struct sockaddr_in client_addr;
  memset(&client_addr, 0, sizeof(client_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if ((bind(list_socket, (ps *)&serv_addr, sizeof(serv_addr))) == -1) {
    printf("Error bind():%s\n", strerror(errno));
    return -1;
  }

  if ((listen(list_socket, 3)) == -1) {
    printf("Error listen()%s\n", strerror(errno));
  }

  for (;;) {
    socklen_t length = sizeof(client_addr);

    client_socket = accept(list_socket, (ps *)&client_addr, &length);
    if (client_socket == -1) {
      printf("Errorr accept():%s\n", strerror(errno));
    }

    char addr_clients[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &(client_addr.sin_addr), addr_clients, INET_ADDRSTRLEN);
    printf("connection from: %s\n", addr_clients);

    // std::thread thr(client_connect, client_socket);
    // thr.detach();

    std::string read_buffer;

    //while ((read(client_socket,(void *)&read_buffer, sizeof(read_buffer))) > 0) {
    //  std::cout << read_buffer;
      // send(client_socket, (const void *)&read_buffer, sizeof(read_buffer),
      // 0);
    //}
  }

  close(client_socket);
  close(list_socket);

  return 0;
}

int client_connect(int client_socket) {
  std::cout << "/* client_connect start */" << '\n';

  std::string read_buffer;

  while ((read(client_socket, &read_buffer, sizeof(read_buffer))) > 0) {
    std::cout << read_buffer;
    send(client_socket, (const void *)&read_buffer, sizeof(read_buffer), 0);
  }
  close(client_socket);

  return 0;
}
