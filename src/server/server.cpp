#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>

int client_task(int sd);
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

  while (1) {
    socklen_t length = sizeof(client_addr);

    client_socket = accept(list_socket, (ps *)&client_addr, &length);
    if (client_socket == -1) {
      printf("Errorr accept():%s\n", strerror(errno));
    }

    char addr_clients[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &(client_addr.sin_addr), addr_clients, INET_ADDRSTRLEN);
    printf("connection from: %s\n", addr_clients);
    std::thread new_client(client_task, client_socket);
    new_client.detach();
  }

  close(list_socket);
  close(client_socket);
  return 0;
}

int client_task(int client_sock) {
  std::array<char, 1024> read_buff = {'\0'};

  while (1) {
    while (read(client_sock, (void *)read_buff.data(), read_buff.size()) > 0) {
      for (auto arr : read_buff) {
        std::cout << arr;
      }
      std::cout << std::endl;
      read_buff = {'\0'};
    }
  }
  close(client_sock);
  return 0;
}
