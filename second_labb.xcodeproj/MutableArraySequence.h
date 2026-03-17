#ifndef MUTABLEARRAYSEQUENCE_H
#define MUTABLEARRAYSEQUENCE_H

#include "DynamicArray.h"
#include "sequence.h"
#include <stdexcept>

template <class T> class MutableArraySequence : public Sequence<T> {
private:
  DynamicArray<T> *items;

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

  ~MutableArraySequence() { delete this->items; }

  const T &GetFirst() const override { return this->items->Get(0); }

  const T &GetLast() const override {
    return this->items->Get(this->items->GetSize() - 1);
  }

  int GetLength() const override { return this->items->GetSize(); }

  const T &Get(int index) const override { return this->items->Get(index); }

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

  Sequence<T> *Append(T item) override {
    items->Resize(items->GetSize() + 1);
    items->Set(items->GetSize() - 1, item);
    return this;
  }

  Sequence<T> *Prepend(T item) override {
    items->Resize(items->GetSize() + 1);
    for (int index = (items->GetSize() - 1); index > 0; index--) {
      items->Set(index, items->Get(index - 1));
    }
    items->Set(0, item);
    return this;
  }

  Sequence<T> *InsertAt(T item, int index) override {
    if (index < 0 || index >= this->items->GetSize()) {
      throw std::out_of_range("Индекс вне диапазона");
    }
    items->Resize(items->GetSize() + 1);
    for (int ind = (items->GetSize() - 1); index > 0; ind--) {
      if (ind == index)
        break;
      items->Set(ind, items->Get(ind - 1));
    }
    items->Set(index, item);
    return this;
  }

  Sequence<T> *Concat(Sequence<T> *list) override {
    MutableArraySequence<T> *new_array = new MutableArraySequence<T>(*this);
    for (int index = 0; index < list->GetLength(); index++) {
      new_array->Append(list->Get(index));
    }
    return new_array;
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
