#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <iostream>

#include <thread>

int client_task(int sd, std::string prog);

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

    int p_pid;
    p_pid = fork();
    if (p_pid == -1) {
      std::cout << "Error fork()" << strerror(errno) << std::endl;
    } else if (p_pid == 0) {
      while (1) {
        std::string prog;
        if(read(client_socket, (void *)prog.data(), prog.size()) > 0);
        std::cout << prog << std::endl;

        std::thread new_client(client_task, client_socket, prog);
        new_client.detach();
        char send_str[5000] = {"\0"};
        fscanf(stdout, "%s", send_str);
        std::cout << "cout" << send_str << std::endl;
        send(client_socket, (const void *)send_str, sizeof(send_str), 0);
      }
    }
  }
  close(list_socket);
  close(client_socket);
  return 0;
}

int client_task(int client_socket, std::string prog) {

  std::string path;
  path = "/bin/ls";
  std::cout << "start new_client" << std::endl;
  execl("/bin/ls", "-l", NULL);

  return 0;
}
