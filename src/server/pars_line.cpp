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

  if (*start_itr == '\0') {
    prog_key->fill('\0');
    prog_name->fill('\0');
    return -1;
  }

  end_itr = std::find(start_itr, read_buff->end(), '\0');
  if (end_itr == (read_buff->end())) {
    return -1;
  }

  while (std::isgraph(*start_itr) == 0) {
    start_itr++;
  }
  if (start_itr == (read_buff->end())) {
    return -1;
  } else {
    end_itr = start_itr;
  }

  while (std::isgraph(*end_itr) != 0) {
    end_itr++;
  }

  if (end_itr == (read_buff->end())) {
    return -1;
  }

  if (*end_itr == '\0') {
    pn_itr = std::copy(start_itr, end_itr, pn_itr);
    *pn_itr = '\0';
    prog_key->fill('\0');
    return 0;
  } else {
    pn_itr = std::copy(start_itr, end_itr, pn_itr);
    *pn_itr = '\0';
  }

  start_itr = end_itr;

  while (std::isgraph(*start_itr) == 0) {
    start_itr++;
  }
  if (start_itr == (read_buff->end())) {
    return -1;
  }

  end_itr = start_itr;

  while (std::isgraph(*end_itr) != 0) {
    end_itr++;
  }

  if (*end_itr == '\0') {
    key_itr = std::copy(start_itr, end_itr, key_itr);
    *key_itr = '\0';
    return 0;
  } else {
    key_itr = std::copy(start_itr, end_itr, key_itr);
    *key_itr = '\0';
    return 0;
  }
}
