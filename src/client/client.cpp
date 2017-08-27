#include "config.h"

int main(int argc, char **argv) {
#define pointer_addr const struct sockaddr

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

  int sock_dsc;
  sock_dsc = socket(AF_INET, SOCK_STREAM, 0);

  if (sock_dsc == -1) {
    std::cout << "Error socket():" << strerror(errno) << std::endl;
    close(sock_dsc);
    return -1;
  }

  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) == -1) {
    std::cout << "Error inet_pton():" << strerror(errno) << std::endl;
    close(sock_dsc);
    return -1;
  }

  if (connect(sock_dsc, (pointer_addr *)&serv_addr, sizeof(serv_addr)) == -1) {
    std::cout << "Error connect:" << strerror(errno) << std::endl;
    return -1;
    close(sock_dsc);
  }

  std::vector<char> send_buff(1000);
  std::vector<char> read_buff(1000);

  while (1) {
    std::cin.getline(send_buff.data(), 1000);
    int ret_send;
    ret_send =
        send(sock_dsc, (const void *)send_buff.data(), send_buff.size(), 0);
    if (ret_send == -1) {
      std::cout << "Error send():" << strerror(errno) << std::endl;
    }

    int read_byte = 0;
    int count = 0;

    read_byte = read(sock_dsc, (void *)read_buff.data(), read_buff.size());
    if (read_byte > 1) {
      std::cout << "server(" << count << "):" << '\n'
                << read_buff.data() << '\n';
      std::cout << "---------------------------------------------------"
                << '\n';
    } else {
      std::cout << "Error read():" << strerror(errno) << std::endl;
    }
  }

  close(sock_dsc);
  return 0;
}
