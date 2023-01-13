#include <algorithm>
#include <random>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <ds/disjoint_set.hpp>

using Catch::Matchers::Equals;
using Catch::Matchers::UnorderedEquals;

TEST_CASE("initialises correctly", "[basics]") {
  ds::disjoint_set<size_t> dis(10);

  SECTION("representatives") {
    for (size_t i = 0; i < 10; i++)
      REQUIRE(dis.rep(i) == i);
  }

  SECTION("singleton sets") {
    auto sets = dis.sets();
    REQUIRE(sets.size() == 10);
    for (auto& i: sets) {
      REQUIRE_THAT(i.second, Equals(std::vector<size_t>({i.first})));
    }
  }

  SECTION("no non-singleton sets") {
    auto sets = dis.sets(false);
    REQUIRE(sets.size() == 0);
  }
}

TEST_CASE("basic usage", "[basics]") {
  ds::disjoint_set<size_t> dis(10);

  // [0, 1, 2, 3, 4] [5, 6, 7, 8] [9]
  dis.merge(0, 1);
  dis.merge(0, 2);
  dis.merge(2, 3);
  dis.merge(4, 1);

  dis.merge(5, 6);
  dis.merge(7, 5);
  dis.merge(7, 8);

  SECTION("all sets") {
    auto sets = dis.sets();
    REQUIRE(sets.size() == 3);

    auto first_set = sets[dis.rep(0)];
    auto second_set = sets[dis.rep(5)];
    auto third_set = sets[dis.rep(9)];

    REQUIRE_THAT(first_set,
        UnorderedEquals(std::vector<size_t>({0, 1, 2, 3, 4})));
    REQUIRE_THAT(second_set,
        UnorderedEquals(std::vector<size_t>({5, 6, 7, 8})));
    REQUIRE_THAT(third_set, Equals(std::vector<size_t>({9})));
  }

  SECTION("non-singleton sets") {
    auto sets = dis.sets(false);
    REQUIRE(sets.size() == 2);

    auto first_set = sets[dis.rep(0)];
    auto second_set = sets[dis.rep(5)];

    REQUIRE_THAT(first_set,
        UnorderedEquals(std::vector<size_t>({0, 1, 2, 3, 4})));
    REQUIRE_THAT(second_set,
        UnorderedEquals(std::vector<size_t>({5, 6, 7, 8})));
  }
}
