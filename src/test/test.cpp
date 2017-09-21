#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "pars_line.h"
#include <array>
#include <vector>

TEST_CASE("pars_line works properly", "[pars_line]") {

  using Buff = std::array<char, 1000>;
  using Pointers = std::vector<char *>;

  Buff user_input;
  Buff null_str;
  Pointers out_start_lines;
  Pointers in_start_lines;

  SECTION("zero input") {
    user_input = Buff{"\0"};
    out_start_lines = pars_line(user_input);
    REQUIRE(out_start_lines.size() == 1);
  }

  SECTION("enter input а line feed only") {
    user_input = Buff{"\n"};
    out_start_lines = pars_line(user_input);
    REQUIRE(out_start_lines.size() == 1);
  }

  SECTION("command without arguments") {
    user_input = Buff{"ls"};
    in_start_lines = {user_input.begin(), nullptr};
    out_start_lines = pars_line(user_input);
    REQUIRE(out_start_lines == in_start_lines);
    REQUIRE(out_start_lines.size() == 2);
    REQUIRE(user_input == Buff{"ls\0"});
  }

  SECTION("command with argument") {
    user_input = Buff{"ls -l"};
    in_start_lines = {user_input.begin(), user_input.begin() + 3, nullptr};
    out_start_lines = pars_line(user_input);
    REQUIRE(out_start_lines == in_start_lines);
    REQUIRE(out_start_lines.size() == 3);
    REQUIRE(user_input == Buff{"ls\0-l\0"});
  }

  SECTION("command with two arguments") {
    user_input = Buff{"ls -l -a"};
    in_start_lines = {user_input.begin(), user_input.begin() + 3,
                      user_input.begin() + 6, nullptr};
    out_start_lines = pars_line(user_input);
    REQUIRE(out_start_lines == in_start_lines);
    REQUIRE(out_start_lines.size() == 4);
    REQUIRE(user_input == Buff{"ls\0-l\0-a\0"});
  }

  SECTION("command with two argument and two space delimeter") {
    user_input = Buff{"ls  -l  -a"};
    in_start_lines = {user_input.begin(), user_input.begin() + 4,
                      user_input.begin() + 8, nullptr};
    out_start_lines = pars_line(user_input);
    REQUIRE(out_start_lines == in_start_lines);
    REQUIRE(out_start_lines.size() == 4);
    REQUIRE(user_input == Buff{"ls\0 -l\0 -a\0"});
  }

  SECTION("command with two argument and two space delimeter") {
    user_input = Buff{"\tls\t-l\t-a\t"};
    in_start_lines = {user_input.begin() + 1, user_input.begin() + 4,
                      user_input.begin() + 7, nullptr};
    out_start_lines = pars_line(user_input);
    REQUIRE(out_start_lines == in_start_lines);
    REQUIRE(out_start_lines.size() == 4);
    REQUIRE(user_input == Buff{"\tls\0-l\0-a\0"});
  }

  SECTION("command with two argument and two space delimeter") {
    user_input = Buff{"  ls\t-l  -a\t"};
    in_start_lines = {user_input.begin() + 2, user_input.begin() + 5,
                      user_input.begin() + 9, nullptr};
    out_start_lines = pars_line(user_input);
    REQUIRE(out_start_lines == in_start_lines);
    REQUIRE(out_start_lines.size() == 4);
    REQUIRE(user_input == Buff{"  ls\0-l\0 -a\0"});
  }

  SECTION("command with two argument and two space delimeter") {
    user_input = Buff{"  ls\t\t\t-l  -a\t"};
    in_start_lines = {user_input.begin() + 2, user_input.begin() + 7,
                      user_input.begin() + 11, nullptr};
    out_start_lines = pars_line(user_input);
    REQUIRE(out_start_lines == in_start_lines);
    REQUIRE(out_start_lines.size() == 4);
    REQUIRE(user_input == Buff{"  ls\0\t\t-l\0 -a\0"});
  }
}
