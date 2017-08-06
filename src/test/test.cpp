#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "pars_line.h"

TEST_CASE("pars_line works with nullptrs")
{
  REQUIRE(1 == pars_line(nullptr, nullptr, nullptr));
}
