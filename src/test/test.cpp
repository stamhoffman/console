#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "parse_line.h"
#include <array>
#include <vector>

TEST_CASE("parse_line works properly", "[parse_line]") {

  using Buff = std::array<wchar_t, 1000>;
  using Pointers = std::vector<wchar_t *>;

  Buff user_input;
  Pointers output;
  Pointers expected_output;

  SECTION("no zero input") {
    user_input = Buff{};
    output = parse_line(user_input);
    REQUIRE(output.size() == 0);
  }

  SECTION("zero input") {
    user_input = Buff{L"\0"};
    output = parse_line(user_input);
    REQUIRE(output.size() == 0);
  }

  SECTION("enter input а line feed only") {
    user_input = Buff{L"\nls\n-a\n"};
    output = parse_line(user_input);
    REQUIRE(output.size() == 0);
  }

  SECTION("command without arguments") {
    user_input = Buff{L"ls"};
    expected_output = {user_input.begin(), nullptr};
    output = parse_line(user_input);
    REQUIRE(output == expected_output);
    REQUIRE(user_input == Buff{L"ls"});
  }

  SECTION("command with argument") {
    user_input = Buff{L"ls -l"};
    expected_output = {user_input.begin(), user_input.begin() + 3, nullptr};
    output = parse_line(user_input);
    REQUIRE(output == expected_output);
    REQUIRE(user_input == Buff{L"ls\0-l\0"});
  }

  SECTION("command with two arguments") {
    user_input = Buff{L"ls -l -a"};
    expected_output = {user_input.begin(), user_input.begin() + 3,
                      user_input.begin() + 6, nullptr};
    output = parse_line(user_input);
    REQUIRE(output == expected_output);
    REQUIRE(user_input == Buff{L"ls\0-l\0-a\0"});
  }

  SECTION("command with two argument and two space delimeter") {
    user_input = Buff{L"ls  -l  -a"};
    expected_output = {user_input.begin(), user_input.begin() + 4,
                      user_input.begin() + 8, nullptr};
    output = parse_line(user_input);
    REQUIRE(output == expected_output);
    REQUIRE(user_input == Buff{L"ls\0 -l\0 -a\0"});
  }

  SECTION("command with two argument and two space delimeter") {
    user_input = Buff{L"\tls\t-l\t-a\t"};
    expected_output = {user_input.begin() + 1, user_input.begin() + 4,
                      user_input.begin() + 7, nullptr};
    output = parse_line(user_input);
    REQUIRE(output == expected_output);
    REQUIRE(user_input == Buff{L"\tls\0-l\0-a\0"});
  }

  SECTION("command with two argument and two space delimeter") {
    user_input = Buff{L"  ls\t-l  -a\t"};
    expected_output = {user_input.begin() + 2, user_input.begin() + 5,
                      user_input.begin() + 9, nullptr};
    output = parse_line(user_input);
    REQUIRE(output == expected_output);
    REQUIRE(user_input == Buff{L"  ls\0-l\0 -a\0"});
  }

  SECTION("command with two argument and two space delimeter") {
    user_input = Buff{L"  ls\t\t\t-l  -a\t"};
    expected_output = {user_input.begin() + 2, user_input.begin() + 7,
                      user_input.begin() + 11, nullptr};
    output = parse_line(user_input);
    REQUIRE(output == expected_output);
    REQUIRE(user_input == Buff{L"  ls\0\t\t-l\0 -a\0"});
  }
}
