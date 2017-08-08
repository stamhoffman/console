#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <array>

#include "pars_line.h"

TEST_CASE("pars_line works properly", "[pars_line]")
{
  using Buff = std::array<char, 1000>;

  Buff user_input;
  Buff file;
  Buff arg;

  SECTION("arguments are nullptrs")
  {
    REQUIRE(-1 == pars_line(nullptr, nullptr, nullptr));
  }

  SECTION("zero input")
  {
    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(Buff{} == file);
    REQUIRE(Buff{} == arg);
  }

  SECTION("command without arguments")
  {
    user_input = {"ls"};

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(Buff{"ls"} == file);
    REQUIRE(Buff{} == arg);
  }

  SECTION("command with argument")
  {
    user_input = {"ls -la"};

    REQUIRE(1 == pars_line(&user_input, &file, &arg));
    REQUIRE(Buff{"ls"} == file);
    REQUIRE(Buff{"-la"} == arg);
  }

  SECTION("command with argument and two space delimeter")
  {
    user_input = {"ls  -la"};

    REQUIRE(1 == pars_line(&user_input, &file, &arg));
    REQUIRE(Buff{"ls"} == file);
    REQUIRE(Buff{"-la"} == arg);
  }

  SECTION("command with argument and tab delimeter")
  {
    user_input = {"ls\t-la"};

    REQUIRE(1 == pars_line(&user_input, &file, &arg));
    REQUIRE(Buff{"ls"} == file);
    REQUIRE(Buff{"-la"} == arg);
  }

  SECTION("command with argument and tabs spaces delimeter")
  {
    user_input = {"ls\t \t   \t   -la"};

    REQUIRE(1 == pars_line(&user_input, &file, &arg));
    REQUIRE(Buff{"ls"} == file);
    REQUIRE(Buff{"-la"} == arg);
  }

  SECTION("command with argument and tail")
  {
    user_input = {"ls -la\t   \t   \t    "};

    REQUIRE(1 == pars_line(&user_input, &file, &arg));
    REQUIRE(Buff{"ls"} == file);
    REQUIRE(Buff{"-la"} == arg);
  }

  SECTION("command without null terminator")
  {
    user_input.fill('a');

    Buff result;
    result.fill('a');
    result[result.size() - 1] = '\0';

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(result == file);
    REQUIRE(Buff{} == arg);
  }

  SECTION("command without null terminator")
  {
    user_input.fill('a');

    Buff result;
    result.fill('a');
    result[result.size() - 1] = '\0';

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(result == file);
    REQUIRE(Buff{} == arg);
  }

  SECTION("command and arg without null terminator")
  {
    user_input.fill('a');
    user_input[1] = ' ';

    Buff arg_result;
    arg_result.fill('a');
    arg_result[arg_result.size() - 2] = '\0';

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(Buff{"a"} == file);
    REQUIRE(arg_result == arg);
  }
}
