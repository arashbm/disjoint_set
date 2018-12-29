#include "catch.hpp"

#include <algorithm>
#include <chrono>
#include <random>

#include "disjoint_set.hpp"

using Catch::Matchers::Equals;
using Catch::Matchers::UnorderedEquals;

TEST_CASE( "initialises correctly", "[basics]" ) {
  auto dis = ds::disjoint_set(10);

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

TEST_CASE("basic usage", "[basics]" ) {
  auto dis = ds::disjoint_set(10);

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

TEST_CASE( "performance", "[basics]" ) {

  SECTION("does not scale horribly") {
    size_t n = 250'000;
    auto dis = ds::disjoint_set(n);

    std::random_device r;
    std::default_random_engine gen(r());
    std::uniform_int_distribution<size_t> rand(0, n);

    for (size_t i = 0; i < 1'000; i++)
      dis.merge(rand(gen), rand(gen));

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 1'000; i < 1'300; i++)
      dis.merge(rand(gen), rand(gen));

    auto stop = std::chrono::high_resolution_clock::now();

    std::chrono::high_resolution_clock::duration total_time1 = stop - start;

    INFO( "set sizes: " << dis.sets(false).size() <<
        " " << dis.sets(true).size() << " time: " << total_time1.count());

    for (size_t i = 1'300; i < 100'000; i++)
      dis.merge(rand(gen), rand(gen));


    start = std::chrono::high_resolution_clock::now();

    for (size_t i = 100'000; i < 100'300; i++)
      dis.merge(rand(gen), rand(gen));

    stop = std::chrono::high_resolution_clock::now();

    std::chrono::high_resolution_clock::duration total_time2 = stop - start;

    INFO( "set sizes: " << dis.sets(false).size() <<
        " " << dis.sets(true).size() << " time: " << total_time2.count());

    for (size_t i = 100'300; i < 1'000'000; i++)
      dis.merge(rand(gen), rand(gen));


    start = std::chrono::high_resolution_clock::now();

    for (size_t i = 1'000'000; i < 1'000'300; i++)
      dis.merge(rand(gen), rand(gen));

    stop = std::chrono::high_resolution_clock::now();

    std::chrono::high_resolution_clock::duration total_time3 = stop - start;

    INFO( "set sizes: " << dis.sets(false).size() <<
        " " << dis.sets(true).size() << " time: " << total_time3.count());

    REQUIRE((double)total_time2.count()/(double)total_time1.count() < 1.05);
    REQUIRE((double)total_time3.count()/(double)total_time2.count() < 1.05);
  }
}
