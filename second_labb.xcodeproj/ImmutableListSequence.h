#ifndef IMMUTABLELISTSEQUENCE_H
#define IMMUTABLELISTSEQUENCE_H

#include <stdexcept>
#include "LinkedList.h"
#include "sequence.h"

template <class T>
class ImmutableListSequence : public Sequence<T> {
private:
    LinkedList<T>* items;
public:
    ImmutableListSequence() : ImmutableListSequence(nullptr, 0) {}

    ImmutableListSequence(T* items, int count) {
        if (items == nullptr) {
            this->items = new LinkedList<T>();
        } else {
            this->items = new LinkedList<T>(items, count);
        }
    }

    ImmutableListSequence(const ImmutableListSequence<T>& other) {
        this->items = new LinkedList<T>(*other.items);
    }

    ImmutableListSequence(const LinkedList<T>& list) {
        this->items = new LinkedList<T>(list);
    }

    ~ImmutableListSequence() {
        delete this->items;
    }

    const T& GetFirst() const override {
        return this->items->GetFirst();
    }

    const T& GetLast() const override {
        return this->items->GetLast();
    }

    const T& Get(int index) const override {
        return this->items->Get(index);
    }

    int GetLength() const override {
        return this->items->GetLength();
    }

    Sequence<T>* GetSubsequence(int start_index, int end_index) const override {
        LinkedList<T>* raw_list = this->items->GetSubList(start_index, end_index);
        ImmutableListSequence<T>* new_list = new ImmutableListSequence<T>(*raw_list);
        delete raw_list;
        return new_list;
    }

    Sequence<T>* Append(T item) override {
        ImmutableListSequence<T>* copy = new ImmutableListSequence(*this);
        copy->items->Append(item);
        return copy;
    }

    Sequence<T>* Prepend(T item) override {
        ImmutableListSequence<T>* copy = new ImmutableListSequence(*this);
        copy->items->Prepend(item);
        return copy;
    }

    Sequence<T>* InsertAt(T item, int index) override {
        ImmutableListSequence<T>* copy = new ImmutableListSequence(*this);
        copy->items->InsertAt(item, index);
        return copy;
    }

    Sequence<T>* Concat(Sequence<T>* list) override {
        ImmutableListSequence<T>* new_list = new ImmutableListSequence<T>(*this);
        for (int i = 0; i < list->GetLength(); i++) {
            new_list->items->Append(list->Get(i));
        }
        return new_list;
    }

    template <typename T2>
    Sequence<T2>* Map(T2 (*mapper)(T)) const {
        ImmutableListSequence<T2>* new_list = new ImmutableListSequence<T2>();
        for (int index = 0; index < this->GetLength(); index++) {
            Sequence<T2>* next = new_list->Append(mapper(this->Get(index)));
            delete new_list;
            new_list = static_cast<ImmutableListSequence<T2>*>(next);
        }
        return new_list;
    }

    Sequence<T>* Where(bool (*where)(T)) const override {
        ImmutableListSequence<T>* new_list = new ImmutableListSequence<T>();
        for (int index = 0; index < this->GetLength(); index++) {
            if (where(this->Get(index))) {
                Sequence<T>* next = new_list->Append(this->Get(index));
                delete new_list;
                new_list = static_cast<ImmutableListSequence<T>*>(next);
            }
        }
        return new_list;
    }
};

#endif // IMMUTABLELISTSEQUENCE_H
