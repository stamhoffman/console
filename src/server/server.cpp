#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <iostream>

#include <thread>

int client_connect();
int client_task(int sd);
int execute_command(std::array<char, 1000> prog_name,
                    std::array<char, 1000> prog_key, int client_socket);

int main(int argc, char **argv) {
#define ps struct sockaddr
  const int PORT = 54321; // 54321

  int list_socket, client_socket;

  list_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (list_socket == -1) {
    std::cout << "Error socket():" << strerror(errno) << "\n";
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
    std::cout << "Error bind():" << strerror(errno) << "\n";
    close(list_socket);
    return -1;
  }

  if ((listen(list_socket, 3)) == -1) {
    std::cout << "Error listen():" << strerror(errno) << "\n";
    close(list_socket);
    return -1;
  }

  while (1) {
    socklen_t length = sizeof(client_addr);
    std::cout << "start accept" << '\n';
    client_socket = accept(list_socket, (ps *)&client_addr, &length);
    if (client_socket == -1) {
      std::cout << "Errorr accept():" << strerror(errno) << "\n";
      close(list_socket);
      return -1;
    }

    char addr_clients[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &(client_addr.sin_addr), addr_clients, INET_ADDRSTRLEN);
    std::cout << "connection from:" << addr_clients << "\n";

    int p_pid;
    p_pid = fork();
    if (p_pid == -1) {
      std::cout << "Error fork()" << strerror(errno) << std::endl;
      close(client_socket);
      return -1;
    } else if (p_pid == 0) { /* message */
      client_task(client_socket);
    }
  }

  close(list_socket);
  return 1;
}

int client_task(int client_socket) {
  int read_byte = 0;
  std::array<char, 1000> read_buff = {'\0'};
  std::array<char, 1000> prog_name = {'\0'};
  std::array<char, 1000> prog_key = {'\0'};
  std::array<char, 1000>::iterator rb_itr = read_buff.begin();
  std::array<char, 1000>::iterator pn_itr = prog_name.begin();
  std::array<char, 1000>::iterator key_itr = prog_key.begin();
  std::cout << "client start" << '\n';

  while (1) {
    read_buff.fill('\0');
    prog_name.fill('\0');
    prog_key.fill('\0');
    rb_itr = read_buff.begin();
    pn_itr = prog_name.begin();
    key_itr = prog_key.begin();

    read_byte = 0;
    read_byte = read(client_socket, (void *)read_buff.data(), read_buff.size());

    if (read_byte > 1) {
      while ((*rb_itr != ' ') && (rb_itr != read_buff.end())) {
        *pn_itr = *rb_itr;
        rb_itr++;
        pn_itr++;
      }

      if (rb_itr != read_buff.end()) {
        rb_itr++;
        while (rb_itr != read_buff.end()) {
          *key_itr = *rb_itr;
          key_itr++;
          rb_itr++;
        }
      }

      execute_command(prog_name, prog_key, client_socket);
    } else {
      return -1;
    }
  }
  close(client_socket);
  return 0;
}

int execute_command(std::array<char, 1000> prog_name,
                    std::array<char, 1000> prog_key, int client_socket) {
  int p_pid;
  p_pid = fork();
  if (p_pid == -1) {
    std::cout << "Error fork()" << strerror(errno) << std::endl;
    return -1;
  } else if (p_pid == 0) {
    dup2(client_socket, 1);

    if (prog_key[0] == '\0') {
      execlp(prog_name.data(), prog_name.data(), NULL);
    } else {
      execlp(prog_name.data(), prog_name.data(), prog_key.data(), NULL);
    }
  }
  return 1;
}
