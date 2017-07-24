#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>

int main(int argc, char **argv) {
#define pointer_adrr const struct sockaddr
#define PORT 54321

  if (argc < 2) {
    std::cout << "Ошибка в формате команды, не введен адрес сервера \n";
    std::cout << "Используйте ключ -h для получения справки \n";
    return -1;
  }

  const std::string const_buffer("-h");

  if (const_buffer.compare(argv[1]) == 0) {
    std::cout << "Формат команды " << argv[0] << " 127.0.0.1 \n";
    return 0;
  }

  int socket_descriptor;
  socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_descriptor == -1) {
    std::cout << "Error socket():" << strerror(errno) << std::endl;
    return -1;
  }

  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) == -1) {
    std::cout << "Error inet_pton():" << strerror(errno) << std::endl;
    return -1;
  }

  if (connect(socket_descriptor, (pointer_adrr *)&serv_addr,
              sizeof(serv_addr)) == -1) {
    std::cout << "Error connect:" << strerror(errno) << std::endl;
  }

  std::string send_buffer;

  while (1) {
    std::cin >> send_buffer;
    send(socket_descriptor, (const void *)send_buffer.data(),
         send_buffer.size(), 0);
  }

  return 0;
}
