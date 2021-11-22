#ifndef INCLUDE_DS_DISJOINT_SET_HPP_
#define INCLUDE_DS_DISJOINT_SET_HPP_

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

      explicit disjoint_set(IdxT n);

      // union sets containing a and b
      void merge(IdxT a, IdxT b);

      // representative of set containing elem
      IdxT rep(IdxT elem) const;

      // map of representative to their sets. `singletons` determines if you
      // want sets with a single element to be returned as well.
      std::unordered_map<IdxT, std::vector<IdxT>>
      sets(bool singletons = true) const;

    private:
      std::vector<IdxT> parent;
      std::vector<IdxT> sizes;

      IdxT rep_with_halving(IdxT elem);
      void link(IdxT rep_a, IdxT rep_b);
  };
}  // namespace ds

#include "../../src/disjoint_set.tpp"

#endif  // INCLUDE_DS_DISJOINT_SET_HPP_
