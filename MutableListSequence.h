#ifndef MUTABLELISTSEQUENCE_H
#define MUTABLELISTSEQUENCE_H

#include "ImmutableListSequence.h"
#include "LinkedList.h"
#include "sequence.h"
#include <stdexcept>

template <class T> class MutableListSequence : public Sequence<T> {
private:
  LinkedList<T> *items;

public:
  MutableListSequence() : MutableListSequence(nullptr, 0) {}

  MutableListSequence(T *items, int count) {
    if (items == nullptr) {
      this->items = new LinkedList<T>();
    } else {
      this->items = new LinkedList<T>(items, count);
    }
  }

  MutableListSequence(const LinkedList<T> &list) {
    this->items = new LinkedList<T>(list);
  }

  ~MutableListSequence() { delete this->items; }

  const T &GetFirst() const override { return this->items->GetFirst(); }

  const T &GetLast() const override { return this->items->GetLast(); }

  const T &Get(int index) const override { return this->items->Get(index); }

  int GetLength() const override { return this->items->GetLength(); }

  Sequence<T> *Append(T item) override {
    this->items->Append(item);
    return this;
  }

  Sequence<T> *Prepend(T item) override {
    this->items->Prepend(item);
    return this;
  }

  Sequence<T> *InsertAt(T item, int index) override {
    this->items->InsertAt(item, index);
    return this;
  }

  Sequence<T> *GetSubsequence(int start_index, int end_index) const override {
    if (start_index < 0 || start_index >= this->GetLength() || end_index < 0 ||
        end_index >= this->GetLength() || start_index > end_index) {
      throw std::out_of_range("Индексы невалидны");
    }
    LinkedList<T> *sub_list = this->items->GetSubList(start_index, end_index);
    MutableListSequence<T> *result = new MutableListSequence<T>(*sub_list);
    delete sub_list;
    return result;
  }

  Sequence<T> *Instance() override { return this; }

  IEnumerator<T> *GetEnumerator() const override {
    return this->items->GetEnumerator();
  }

  Sequence<T> *Concat(Sequence<T> *list) override {
    MutableListSequence<T> *result = new MutableListSequence<T>(*this->items);
    IEnumerator<T> *it = list->GetEnumerator();
    while (it->HasNext()) {
      result->items->Append(it->GetCurrent());
      it->MoveNext();
    }
    delete it;
    return result;
  }

  Sequence<T> *Map(T (*mapper)(const T &)) const override {
    MutableListSequence<T> *new_list = new MutableListSequence<T>();
    for (int index = 0; index < this->GetLength(); index++) {
      new_list->Append(mapper(this->Get(index)));
    }
    return new_list;
  }

  Sequence<T> *Where(bool (*where)(const T &)) const override {
    MutableListSequence<T> *new_list = new MutableListSequence<T>();
    for (int index = 0; index < this->GetLength(); index++) {
      if (where(this->Get(index))) {
        new_list->Append(this->Get(index));
      }
    }
    return new_list;
  }
};

#endif // MUTABLELISTSEQUENCE_H
