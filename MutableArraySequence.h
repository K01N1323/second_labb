#ifndef MUTABLEARRAYSEQUENCE_H
#define MUTABLEARRAYSEQUENCE_H

#include "ArraySequence.h"
#include <stdexcept>

template <class T> class MutableArraySequence : public ArraySequence<T> {
public:
  MutableArraySequence() : MutableArraySequence(nullptr, 0) {}

  MutableArraySequence(T *items, int count) {
    if (items == nullptr) {
      this->items = new DynamicArray<T>(0);
    } else {
      this->items = new DynamicArray<T>(items, count);
    }
  }

  MutableArraySequence(const MutableArraySequence<T> &other) {
    this->items = new DynamicArray<T>(*other.items);
  }

  MutableArraySequence<T> *Instance() override { return this; }

  Sequence<T> *GetSubsequence(int start_index, int end_index) const override {
    if (start_index < 0 || start_index >= this->GetLength() || end_index < 0 ||
        end_index >= this->GetLength() || start_index > end_index) {
      throw std::out_of_range("Индексы невалидны для данного списка");
    }
    MutableArraySequence<T> *result = new MutableArraySequence<T>();
    for (int index = start_index; index <= end_index; index++) {
      result->Append(this->Get(index));
    }
    return result;
  }

  Sequence<T> *Map(T (*mapper)(const T &)) const override {
    MutableArraySequence<T> *new_array = new MutableArraySequence<T>();

    for (int index = 0; index < this->GetLength(); index++) {
      new_array->Append(mapper(this->items->Get(index)));
    }
    return new_array;
  }

  Sequence<T> *Where(bool (*where)(const T &)) const override {
    MutableArraySequence<T> *new_array = new MutableArraySequence<T>();

    for (int index = 0; index < this->GetLength(); index++) {
      if (where(this->Get(index))) {
        new_array->Append(this->Get(index));
      }
    }
    return new_array;
  }

  IEnumerator<T> *GetEnumerator() const override { return nullptr; }
};

#endif // MUTABLEARRAYSEQUENCE_H