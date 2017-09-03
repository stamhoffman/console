
#include "config.h"

int execute_command(std::vector<char*> &user_string_pointer, int &client_socket);

int client_task(int client_socket);
int main(int argc, char **argv) {
#define ps struct sockaddr

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
    int status;
    p_pid = fork();
    if (p_pid == -1) {
      std::cout << "Error fork()" << strerror(errno) << std::endl;
      close(client_socket);
      exit(1);
    } else if (p_pid == 0) {
      client_task(client_socket);
    }
      else{
        while (wait(& status) != p_pid);
      }
  }

  close(list_socket);
  return 1;
}

int client_task(int client_socket) {
  int count = 0;
  std::cout << "client start(" << count << ")" << '\n';

  int read_byte = 0;
  std::array<char, 1000> user_string = {{'\0'}};
  std::vector<char *> user_string_pointer = {nullptr};

  while (1) {
    read_byte = 0;
    read_byte = read(client_socket, (void *)user_string.data(), user_string.size());

    if (read_byte > 1) {
      user_string_pointer = pars_line(user_string);
      execute_command(user_string_pointer, client_socket);
    }
  }

  close(client_socket);
  return 0;
}

int execute_command(std::vector<char*> &user_string_pointer, int &client_socket) {
  int count = 0;
  std::cout << "execute_command start(" << count << ")" << '\n';
  int p_pid;
  p_pid = fork();
  if (p_pid == -1) {
    std::cout << "Error fork()" << strerror(errno) << std::endl;
    return -1;
    exit(1);
  } else if (p_pid == 0) {
    dup2(client_socket, 1);
    int ret;
    ret = execvp(user_string_pointer[0], (char *const *)&user_string_pointer[0]);
    if (ret == -1) {
    std::cout << "Error execlpv(1)" << strerror(errno) << std::endl;
    close(client_socket);
    exit(1);
    return 0;
    }
  }

  return 1;
}
