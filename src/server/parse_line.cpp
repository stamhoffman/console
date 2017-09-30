#include "config.h"
#include "parse_line.h"

bool isblank_wrapper(char symbol);
bool isgraph_wrapper(char symbol);
std::vector<char *> parse_line(std::array<char, 1000> &user_string) {

  std::vector<char *> data_pointers;
  std::array<char, 1000>::iterator start_itr = user_string.begin();
  std::array<char, 1000>::iterator end_itr = user_string.end();

  while (start_itr != user_string.end()) {
    start_itr = std::find_if_not(start_itr, user_string.end(), isblank_wrapper);
    if (start_itr == user_string.end()) {
      data_pointers.clear();
      return data_pointers;
    }
    if (*start_itr == '\0' && !data_pointers.empty()) {
      data_pointers.push_back(nullptr);
      return data_pointers;
    }

    if (!std::isgraph(*start_itr)) {
      data_pointers.clear();
      return data_pointers;
    }

    data_pointers.push_back(start_itr);
    end_itr = start_itr;

    end_itr = std::find_if_not(start_itr, user_string.end(), isgraph_wrapper);
    if (end_itr == user_string.end()) {
      data_pointers.clear();
      return data_pointers;
    }

    if (*end_itr == '\0') {
      data_pointers.push_back(nullptr);
      return data_pointers;
    }

    if (!std::isblank(*end_itr)) {
      data_pointers.clear();
      return data_pointers;
    }

    start_itr = end_itr + 1;
    if (start_itr != user_string.end()) {
      *end_itr = '\0';
    }
  }
  data_pointers.clear();
  return data_pointers;
}

bool isblank_wrapper(char symbol) { return std::isblank(symbol); }
bool isgraph_wrapper(char symbol) { return std::isgraph(symbol); }
