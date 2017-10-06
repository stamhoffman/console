#include "config.h"
#include "parse_line.h"

bool iswblank_wrapper(wchar_t symbol);
bool iswgraph_wrapper(wchar_t symbol);
void reset_vector(void);
std::vector<wchar_t *> parse_line(std::array<wchar_t, 1000> &user_string) {

  std::vector<wchar_t *> data_pointers;
  std::array<wchar_t, 1000>::iterator cur_itr = user_string.begin();

  while (cur_itr != user_string.end()) {
    cur_itr = std::find_if_not(cur_itr, user_string.end(), iswblank_wrapper);
    if (cur_itr == user_string.end()) {
      data_pointers.clear();
      break;
    }
    if (*cur_itr == '\0' && !data_pointers.empty()) {
      break;
    }
    if (!std::iswgraph(*cur_itr)) {
      data_pointers.clear();
      break;
    }
    data_pointers.push_back(cur_itr);
    cur_itr = std::find_if_not(cur_itr, user_string.end(), iswgraph_wrapper);
    if (cur_itr == user_string.end()) {
      data_pointers.clear();
      break;
    }
    if (*cur_itr == '\0') {
      break;
    }
    if (!std::iswblank(*cur_itr)) {
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

bool iswblank_wrapper(wchar_t symbol) { return std::iswblank(symbol); }
bool iswgraph_wrapper(wchar_t symbol) { return std::iswgraph(symbol); }
