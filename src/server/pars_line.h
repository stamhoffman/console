/*!
Функция преобразует массив символов в два массива символов, если принятый массив содержит
последовательность символов разделенных пробелом, в первый помещаются символы с начала входного
массива и до символа пробел, остальные символы копируются во второй массив, если входной массив
состоит из одной последовательности символов то все они копируются в первый выходной массив

\param [<in>] <read_buff> {Указатель на массив разбиваемый функцией на команду и ключ}
\param [<out>] <prog_name> {Указатель на массив куда копируется распознанная команда}
\param [<out>] <prog_name> {Указатель на массив куда копируется распознанный ключ}

\return {-1 если принятые указатели на массивы не инициализированы, 0 если принятый по указателю
массив состоит из одной последовательности символов, 1 если из двух, разделенных символом пробел}

*/
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
