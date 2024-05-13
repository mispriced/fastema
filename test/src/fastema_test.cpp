#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "fastema/fastema.hpp"

#include <catch2/catch_all.hpp>

using namespace Catch;

TEST_CASE("EMA Filter - Unsigned Input Types", "[ema]")
{
  SECTION("uint8_t")
  {
    EMA<3, std::uint8_t> filter(100);
    CHECK(filter(50) == 94);
    CHECK(filter(200) == 107);
    CHECK(filter(0) == 94);
  }
  SECTION("uint16_t")
  {
    EMA<5, std::uint16_t> filter(1000);
    CHECK(filter(500) == 984);
    CHECK(filter(2000) == 1016);
    CHECK(filter(0) == 984);
  }

  SECTION("uint32_t")
  {
    EMA<7, std::uint32_t> filter(100000);
    CHECK(filter(50000) == 99609);
    CHECK(filter(200000) == 100394);
    CHECK(filter(0) == 99609);
  }
}

TEST_CASE("EMA Filter - Signed Input Types", "[ema]")
{
  SECTION("int8_t")
  {
    EMA<3, std::int8_t> filter(0);
    CHECK(filter(50) == 6);
    CHECK(filter(-100) == -7);
    CHECK(filter(0) == -6);
  }

  SECTION("int16_t")
  {
    EMA<5, std::int16_t> filter(1000);
    CHECK(filter(-500) == 953);
    CHECK(filter(2000) == 986);
    CHECK(filter(0) == 955);
  }

  SECTION("int32_t")
  {
    EMA<7, std::int32_t> filter(-100000);
    CHECK(filter(50000) == -98828);
    CHECK(filter(-200000) == -99619);
    CHECK(filter(0) == -98840);
  }
}

TEST_CASE("EMA Filter - Reset", "[ema]")
{
  EMA<3, std::uint16_t> filter(1000);
  CHECK(filter(500) == 938);
  CHECK(filter(2000) == 1070);

  filter.reset(100);
  CHECK(filter(500) == 150);
  CHECK(filter(2000) == 381);
}

TEST_CASE("EMA Filter - Largest K", "[ema]")
{
  EMA<8, std::uint8_t> filter(100);
  CHECK(filter(50) == 100);
  CHECK(filter(200) == 100);
  CHECK(filter(0) == 100);
}