#include<vector>
#include<unordered_map>
namespace ds {
  class disjoint_set {
    public:

      disjoint_set(size_t n)
        : parent(n), sizes(n, 1)  {
          for (size_t i = 0; i < n; i++)
            parent[i] = i;
        }

      // union sets containing a and b
      void merge(size_t a, size_t b) {
        size_t rep_a = rep_with_halving(a);
        size_t rep_b = rep_with_halving(b);
        link(rep_a, rep_b);
      }

      // representative of set containing elem
      size_t rep(size_t elem) const {
        while (parent[elem] != elem)
          elem = parent[elem];
        return elem;
      }

      // map of representative to their sets. `singletons` determines if you want
      // sets with a single element to be returned as well.
      std::unordered_map<size_t, std::vector<size_t>>
      sets(bool singletons=true) const {
        std::unordered_map<size_t, std::vector<size_t>> sets_map;
        for (size_t i = 0; i < parent.size(); i++) {
          size_t rep_i = rep(i);
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

      std::vector<size_t> parent;
      std::vector<size_t> sizes;

      size_t rep_with_halving(size_t elem) {
        size_t p = parent[elem];
        size_t gp = parent[p];
        while(p != gp) {
          parent[elem] = gp;

          elem = gp;
          p = parent[elem];
          gp = parent[p];
        }

        return p;
      }

      void link(size_t rep_a, size_t rep_b) {
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
