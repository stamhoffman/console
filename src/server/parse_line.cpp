#include "config.h"
#include "parse_line.h"

bool isblank_wrapper(char symbol);
bool isgraph_wrapper(char symbol);
std::vector<char *> parse_line(std::array<char, 1000> &user_string) {

  std::vector<char *> data_pointers;
  std::array<char, 1000>::iterator start_itr = user_string.begin();

  while (start_itr != user_string.end()) {
    start_itr = std::find_if_not(start_itr, user_string.end(), isblank_wrapper);
    if (start_itr == user_string.end()) {
      break;
    }
    if (*start_itr == '\0' && !data_pointers.empty()) {
      data_pointers.push_back(nullptr);
      return data_pointers;
    }
    if (!std::isgraph(*start_itr)) {
      break;
    }
    data_pointers.push_back(start_itr);
    start_itr = std::find_if_not(start_itr, user_string.end(), isgraph_wrapper);
    if (start_itr == user_string.end()) {
      break;
    }
    if (*start_itr == '\0') {
      data_pointers.push_back(nullptr);
      return data_pointers;
    }
    if (!std::isblank(*start_itr)) {
      break;
    }
    *start_itr = '\0';
    start_itr++;
  }
  data_pointers.clear();
  return data_pointers;
}

bool isblank_wrapper(char symbol) { return std::isblank(symbol); }
bool isgraph_wrapper(char symbol) { return std::isgraph(symbol); }
