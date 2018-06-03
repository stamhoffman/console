// Функция для парсинга пользовательского ввода от клиента
//
// Предполагается, что пользователь посылает по сети команду с аргументами
// в виде строки ASCII символов которая оканчивается нулём '\0'.
// Эта строка находится в буфере user_str.
//
// Строка может содержать только символы для которых функции std::isblank и std::isgraph
// возвращают ненулевое значение и обязана завершаться нулём '\0'. Любое нарушение этого
// соглашения считается ошибкой.
//
// Функция разбивает строку на множество подстрок, устанавливая символ нуля '\0' после
// команды и каждого последующего аргумента и возвращает вектор с указателями на эти
// подстроки.
//
// Ошибкой в работе функции считается нарушение соглашения о символах, которые может
// содержать строка, а также если в ней не содержится команда.
// В случае ошибки функция возвращает вектор нулевого размера.
// В случае ошибки буфер находится в неопределенном состоянии и должен игнорироваться.
#include <vector>
#include <array>
#include <algorithm>
#include <cctype>

namespace
{
bool isblank_wrapper(char symbol) { return std::isblank(symbol); }
bool isgraph_wrapper(char symbol) { return std::isgraph(symbol); }
}

template <size_t N>
std::vector<char *> parse_line(std::array<char, N> &user_string) {

  std::vector<char *> data_pointers;
  auto cur_itr = user_string.begin();

  while (cur_itr != user_string.end()) {
    cur_itr = std::find_if_not(cur_itr, user_string.end(), isblank_wrapper);
    if (cur_itr == user_string.end()) {
      data_pointers.clear();
      break;
    }
    if (*cur_itr == '\0') {
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
