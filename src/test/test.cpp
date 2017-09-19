#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <array>
#include <vector>
#include <string.h>

#include "pars_line.h"

TEST_CASE("pars_line works properly", "[pars_line]")
{

  using Buff = std::array<char, 1000>;
  using Pointers = std::vector<char *>;

  Buff user_input;
  Buff null_str;
  Pointers headers;
  Pointers user_headers;
  char prog_name[] = "ls";
  char options_0[] = "-l";
  char options_1[] = "-a";

  SECTION("zero input")
  {
    user_input = Buff{"\0"};
    headers = pars_line(user_input);
    REQUIRE(headers.empty());
  }

  SECTION("enter input")
  {
    user_input = Buff{"\n"};
    headers = pars_line(user_input);
    REQUIRE(headers.empty());
  }

  SECTION("command without arguments")
  {
    user_input = Buff{"ls"};
    headers = pars_line(user_input);
    REQUIRE(headers[0] == user_input.begin());
  }

  SECTION("command with argument")
  {
    user_input = Buff{"ls -l"};
    user_headers = {user_input.begin(), user_input.begin() + 3};
    headers = pars_line(user_input);
    REQUIRE(headers == user_headers);
  }

  SECTION("command with two arguments")
  {
    user_input = Buff{"ls -l -a"};
    user_headers = {user_input.begin(), user_input.begin() + 3, user_input.begin() + 6};
    headers = pars_line(user_input);
    REQUIRE(headers == user_headers);
  }

  SECTION("command with two argument and two space delimeter")
  {
    user_input = Buff{"ls  -l  -a"};
    user_headers = {user_input.begin(), user_input.begin() + 4, user_input.begin() + 8};
    headers = pars_line(user_input);
    REQUIRE(headers == user_headers);
  }

  SECTION("command with two argument and two space delimeter")
  {
    user_input = Buff{"\tls\t-l\t-a\t"};
    user_headers = {user_input.begin() + 1, user_input.begin() + 4, user_input.begin() + 7};
    headers = pars_line(user_input);
    REQUIRE(headers == user_headers);
  }

  SECTION("command with two argument and two space delimeter")
  {
    user_input = Buff{"  ls\t-l  -a\t"};
    user_headers = {user_input.begin() + 2, user_input.begin() + 5, user_input.begin() + 9};
    headers = pars_line(user_input);
    REQUIRE(headers == user_headers);
  }

  SECTION("command with two argument and two space delimeter")
  {
    user_input = Buff{"  ls\t\t\t-l  -a\t"};
    user_headers = {user_input.begin() + 2, user_input.begin() + 7, user_input.begin() + 11};
    headers = pars_line(user_input);
    REQUIRE(headers == user_headers);
  }
}
