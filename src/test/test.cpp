#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <array>
#include <vector>
#include <string.h>

#include "pars_line.h"

TEST_CASE("pars_line works properly", "[pars_line]")
{

  using Buff = std::array<char, 1000>;
  using Pointer = std::vector<char *>;

  Buff user_input;
  Buff null_str;
  Pointer pointer;
  char prog_name[] = "ls";
  char options_0[] = "-l";
  char options_1[] = "-a";

  SECTION("zero input")
  {
    user_input = Buff{"\0"};
    pointer = pars_line(user_input);
    REQUIRE(pointer[0] == user_input.begin());
    REQUIRE(*pointer[0] == '\0');
  }

  SECTION("enter input")
  {
    user_input = Buff{"\n"};
    pointer = pars_line(user_input);
    REQUIRE(pointer[0] == user_input.begin());
    REQUIRE(*pointer[0] == '\0');
  }

  SECTION("command without arguments")
  {
    user_input = Buff{"ls"};
    pointer = pars_line(user_input);
    REQUIRE(pointer[0] == user_input.begin());
    REQUIRE(isgraph(*pointer[0]) != 0);
    REQUIRE(std::equal(std::begin(prog_name), std::end(prog_name), pointer[0]));
  }

  SECTION("command with argument")
  {
    user_input = Buff{"ls -l"};
    pointer = pars_line(user_input);
    REQUIRE(pointer[0] == user_input.begin());
    REQUIRE(isgraph(*pointer[0]) != 0);
    REQUIRE(pointer[1] == user_input.begin() + 3);
    REQUIRE(isgraph(*pointer[1]) != 0);
    REQUIRE(std::equal(std::begin(prog_name), std::end(prog_name), pointer[0]));
    REQUIRE(std::equal(std::begin(options_0), std::end(options_0), pointer[1]));
  }

  SECTION("command with two arguments")
  {
    user_input = Buff{"ls -l -a"};
    pointer = pars_line(user_input);
    REQUIRE(pointer[0] == user_input.begin());
    REQUIRE(isgraph(*pointer[0]) != 0);
    REQUIRE(pointer[1] == user_input.begin() + 3);
    REQUIRE(isgraph(*pointer[1]) != 0);
    REQUIRE(pointer[2] == user_input.begin() + 6);
    REQUIRE(isgraph(*pointer[2]) != 0);
    REQUIRE(std::equal(std::begin(prog_name), std::end(prog_name), pointer[0]));
    REQUIRE(std::equal(std::begin(options_0), std::end(options_0), pointer[1]));
    REQUIRE(std::equal(std::begin(options_1), std::end(options_1), pointer[2]));
  }

SECTION("command with two argument and two space delimeter")
{
  user_input = Buff{"ls  -l  -a"};
  pointer = pars_line(user_input);
  REQUIRE(pointer[0] == user_input.begin());
  REQUIRE(isgraph(*pointer[0]) != 0);
  REQUIRE(pointer[1] == user_input.begin() + 4);
  REQUIRE(isgraph(*pointer[1]) != 0);
  REQUIRE(pointer[2] == user_input.begin() + 8);
  REQUIRE(isgraph(*pointer[2]) != 0);
  REQUIRE(std::equal(std::begin(prog_name), std::end(prog_name), pointer[0]));
  REQUIRE(std::equal(std::begin(options_0), std::end(options_0), pointer[1]));
  REQUIRE(std::equal(std::begin(options_1), std::end(options_1), pointer[2]));
}

SECTION("command with two argument and two space delimeter")
{
  user_input = Buff{"\tls\t-l\t-a\t"};
  pointer = pars_line(user_input);
  REQUIRE(pointer[0] == user_input.begin() + 1);
  REQUIRE(isgraph(*pointer[0]) != 0);
  REQUIRE(pointer[1] == user_input.begin() + 4);
  REQUIRE(isgraph(*pointer[1]) != 0);
  REQUIRE(pointer[2] == user_input.begin() + 7);
  REQUIRE(isgraph(*pointer[2]) != 0);
  REQUIRE(std::equal(std::begin(prog_name), std::end(prog_name), pointer[0]));
  REQUIRE(std::equal(std::begin(options_0), std::end(options_0), pointer[1]));
  REQUIRE(std::equal(std::begin(options_1), std::end(options_1), pointer[2]));
}

SECTION("command with two argument and two space delimeter")
{
  user_input = Buff{"  ls\t-l  -a\t"};
  pointer = pars_line(user_input);
  REQUIRE(pointer[0] == user_input.begin() + 2);
  REQUIRE(isgraph(*pointer[0]) != 0);
  REQUIRE(pointer[1] == user_input.begin() + 5);
  REQUIRE(isgraph(*pointer[1]) != 0);
  REQUIRE(pointer[2] == user_input.begin() + 9);
  REQUIRE(isgraph(*pointer[2]) != 0);
  REQUIRE(std::equal(std::begin(prog_name), std::end(prog_name), pointer[0]));
  REQUIRE(std::equal(std::begin(options_0), std::end(options_0), pointer[1]));
  REQUIRE(std::equal(std::begin(options_1), std::end(options_1), pointer[2]));
}

SECTION("command with two argument and two space delimeter")
{
  user_input = Buff{"  ls\t\t\t-l  -a\t"};
  pointer = pars_line(user_input);
  REQUIRE(pointer[0] == user_input.begin() + 2);
  REQUIRE(isgraph(*pointer[0]) != 0);
  REQUIRE(pointer[1] == user_input.begin() + 7);
  REQUIRE(isgraph(*pointer[1]) != 0);
  REQUIRE(pointer[2] == user_input.begin() + 11);
  REQUIRE(isgraph(*pointer[2]) != 0);
  REQUIRE(std::equal(std::begin(prog_name), std::end(prog_name), pointer[0]));
  REQUIRE(std::equal(std::begin(options_0), std::end(options_0), pointer[1]));
  REQUIRE(std::equal(std::begin(options_1), std::end(options_1), pointer[2]));
}
}
