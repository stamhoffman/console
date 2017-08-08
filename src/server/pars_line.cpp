
#include "config.h"

int pars_line(std::array<char, 1000> *read_buff,
              std::array<char, 1000> *prog_name,
              std::array<char, 1000> *prog_key) {

  if(read_buff == nullptr || prog_name == nullptr || prog_key == nullptr){
    std::cout << "Ошибка: Функция приняла nullptr" << '\n';
    return -1;
  }

  int count = 0;
  std::cout << "pars_line start(" << count << ")" << '\n';
  const char space = ' ';
  std::fill(std::begin(*prog_key), std::end(*prog_key), '\0');
  std::fill(std::begin(*prog_name), std::end(*prog_name), '\0');

  std::array<char, 1000>::iterator rb_itr = (*read_buff).begin();
  std::array<char, 1000>::iterator pn_itr = (*prog_name).begin();
  std::array<char, 1000>::iterator key_itr = (*prog_key).begin();

  rb_itr = std::find(std::begin(*read_buff), std::end(*read_buff), space);

  std::copy((*read_buff).begin(), rb_itr, pn_itr);

  if (rb_itr != std::end(*read_buff)) {
    std::copy(rb_itr + 1, (*read_buff).end(), key_itr);
    return 1;
  }

  return 0;
}
