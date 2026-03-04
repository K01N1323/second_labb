#include "sequence.h"
#include <stdexcept>

template <class T>
class Sequence {
public:
    // destructor
    virtual ~Sequence() {}
    // getters 
    virtual const T& GetFirst() const = 0;
    virtual const T& GetLast() const = 0;
    virtual const T& Get(int index) const = 0;
    virtual int GetLength() const = 0;
    // methods
    // получение подпоследовательности
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
    // операции добавления и вставки
    virtual Sequence<T>* Append(T item) = 0; 
    virtual Sequence<T>* Prepend(T item) = 0; 
    virtual Sequence<T>* InsertAt(T item, int index) = 0;
    // сцепление 
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;
};