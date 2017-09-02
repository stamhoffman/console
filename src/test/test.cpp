#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <array>
#include <vector>

#include "pars_line.h"

TEST_CASE("pars_line works properly", "[pars_line]")
{

  using Buff = std::array<char, 1000>;
  using POINTER = std::vector<char *>;

  Buff user_input;
  POINTER pointer;
  char prog_name[] = "ls";
  char options[] = "-l";
  char options_0[] = "-a";


  SECTION("command without arguments")
  {
    user_input = Buff{"ls"};
    pointer = pars_line(user_input);
    REQUIRE(std::equal(std::begin(prog_name), std::end(prog_name), pointer[0]));
  }

  SECTION("command without arguments")
  {
    user_input = Buff{"ls -l"};
    pointer = pars_line(user_input);
    REQUIRE(std::equal(std::begin(prog_name), std::end(prog_name), pointer[0]));
    REQUIRE(std::equal(std::begin(options), std::end(options), pointer[1]));
  }

  SECTION("command without arguments")
  {
    user_input = Buff{"ls -l -a"};
    pointer = pars_line(user_input);
    REQUIRE(std::equal(std::begin(prog_name), std::end(prog_name), pointer[0]));
    REQUIRE(std::equal(std::begin(options_0), std::end(options_0), pointer[2]));
  }

  /*
  using Buff = std::array<char, 1000>;

  Buff user_input;
  Buff file;
  Buff arg;

  char file_ls[] = "ls";
  char arg_la[] = "-la";

  SECTION("arguments are nullptrs")
  {
    REQUIRE(-1 == pars_line(nullptr, nullptr, nullptr));
  }

  SECTION("zero input")
  {
    user_input[0] = '\0';

    REQUIRE(-1 == pars_line(&user_input, &file, &arg));
    REQUIRE(Buff{} == file);
    REQUIRE(Buff{} == arg);
  }

  SECTION("command without arguments")
  {
    user_input = Buff{"ls"};

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(std::equal(std::begin(file_ls), std::end(file_ls), file.begin()));
    REQUIRE(Buff{} == arg);
  }

  SECTION("command with argument")
  {
    user_input = Buff{"ls -la"};

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(std::equal(std::begin(file_ls), std::end(file_ls), file.begin()));
    REQUIRE(std::equal(std::begin(arg_la), std::end(arg_la), arg.begin()));
  }

  SECTION("command with argument and two space delimeter")
  {
    user_input = Buff{"ls  -la"};

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(std::equal(std::begin(file_ls), std::end(file_ls), file.begin()));
    REQUIRE(std::equal(std::begin(arg_la), std::end(arg_la), arg.begin()));
  }

  SECTION("command with argument and tab delimeter")
  {
    user_input = Buff{"ls\t-la"};

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(std::equal(std::begin(file_ls), std::end(file_ls), file.begin()));
    REQUIRE(std::equal(std::begin(arg_la), std::end(arg_la), arg.begin()));
  }

  SECTION("command with argument and tabs spaces delimeter")
  {
    user_input = Buff{"ls\t \t   \t   -la"};

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(std::equal(std::begin(file_ls), std::end(file_ls), file.begin()));
    REQUIRE(std::equal(std::begin(arg_la), std::end(arg_la), arg.begin()));
  }

  SECTION("command with argument and tail")
  {
    user_input = Buff{"ls -la\t   \t   \t    "};

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(std::equal(std::begin(file_ls), std::end(file_ls), file.begin()));
    REQUIRE(std::equal(std::begin(arg_la), std::end(arg_la), arg.begin()));
  }

  SECTION("command with argument and head spaces")
  {
    user_input = Buff{"\t     \tls -la"};

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(std::equal(std::begin(file_ls), std::end(file_ls), file.begin()));
    REQUIRE(std::equal(std::begin(arg_la), std::end(arg_la), arg.begin()));
  }

  SECTION("command without null terminator")
  {
    user_input.fill('a');

    REQUIRE(-1 == pars_line(&user_input, &file, &arg));
  }

  SECTION("command and arg without null terminator")
  {
    user_input.fill('a');
    user_input[1] = ' ';

    REQUIRE(-1 == pars_line(&user_input, &file, &arg));
  }
  */

}
