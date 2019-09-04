# disjoint\_set

A simple implementation of disjoint-set data structure with union-by-size and
path halving. Only works with any integral, unsigned that fits in a
`std::size_t`.

## Usage

Clone the library:

```bash
$ git clone https://github.com/arashbm/disjoint_set.git
```

Run the tests:
```bash
$ make && ./tests
```

## Example

```
// in "example.cpp"

#include <iostream>
#include <disjoint_set.hpp>

int main() {
  auto dis  = ds::disjoint_set<size_t>(10);

  dis.merge(1, 2);
  dis.merge(3, 2);
  dis.merge(0, 5);


  // get all the sets with their representative
  std::unordered_map<size_t, std::vector<size_t>> sets = dis.sets();

  // get all the sets with their representative, except singleton sets
  auto sets_no_sing = dis.sets(false);

  // get representative of the set that 4 belongs to
  size_t rep = dis.rep(4);

  return 0;
}
```

Assuming you cloned this library in `/path/to/disjoint_set`  you can compile
`example.cpp` with:

```bash
$ g++ -std=c++14 -I/path/to/disjoint_set/include  -c -o example.o example.cpp
$ g++ example.o -o example

```

Check out the tests (in `src/disjoint_tests.cpp`) for more examples.
