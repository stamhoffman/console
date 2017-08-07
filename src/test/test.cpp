#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <array>

#include "pars_line.h"

TEST_CASE("pars_line works with nullptrs")
{
  REQUIRE(-1 == pars_line(nullptr, nullptr, nullptr));
}

TEST_CASE("pars_line works with zero input")
{
  std::array<char, 1000> user_input;
  std::array<char, 1000> file;
  std::array<char, 1000> arg;

  REQUIRE(0 == pars_line(&user_input, &file, &arg));
  REQUIRE((std::array<char, 1000>{} == file));
  REQUIRE((std::array<char, 1000>{} == arg));
}

TEST_CASE("pars_line works with simple command")
{
  std::array<char, 1000> user_input = {"ls"};
  std::array<char, 1000> file;
  std::array<char, 1000> arg;

  REQUIRE(0 == pars_line(&user_input, &file, &arg));
  REQUIRE((std::array<char, 1000>{"ls"} == file));
  REQUIRE((std::array<char, 1000>{} == arg));
}

TEST_CASE("pars_line works with command and arg")
{
  std::array<char, 1000> user_input = {"ls -la"};
  std::array<char, 1000> file;
  std::array<char, 1000> arg;

  REQUIRE(1 == pars_line(&user_input, &file, &arg));
  REQUIRE((std::array<char, 1000>{"ls"} == file));
  REQUIRE((std::array<char, 1000>{"-la"} == arg));
}

TEST_CASE("pars_line works with command and arg with two space delimeter")
{
  std::array<char, 1000> user_input = {"ls  -la"};
  std::array<char, 1000> file;
  std::array<char, 1000> arg;

  REQUIRE(1 == pars_line(&user_input, &file, &arg));
  REQUIRE((std::array<char, 1000>{"ls"} == file));
  REQUIRE((std::array<char, 1000>{"-la"} == arg));
}
