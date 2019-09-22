#ifndef INCLUDE_DISJOINT_SET_HPP_
#define INCLUDE_DISJOINT_SET_HPP_

#include<vector>
#include<unordered_map>

namespace ds {
  template <typename IdxT = size_t>
  class disjoint_set {

    static_assert(std::is_unsigned<IdxT>::value,
        "IdxT should be an unsigned type");

    static_assert(std::is_integral<IdxT>::value,
        "IdxT should be an integral type");

    public:

      using IndexType = IdxT;

      disjoint_set(IdxT n)
        : parent(n), sizes(n, 1)  {

          if (n > std::numeric_limits<size_t>::max())
            throw std::invalid_argument(
                "maximum number of items should fit in size_t");

          for (IdxT i = 0; i < n; i++)
            parent[i] = i;
        }

      // union sets containing a and b
      void merge(IdxT a, IdxT b) {
        if (a > parent.size() || b > parent.size())
          throw std::invalid_argument(
              "item id larger than specified maximum");
        IdxT rep_a = rep_with_halving(a);
        IdxT rep_b = rep_with_halving(b);
        link(rep_a, rep_b);
      }

      // representative of set containing elem
      IdxT rep(IdxT elem) const {
        if (elem > parent.size())
          throw std::invalid_argument(
              "item id larger than specified maximum");
        while (parent[elem] != elem)
          elem = parent[elem];
        return elem;
      }

      // map of representative to their sets. `singletons` determines if you
      // want sets with a single element to be returned as well.
      std::unordered_map<IdxT, std::vector<IdxT>>
      sets(bool singletons=true) const {
        std::unordered_map<IdxT, std::vector<IdxT>> sets_map;
        for (IdxT i = 0; i < parent.size(); i++) {
          IdxT rep_i = rep(i);
          if (sets_map.find(rep_i) != sets_map.end())
            sets_map[rep_i].push_back(i);
          else if ((sizes[rep_i] > 1) || singletons) {
            sets_map[rep_i].reserve(sizes[rep_i]);
            sets_map[rep_i].push_back(i);
          }
        }

        return sets_map;
      }

    private:

      std::vector<IdxT> parent;
      std::vector<IdxT> sizes;

      IdxT rep_with_halving(IdxT elem) {
        IdxT p = parent[elem];
        IdxT gp = parent[p];
        while(p != gp) {
          parent[elem] = gp;

          elem = gp;
          p = parent[elem];
          gp = parent[p];
        }

        return p;
      }

      void link(IdxT rep_a, IdxT rep_b) {
        if (rep_a == rep_b)
          return;
        else if (sizes[rep_a] > sizes[rep_b]) {
          parent[rep_b] = rep_a;
          sizes[rep_a] += sizes[rep_b];
        } else {
          parent[rep_a] = rep_b;
          sizes[rep_b] += sizes[rep_a];
        }
      }
  };
}

#endif // INCLUDE_DISJOINT_SET_HPP_
