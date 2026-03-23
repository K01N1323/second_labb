#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H

#include "DynamicArray.h"
#include "sequence.h"
#include <stdexcept>

template <class T> class ArraySequence : public Sequence<T> {
protected:
  DynamicArray<T> *items;

public:
  ArraySequence() : items(nullptr) {}
  virtual ~ArraySequence() { delete this->items; }

  virtual ArraySequence<T> *Instance() = 0;

  const T &GetFirst() const override { return this->items->Get(0); }
  const T &GetLast() const override {
    return this->items->Get(this->items->GetSize() - 1);
  }
  int GetLength() const override { return this->items->GetSize(); }
  const T &Get(int index) const override { return this->items->Get(index); }

  ArraySequence<T> *Append(T item) override {
    ArraySequence<T> *target = this->Instance();
    target->items->Resize(target->items->GetSize() + 1);
    target->items->Set(target->items->GetSize() - 1, item);
    return target;
  }

  ArraySequence<T> *Prepend(T item) override {
    ArraySequence<T> *target = this->Instance();
    target->items->Resize(target->items->GetSize() + 1);
    for (int index = (target->items->GetSize() - 1); index > 0; index--) {
      target->items->Set(index, target->items->Get(index - 1));
    }
    target->items->Set(0, item);
    return target;
  }

  ArraySequence<T> *InsertAt(T item, int index) override {
    if (index < 0 || index >= this->items->GetSize()) {
      throw std::out_of_range("Индекс вне диапазона");
    }
    ArraySequence<T> *target = this->Instance();
    target->items->Resize(target->items->GetSize() + 1);
    for (int ind = (target->items->GetSize() - 1); index > 0; ind--) {
      if (ind == index)
        break;
      target->items->Set(ind, target->items->Get(ind - 1));
    }
    target->items->Set(index, item);
    return target;
  }

  ArraySequence<T> *Concat(Sequence<T> *list) override {
    ArraySequence<T> *target = this->Instance();
    for (int index = 0; index < list->GetLength(); index++) {
      ArraySequence<T> *next = target->Append(list->Get(index));
      if (next != target) {
        delete target;
        target = next;
      }
    }
    return target;
  }
};

#endif // ARRAYSEQUENCE_H