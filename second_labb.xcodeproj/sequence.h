#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdexcept>

template <class T>
class Sequence {
public:
    virtual ~Sequence() {}

    virtual const T& GetFirst() const = 0;
    virtual const T& GetLast() const = 0;
    virtual const T& Get(int index) const = 0;
    virtual int GetLength() const = 0;

    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;

    virtual Sequence<T>* Append(T item) = 0;
    virtual Sequence<T>* Prepend(T item) = 0;
    virtual Sequence<T>* InsertAt(T item, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;

    const T& operator[](int index) const {
        return this->Get(index);
    }

    template <typename T2>
    Sequence<T2>* Map(T2 (*mapper)(T)) const { return nullptr; }

    virtual Sequence<T>* Where(bool (*where)(T)) const = 0;

    template <typename T2>
    T2 Reduce(T2 (*reduce_func)(T2, T), T2 start_value) const {
        T2 result = start_value;
        for (int index = 0; index < this->GetLength(); index++) {
            result = reduce_func(result, this->Get(index));
        }
        return result;
    }
};

#endif // SEQUENCE_H