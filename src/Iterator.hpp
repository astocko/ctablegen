#ifndef _CTABLEGEN_ITERATOR_HPP_
#define _CTABLEGEN_ITERATOR_HPP_

#include "TableGen.hpp"
#include <iostream>

namespace ctablegen {

template <class T> class ArrayRefIterator {
public:
  explicit ArrayRefIterator(ArrayRef<T> a)
      : array_(a), idx_(0), len_(a.size()) {}
  const T *Next() {
    if (idx_ < len_) {
      return &array_[idx_++];
    } else {
      return nullptr;
    }
  }

private:
  ArrayRef<T> array_;
  size_t idx_;
  const size_t len_;
};

class ListRefIterator {
public:
  explicit ListRefIterator(ListInit *list)
    : list_(list), idx_(0), len_(list->size()) {}

  TypedInit* Next() {
    if (idx_ >= len_) return nullptr;
    auto elem = dyn_cast<TypedInit>(list_->getElement(idx_++));
    if (!elem) return nullptr;
    return elem;
  }
private:
  ListInit *list_;
  size_t idx_;
  const size_t len_;
};

class DagRefIterator {
public:
  explicit DagRefIterator(DagInit *dag)
      : dag_(dag), idx_(0), len_(dag->getNumArgs()) {}

  TypedInit* Next() {
    if (idx_ >= len_) return nullptr;
    auto arg = dyn_cast<TypedInit>(dag_->getArg(idx_++));
    if (!arg) return nullptr;
    return arg;
  }

  DagPair* NextPair() {
    if (idx_ >= len_) return nullptr;
    auto name = dag_->getArgName(idx_);
    auto arg = dyn_cast<TypedInit>(dag_->getArg(idx_++));
    if (!arg) return nullptr;
    return new DagPair(name, arg);
  }

private:
  DagInit *dag_;
  size_t idx_;
  const size_t len_;
};
}

#endif
