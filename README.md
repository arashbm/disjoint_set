# `ds:disjoint_set`: c++14 disjoint-set data structure [![Actions Status](https://github.com/arashbm/disjoint_set/workflows/Tests/badge.svg)](https://github.com/arashbm/disjoint_set/actions)

A simple implementation of [disjoint-set data structure][ds] with union-by-size
and path halving. Only works with any integral, unsigned type that fits in a
`std::size_t`.

A disjoint-set data structure, also known as union-find or merge-find data
structure, can help you store and quary and manipulate a collection of
non-overlaping (disjoin) subsets of a set.

For example, you can use a disjoint-set data structure to determine connected
components of a graph: start from every node being in it's own set. For each
edge in the network, merge (union) the two sets the two ends of the edge belong
to. The final collection of sets each detemine a connected component.

[ds]: https://en.wikipedia.org/wiki/Disjoint-set_data_structure

## Usage

Clone the library:

```bash
$ git clone https://github.com/arashbm/disjoint_set.git
```

Run the tests:
```bash
$ make check
```

## Example

```
// in "example.cpp"

#include <iostream>
#include <ds/disjoint_set.hpp>

int main() {
  ds::disjoint_set<std::size_t> dis(10);

  dis.merge(1, 2);
  dis.merge(3, 2);
  dis.merge(0, 5);

  // get all the sets with their representative
  std::unordered_map<
    std::size_t,
    std::vector<std::size_t>> sets = dis.sets();
  std::cout << sets.size() << " disjoint sets" << std::endl;

  // get all the sets with their representative, except singleton sets
  auto sets_no_sing = dis.sets(false);
  std::cout << sets_no_sing.size() <<
    " sets without the singletons" << std::endl;

  // get representative of the set that 1 belongs to
  size_t rep = dis.rep(1);

  std::cout << "Members of the set containing 1:" << std::endl;
  for (auto&& i: sets[rep])
    std::cout << "- " << i << std::endl;

  return 0;
}
```

Assuming you cloned this library in `/path/to/disjoint_set`  you can compile
`example.cpp` with:

```bash
$ g++ -std=c++14 -I/path/to/disjoint_set/include -o example example.cpp
$ ./example
7 disjoint sets
2 sets without the singletons
Members of the set containing 1:
- 1
- 2
- 3
```

Check out the tests (in `src/disjoint_tests.cpp`) for more examples.
