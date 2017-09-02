#include "config.h"

std::vector<char *> pars_line(std::array<char, 1000> &user_string) {

  std::vector<char *> pars_line_pointer;

  std::array<char, 1000>::iterator start_itr = user_string.begin();
  std::array<char, 1000>::iterator end_itr = user_string.begin();

while(*start_itr != '\0'){
  while (std::isgraph(*start_itr) == 0) {
    start_itr++;
  }
  pars_line_pointer.push_back(start_itr);
  end_itr = start_itr;

  while (std::isgraph(*end_itr) != 0) {
    end_itr++;
  }
  if(end_itr != '\0') {
    *end_itr = '\0';
    end_itr++;
  }
  start_itr = end_itr;
}
return pars_line_pointer;
}
