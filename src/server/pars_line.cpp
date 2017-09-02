#include "config.h"

int find_data(std::vector<char>::iterator &start_itr,
              std::vector<char>::iterator &end_itr,
              std::vector<char>::iterator &data);

int pars_line(std::vector<char> *read_buff, std::vector<char> *prog_name,
              std::vector<char> *prog_key) {

  std::cout << "start pars_line" << '\n';

  if (read_buff == nullptr || prog_name == nullptr || prog_key == nullptr) {
    return -1;
  }

  std::vector<char>::iterator start_itr = read_buff->begin();
  std::vector<char>::iterator end_itr = read_buff->begin();
  std::vector<char>::iterator pn_itr = prog_name->begin();
  std::vector<char>::iterator key_itr = prog_key->begin();

  if (read_buff -> at(0) == '\0') {
    std::fill(prog_name -> begin(), prog_name -> end(), '\0');
    std::fill(prog_key -> begin(), prog_key -> end(), '\0');
    return -1;
  }

  if (*start_itr == '\n') {
    std::fill(prog_name -> begin(), prog_name -> end(), '\0');
    std::fill(prog_key -> begin(), prog_key -> end(), '\0');
    return -1;
  }

  end_itr = std::find(read_buff->begin(), read_buff->end(), '\0');
  if (end_itr == read_buff->end()) {
    std::fill(prog_name -> begin(), prog_name -> end(), '\0');
    std::fill(prog_key -> begin(), prog_key -> end(), '\0');
    return -1;
  }

  int ret_find;
  prog_key->front() = ('\0');

  ret_find = find_data(start_itr, end_itr, pn_itr);
  if (ret_find == 0) {
    std::cout << "prog_name:" << prog_name->data() << '\n';
    std::cout << "prog_key:" << prog_key->data() << '\n';
    return ret_find;
  }

  ret_find = find_data(start_itr, end_itr, key_itr);
  if (ret_find == 1) {
    std::cout << "prog_name:" << prog_name->data() << '\n';
    std::cout << "prog_key:" << prog_key->data() << '\n';
    ret_find = ret_find - 1;
  }
  return ret_find;
}

int find_data(std::vector<char>::iterator &start_itr,
              std::vector<char>::iterator &end_itr,
              std::vector<char>::iterator &data_itr) {

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
