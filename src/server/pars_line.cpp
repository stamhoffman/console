#include "config.h"

int find_data(std::array<char, 1000>::iterator &start_itr,
              std::array<char, 1000>::iterator &end_itr,
              std::array<char, 1000>:: iterator &data);

int pars_line(std::array<char, 1000> *read_buff,
              std::array<char, 1000> *prog_name,
              std::array<char, 1000> *prog_key) {

  if (read_buff == nullptr || prog_name == nullptr || prog_key == nullptr) {
    return -1;
  }

  std::array<char, 1000>::iterator start_itr = read_buff->begin();
  std::array<char, 1000>::iterator end_itr = read_buff->begin();
  std::array<char, 1000>::iterator pn_itr = prog_name->begin();
  std::array<char, 1000>::iterator key_itr = prog_key->begin();

  if (*start_itr == '\0') {
    prog_key->fill('\0');
    prog_name->fill('\0');
    return -1;
  }

  if (*start_itr == '\n') {
    prog_key->fill('\0');
    prog_name->fill('\0');
    return -1;
  }

  end_itr = std::find(read_buff->begin(), read_buff->end(), '\0');
  if (end_itr == read_buff->end()) {
    return -1;
  }

  int ret_find;
  prog_key->fill('\0');

  ret_find = find_data(start_itr, end_itr, pn_itr);
  if (ret_find == 0) return ret_find;

  ret_find = find_data(start_itr, end_itr, key_itr);
  if (ret_find == 1) ret_find = ret_find - 1;
  return ret_find;
}

int find_data(std::array<char, 1000>::iterator &start_itr,
              std::array<char, 1000>::iterator &end_itr,
              std::array<char, 1000>::iterator &data_itr) {

  while (std::isgraph(*start_itr) == 0) {
    start_itr++;
  }
  end_itr = start_itr;

  while (std::isgraph(*end_itr) != 0) {
    end_itr++;
  }

  if (*end_itr == '\0') {
    data_itr = std::copy(start_itr, end_itr, data_itr);
    *data_itr = '\0';
    start_itr = end_itr;
    return 0;
  } else {
    data_itr = std::copy(start_itr, end_itr, data_itr);
    *data_itr = '\0';
    start_itr = end_itr;
    return 1;
  }
}
