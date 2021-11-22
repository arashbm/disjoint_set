namespace ds {
  template <typename IdxT>
  disjoint_set<IdxT>::disjoint_set(IdxT n)
  : parent(n), sizes(n, 1) {
    if (n > std::numeric_limits<size_t>::max())
      throw std::invalid_argument(
          "maximum number of items should fit in size_t");

    for (IdxT i = 0; i < n; i++)
      parent[i] = i;
  }

  template <typename IdxT>
  void disjoint_set<IdxT>::merge(IdxT a, IdxT b) {
    if (a >= parent.size() || b >= parent.size())
      throw std::invalid_argument(
          "item id larger than specified maximum");
    IdxT rep_a = rep_with_halving(a);
    IdxT rep_b = rep_with_halving(b);
    link(rep_a, rep_b);
  }

  template <typename IdxT>
  IdxT disjoint_set<IdxT>::rep(IdxT elem) const {
    if (elem >= parent.size())
      throw std::invalid_argument(
          "item id larger than specified maximum");
    while (parent[elem] != elem)
      elem = parent[elem];
    return elem;
  }

  template <typename IdxT>
  std::unordered_map<IdxT, std::vector<IdxT>>
  disjoint_set<IdxT>::sets(bool singletons) const {
    std::unordered_map<IdxT, std::vector<IdxT>> sets_map;
    for (IdxT i = 0; i < parent.size(); i++) {
      IdxT rep_i = rep(i);
      if (sets_map.find(rep_i) != sets_map.end()) {
        sets_map[rep_i].push_back(i);
      } else if ((sizes[rep_i] > 1) || singletons) {
        sets_map[rep_i].reserve(sizes[rep_i]);
        sets_map[rep_i].push_back(i);
      }
    }

    return sets_map;
  }

  template <typename IdxT>
  IdxT disjoint_set<IdxT>::rep_with_halving(IdxT elem) {
    IdxT p = parent[elem];
    IdxT gp = parent[p];
    while (p != gp) {
      parent[elem] = gp;

      elem = gp;
      p = parent[elem];
      gp = parent[p];
    }

    return p;
  }

  template <typename IdxT>
  void disjoint_set<IdxT>::link(IdxT rep_a, IdxT rep_b) {
    if (rep_a == rep_b) {
      return;
    } else if (sizes[rep_a] > sizes[rep_b]) {
      parent[rep_b] = rep_a;
      sizes[rep_a] += sizes[rep_b];
    } else {
      parent[rep_a] = rep_b;
      sizes[rep_b] += sizes[rep_a];
    }
  }


}  // namespace ds
