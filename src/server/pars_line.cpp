#include "config.h"

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
  int count = 0;

  if(*start_itr == '\0')
  {
    *pn_itr = '\0';
    *key_itr = '\0';
    return -1;
  }

  while(std::isgraph(*start_itr) == 0){
    start_itr++;
  }
  if (start_itr == (read_buff->end())) {
    return -1;
  }

  end_itr = start_itr;

  while (std::isalnum(*end_itr) != 0) {
    end_itr++;
    count++;
    std::cout << "end_itr:" << end_itr[count] << '\n';
  }

  if (end_itr == (read_buff->end())) {
    return -1;
  }

  if(*end_itr == '\0'){
    std::copy(start_itr, end_itr, pn_itr);
    return 0;
  }
  else{
    pn_itr[count] = '\0';
  }

  start_itr = end_itr;

  while(std::isgraph(*start_itr) == 0){
    start_itr++;
  }
  if (start_itr == (read_buff->end())) {
    return -1;
  }

  end_itr = std::find(start_itr, read_buff->end(), '\0');
  if (end_itr == (read_buff->end())) {
    return -1;
  }
  else{
    std::copy(start_itr, end_itr, key_itr);
    return 0;
  }
}
