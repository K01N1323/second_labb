#ifndef IMMUTABLEARRAYSEQUENCE_H
#define IMMUTABLEARRAYSEQUENCE_H

#include "DynamicArray.h"
#include "sequence.h"
#include <stdexcept>

template <class T> class ImmutableArraySequence : public Sequence<T> {
private:
  DynamicArray<T> *items;

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

  ~ImmutableArraySequence() override { delete this->items; }

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
    ImmutableArraySequence<T> *result = new ImmutableArraySequence<T>();
    for (int index = start_index; index <= end_index; index++) {
      Sequence<T> *next = result->Append(this->Get(index));
      delete result;
      result = static_cast<ImmutableArraySequence<T> *>(next);
    }
    return result;
  }

  Sequence<T> *Append(T item) override {
    ImmutableArraySequence<T> *copy = new ImmutableArraySequence<T>(*this);
    copy->items->Resize(copy->items->GetSize() + 1);
    copy->items->Set(copy->items->GetSize() - 1, item);
    return copy;
  }

  Sequence<T> *Prepend(T item) override {
    ImmutableArraySequence<T> *copy = new ImmutableArraySequence<T>(*this);
    copy->items->Resize(copy->items->GetSize() + 1);
    for (int index = copy->items->GetSize() - 1; index > 0; index--) {
      copy->items->Set(index, copy->items->Get(index - 1));
    }
    copy->items->Set(0, item);
    return copy;
  }

  Sequence<T> *InsertAt(T item, int index) override {
    if (index < 0 || index >= this->items->GetSize()) {
      throw std::out_of_range("Индекс вне диапазона");
    }
    ImmutableArraySequence<T> *copy = new ImmutableArraySequence<T>(*this);
    copy->items->Resize(copy->items->GetSize() + 1);
    for (int ind = copy->items->GetSize() - 1; ind > index; ind--) {
      copy->items->Set(ind, copy->items->Get(ind - 1));
    }
    copy->items->Set(index, item);
    return copy;
  }

  Sequence<T> *Concat(Sequence<T> *list) override {
    ImmutableArraySequence<T> *new_array = new ImmutableArraySequence<T>(*this);
    for (int index = 0; index < list->GetLength(); index++) {
      new_array->items->Resize(new_array->items->GetSize() + 1);
      new_array->items->Set(new_array->items->GetSize() - 1, list->Get(index));
    }
    return new_array;
  }

  Sequence<T> *Map(T (*mapper)(const T &)) const override {
    ImmutableArraySequence<T> *new_array = new ImmutableArraySequence<T>();

    for (int index = 0; index < this->GetLength(); index++) {
      new_array->items->Resize(new_array->items->GetSize() + 1);
      new_array->items->Set(new_array->items->GetSize() - 1,
                            mapper(this->Get(index)));
    }

    return new_array;
  }

  Sequence<T> *Where(bool (*where)(const T &)) const override {
    ImmutableArraySequence<T> *new_array = new ImmutableArraySequence<T>();

    for (int index = 0; index < this->GetLength(); index++) {
      if (where(this->Get(index))) {
        new_array->items->Resize(new_array->items->GetSize() + 1);
        new_array->items->Set(new_array->items->GetSize() - 1,
                              this->Get(index));
      }
    }

    return new_array;
  }

  IEnumerator<T> *GetEnumerator() const override { return nullptr; }
};

#endif // IMMUTABLEARRAYSEQUENCE_H
