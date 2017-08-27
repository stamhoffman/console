#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <array>
#include <vector>
#include <algorithm>

#include "pars_line.h"

TEST_CASE("pars_line works properly", "[pars_line]")
{
  using Buff = std::vector<char>;

  Buff user_input(1000);
  Buff file(1000);
  Buff arg(1000);

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
    //user_input = Buff{"ls"};
    user_input = Buff{'l', 's', '\0'};

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(std::equal(std::begin(file_ls), std::end(file_ls), file.begin()));
    REQUIRE(Buff{} == arg);
  }

  SECTION("command with argument")
  {
    //user_input = Buff{"ls -la"};
    user_input = Buff{'l','s', ' ', '-', 'l', 'a', '\0'};

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(std::equal(std::begin(file_ls), std::end(file_ls), file.begin()));
    REQUIRE(std::equal(std::begin(arg_la), std::end(arg_la), arg.begin()));
  }

  SECTION("command with argument and two space delimeter")
  {
    //user_input = Buff{"ls  -la"};
    user_input = Buff{'l','s',' ',' ','-','l','a'};

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(std::equal(std::begin(file_ls), std::end(file_ls), file.begin()));
    REQUIRE(std::equal(std::begin(arg_la), std::end(arg_la), arg.begin()));
  }

  SECTION("command with argument and tab delimeter")
  {
    //user_input = Buff{"ls\t-la"};
    user_input = Buff{'l','s','\t','-','l','a'};

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(std::equal(std::begin(file_ls), std::end(file_ls), file.begin()));
    REQUIRE(std::equal(std::begin(arg_la), std::end(arg_la), arg.begin()));
  }

  SECTION("command with argument and tabs spaces delimeter")
  {
    //user_input = Buff{"ls\t \t   \t   -la"};
    user_input = Buff{'l','s','\t',' ','\t',' ',' ',' ','\t',' ',' ',' ','-','l','a'};

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(std::equal(std::begin(file_ls), std::end(file_ls), file.begin()));
    REQUIRE(std::equal(std::begin(arg_la), std::end(arg_la), arg.begin()));
  }

  SECTION("command with argument and tail")
  {
    //user_input = Buff{"ls -la\t   \t   \t    "};
    user_input = Buff{'l','s',' ','-','l','a','\t',' ',' ',' ','\t',' ',' ',' ','\t',' ',' ',' ',' '};

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(std::equal(std::begin(file_ls), std::end(file_ls), file.begin()));
    REQUIRE(std::equal(std::begin(arg_la), std::end(arg_la), arg.begin()));
  }

  SECTION("command with argument and head spaces")
  {
    //user_input = Buff{"\t     \tls -la"};
    user_input = Buff{'\t',' ',' ',' ',' ',' ','\t','l','s',' ','-','l','a'};

    REQUIRE(0 == pars_line(&user_input, &file, &arg));
    REQUIRE(std::equal(std::begin(file_ls), std::end(file_ls), file.begin()));
    REQUIRE(std::equal(std::begin(arg_la), std::end(arg_la), arg.begin()));
  }

  SECTION("command without null terminator")
  {
    //user_input.fill('a');
    user_input.assign(1000,'a');

    REQUIRE(-1 == pars_line(&user_input, &file, &arg));
  }

  SECTION("command and arg without null terminator")
  {
    //user_input.fill('a');
    user_input.assign(1000,'a');
    user_input[1] = ' ';

    REQUIRE(-1 == pars_line(&user_input, &file, &arg));
  }
}
