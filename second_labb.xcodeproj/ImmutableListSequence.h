#ifndef IMMUTABLELISTSEQUENCE_H
#define IMMUTABLELISTSEQUENCE_H

#include "LinkedList.h"
#include "sequence.h"
#include <stdexcept>

template <class T> class ImmutableListSequence : public Sequence<T> {
private:
  LinkedList<T> *items;

public:
  ImmutableListSequence() : ImmutableListSequence(nullptr, 0) {}

  ImmutableListSequence(T *items, int count) {
    if (items == nullptr) {
      this->items = new LinkedList<T>();
    } else {
      this->items = new LinkedList<T>(items, count);
    }
  }

  ImmutableListSequence(const ImmutableListSequence<T> &other) {
    this->items = new LinkedList<T>(*other.items);
  }

  ImmutableListSequence(const LinkedList<T> &list) {
    this->items = new LinkedList<T>(list);
  }

  ~ImmutableListSequence() { delete this->items; }

  const T &GetFirst() const override { return this->items->GetFirst(); }

  const T &GetLast() const override { return this->items->GetLast(); }

  const T &Get(int index) const override { return this->items->Get(index); }

  int GetLength() const override { return this->items->GetLength(); }

  Sequence<T> *GetSubsequence(int start_index, int end_index) const override {
    LinkedList<T> *raw_list = this->items->GetSubList(start_index, end_index);
    ImmutableListSequence<T> *new_list =
        new ImmutableListSequence<T>(*raw_list);
    delete raw_list;
    return new_list;
  }

  Sequence<T> *Append(T item) override {
    ImmutableListSequence<T> *copy = new ImmutableListSequence(*this);
    copy->items->Append(item);
    return copy;
  }

  Sequence<T> *Prepend(T item) override {
    ImmutableListSequence<T> *copy = new ImmutableListSequence(*this);
    copy->items->Prepend(item);
    return copy;
  }

  Sequence<T> *InsertAt(T item, int index) override {
    ImmutableListSequence<T> *copy = new ImmutableListSequence(*this);
    copy->items->InsertAt(item, index);
    return copy;
  }

  IEnumerator<T> *GetEnumerator() const override {
    return this->items->GetEnumerator();
  }

  Sequence<T> *Concat(Sequence<T> *list) override {
    ImmutableListSequence<T> *new_list = new ImmutableListSequence<T>(*this);

    IEnumerator<T> *it = list->GetEnumerator();
    while (it->HasNext()) {
      new_list->items->Append(it->GetCurrent());
      it->MoveNext();
    }
    delete it;
    return new_list;
  }

  Sequence<T> *Map(T (*mapper)(const T &)) const override {
    ImmutableListSequence<T> *new_list = new ImmutableListSequence<T>();

    for (int index = 0; index < this->GetLength(); index++) {
      new_list->Append(mapper(this->Get(index)));
    }
    return new_list;
  }
  Sequence<T> *Where(bool (*where)(const T &)) const override {
    ImmutableListSequence<T> *new_list = new ImmutableListSequence<T>();

    for (int index = 0; index < this->GetLength(); index++) {
      if (where(this->Get(index))) {
        new_list->Append(this->Get(index));
      }
    }
    return new_list;
  }
};

#endif // IMMUTABLELISTSEQUENCE_H
