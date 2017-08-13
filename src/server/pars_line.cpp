#include "config.h"

int pars_line(std::array<char, 1000> *read_buff,
              std::array<char, 1000> *prog_name,
              std::array<char, 1000> *prog_key) {

  if (read_buff == nullptr || prog_name == nullptr || prog_key == nullptr) {
    return -1;
  }

  std::array<char, 1000> symbol = {{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                                    'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                    's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}};
  std::array<char, 1000> end_symbol = {{' ', '\t', '\0'}};

  *prog_name = {};
  *prog_key = {};

  std::array<char, 1000>::iterator start_itr = read_buff->begin();
  std::array<char, 1000>::iterator end_itr = read_buff->begin();
  std::array<char, 1000>::iterator pn_itr = prog_name->begin();
  std::array<char, 1000>::iterator key_itr = prog_key->begin();

  if (read_buff->empty()) {
    *prog_name = {};
    *prog_key = {};
    return -1;
  }

  start_itr = std::find(end_itr, read_buff->end(), '\0');

  if (start_itr == (read_buff->begin())) {
    *prog_name = {};
    *prog_key = {};
    return -1;
  }

  start_itr = std::find_first_of(read_buff->begin(), read_buff->end(),
                                 symbol.begin(), symbol.end());
  if (start_itr == read_buff->end()) {
    *prog_name = {};
    *prog_key = {};
    return -1;
  }

  end_itr = std::find_first_of(start_itr, read_buff->end(), end_symbol.begin(),
                               end_symbol.end());

  if (end_itr == (read_buff->end())) {
    *prog_name = {};
    *prog_key = {};
    return -1;
  } else {
    std::copy(start_itr, end_itr, pn_itr);
  }

  if ((*end_itr) == '\0') {
    *prog_key = {};
    int count;
    for (count = 0; (*prog_name)[count] != '\0'; count++)
      ;
    if (count > 25) {
      return -1;
    } else {
      return 0;
    }
  }

  while((*end_itr == ' ') || (*end_itr == '\t')){
    end_itr++;
  }

  if (end_itr == (read_buff->end())) {
    *prog_key = {};
    return -1;
  }

  if (((*end_itr) == '\0')) {
    *prog_key = {};
    return 0;
  }

  start_itr = end_itr;

  end_itr = std::find_first_of(start_itr, read_buff->end(), end_symbol.begin(), end_symbol.end());
  {
    if(end_itr == read_buff->end()){
      return -1;
    }
    std::copy(start_itr, end_itr, key_itr);
    int count;
    for (count = 0; (*prog_name)[count] != '\0'; count++)
      ;
    if (count > 25) {
      return -1;
    }
    return 0;
  }
}
