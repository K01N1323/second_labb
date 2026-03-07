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
    // перегрузка оператора []
    const T& operator[](int index)const{
        return this->Get(index);
    }
    // map 
    template <typename T2>
    virtual Sequence<T2>* Map(T2 (*mapper)(T)) const = 0;
    // where 
    virtual Sequence<T>* Where(bool (*where)(T)) const  = 0;
    // reduce 
    template <typename T2>
    T2 Reduce(T2 (*reduce_func)(T2, T), T2 start_value) const{
        T2 result = start_value;

        for (int index = 0; index < this->GetLength(); index++){
            result = reduce_func(result, this->Get(index));
        }

        return result;
    }
};