#include "config.h"
#include "parse_line.h"

bool isblank_wrapper(char symbol);
bool isgraph_wrapper(char symbol);
void reset_vector(void);
std::vector<char *> parse_line(std::array<char, 1000> &user_string) {

  std::vector<char *> data_pointers;
  std::array<char, 1000>::iterator cur_itr = user_string.begin();

  while (cur_itr != user_string.end()) {
    cur_itr = std::find_if_not(cur_itr, user_string.end(), isblank_wrapper);
    if (cur_itr == user_string.end()) {
      data_pointers.clear();
      break;
    }
    if (*cur_itr == '\0' && !data_pointers.empty()) {
      break;
    }
    if (!std::isgraph(*cur_itr)) {
      data_pointers.clear();
      break;
    }
    data_pointers.push_back(cur_itr);
    cur_itr = std::find_if_not(cur_itr, user_string.end(), isgraph_wrapper);
    if (cur_itr == user_string.end()) {
      data_pointers.clear();
      break;
    }
    if (*cur_itr == '\0') {
      break;
    }
    if (!std::isblank(*cur_itr)) {
      data_pointers.clear();
      break;
    }
    *cur_itr = '\0';
    cur_itr++;
  }
  if (!data_pointers.empty()) {
    data_pointers.push_back(nullptr);
  }
  return data_pointers;
}

bool isblank_wrapper(char symbol) { return std::isblank(symbol); }
bool isgraph_wrapper(char symbol) { return std::isgraph(symbol); }
