// Функция для парсинга пользовательского ввода от клиента
//
// Предполагается, что пользователь посылает по сети команду с аргументами
// в виде строки символов, оканчивающейся нулём '\0'. Эта строка находится в буфере read_buff.
// Функция парсит строку и копирует имя команды в prog_name.
// Если у команды есть аргумент он копируется в буфер по указателю prog_key.
// Если аргумент не будет найден первый символ в буфере prog_key устанавливается в ноль.
// Буфер prog_name и prog_key содержат строки оканчивающиеся нулями.
//
// В случае правильной работы функция возвращает 0, в случае ошибки -1.
//
// Ошибкой считаются следующие случаи:
// - хотя бы один из аргументов равняется nullptr,
// - read_buff не содержит нулевого символа завершения строки,
// - read_buff содержит некорректное имя команды.

int pars_line(std::array<char, 1000> *read_buff,
              std::array<char, 1000> *prog_name,
              std::array<char, 1000> *prog_key);
