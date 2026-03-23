#ifndef IMMUTABLEARRAYSEQUENCE_H
#define IMMUTABLEARRAYSEQUENCE_H

#include "ArraySequence.h"
#include <stdexcept>

template <class T> class ImmutableArraySequence : public ArraySequence<T> {
public:
  ImmutableArraySequence() : ImmutableArraySequence(nullptr, 0) {}

  ImmutableArraySequence(T *items, int count) {
    if (items == nullptr || count == 0) {
      this->items = new DynamicArray<T>(0);
    } else {
      this->items = new DynamicArray<T>(items, count);
    }
  }

  ImmutableArraySequence(const ImmutableArraySequence<T> &other) {
    this->items = new DynamicArray<T>(*other.items);
  }

  ImmutableArraySequence<T> *Instance() override {
    return new ImmutableArraySequence<T>(*this);
  }

  Sequence<T> *GetSubsequence(int start_index, int end_index) const override {
    if (start_index < 0 || start_index >= this->GetLength() || end_index < 0 ||
        end_index >= this->GetLength() || start_index > end_index) {
      throw std::out_of_range("Индексы невалидны для данного списка");
    }

    Sequence<T> *result = new ImmutableArraySequence<T>();
    for (int index = start_index; index <= end_index; index++) {
      Sequence<T> *next = result->Append(this->Get(index));
      delete result;
      result = next;
    }
    return result;
  }

  Sequence<T> *Map(T (*mapper)(const T &)) const override {
    Sequence<T> *new_array = new ImmutableArraySequence<T>();

    for (int index = 0; index < this->GetLength(); index++) {
      Sequence<T> *next = new_array->Append(mapper(this->items->Get(index)));
      delete new_array;
      new_array = next;
    }
    return new_array;
  }

  Sequence<T> *Where(bool (*where)(const T &)) const override {
    Sequence<T> *new_array = new ImmutableArraySequence<T>();

    for (int index = 0; index < this->GetLength(); index++) {
      if (where(this->Get(index))) {
        Sequence<T> *next = new_array->Append(this->Get(index));
        delete new_array;
        new_array = next;
      }
    }
    return new_array;
  }

  IEnumerator<T> *GetEnumerator() const override { return nullptr; }
};

#endif // IMMUTABLEARRAYSEQUENCE_H