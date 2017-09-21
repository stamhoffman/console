#include "config.h"

std::vector<char *> pars_line(std::array<char, 1000> &user_string) {

  std::vector<char *> data_pointers;
  std::array<char, 1000>::iterator start_itr = user_string.begin();
  std::array<char, 1000>::iterator end_itr = user_string.begin();

  if (*start_itr == '\0' || *start_itr == '\n') {
    data_pointers.push_back(nullptr);
    return data_pointers;
  }

  while (*start_itr != '\0') {
    while (std::isgraph(*start_itr) == 0) {
      start_itr++;
    }
    data_pointers.push_back(start_itr);
    end_itr = start_itr;

    while (std::isgraph(*end_itr) != 0) {
      end_itr++;
    }
    if (end_itr != '\0') {
      *end_itr = '\0';
      end_itr++;
    }
    start_itr = end_itr;
  }
  data_pointers.push_back(nullptr);
  return data_pointers;
}
