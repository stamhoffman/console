#include "config.h"
#include "pars_line.h"

std::vector<char *> pars_line(std::array<char, 1000> &user_string) {

  std::vector<char *> data_pointers;
  std::array<char, 1000>::iterator start_itr = user_string.begin();
  std::array<char, 1000>::iterator end_itr = user_string.end();

  while (start_itr != user_string.end()) {
    start_itr = std::find_if(start_itr, user_string.end(), search_begin);
    if (*start_itr == '\0') {
      data_pointers.push_back(nullptr);
      return data_pointers;
    }
    if (*start_itr == '\n')
      return data_pointers;

    data_pointers.push_back(start_itr);
    end_itr = start_itr;

    end_itr = std::find_if_not(start_itr, user_string.end(), search_begin);

    if (*end_itr != '\0') {
      *end_itr = '\0';
      end_itr++;
    } else {
      data_pointers.push_back(nullptr);
      return data_pointers;
    }
    start_itr = end_itr;
  }
  data_pointers.push_back(nullptr);
  return data_pointers;
}

bool search_begin(char symbol) { return std::isgraph(symbol); }
