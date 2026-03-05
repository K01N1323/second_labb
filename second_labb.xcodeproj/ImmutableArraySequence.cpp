#include <stdexcept>

template <class T>
class ImmutableArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* items;

public:
    // constructors
    ImmutableArraySequence() : ImmutableArraySequence(nullptr, 0) {}

    ImmutableArraySequence(T* items, int count) {
        if (items == nullptr || count == 0) {
            this->items = new DynamicArray<T>(0);
        } else {
            this->items = new DynamicArray<T>(items, count); // добавлена ;
        }
    }

    ImmutableArraySequence(const ImmutableArraySequence<T>& other) {
        this->items = new DynamicArray<T>(*other.items); 
    }

    // destructor
    ~ImmutableArraySequence() override { 
        delete this->items;
    }

    // getters
    int GetLength() const override {
        return this->items->GetSize();
    }

    const T& Get(int index) const override {
        return this->items->Get(index);
    }

    Sequence<T>* GetSubsequence(int start_index, int end_index) const override {
    if (start_index < 0 || start_index >= this->GetLength() ||  end_index < 0 || end_index >= this->GetLength() || start_index > end_index) {throw std::out_of_range("Индексы невалидны для данного списка"); }
   
    ArraySequence<T>* result = new ArraySequence<T>();    
    
    for (int index = start_index; index <= end_index; index++) {
        result->Append(this->Get(index));
    }
    return result;
    }
    // methods
    Sequence<T>* Append(T item) override {
        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);
        
        copy->items->Resize(copy->items->GetSize() + 1);
        copy->items->Set(copy->items->GetSize() - 1, item);

        return copy;
    }

    Sequence<T>* Prepend(T item) override {
        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);

        copy->items->Resize(copy->items->GetSize() + 1);

        for (int index = copy->items->GetSize() - 1; index > 0; index--) {
            copy->items->Set(index, copy->items->Get(index - 1));
        }
        
        copy->items->Set(0, item);

        return copy;
    }

    Sequence<T>* InsertAt(T item, int index) override {
        if (index < 0 || index >= this->items->GetSize()) {
            throw std::out_of_range("Индекс вне диапазона");
        }

        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);

        copy->items->Resize(copy->items->GetSize() + 1);

        for (int ind = copy->items->GetSize() - 1; ind > index; ind--) {
            copy->items->Set(ind, copy->items->Get(ind - 1));
        }

        copy->items->Set(index, item);

        return copy;
    }

    Sequence<T>* Concat(Sequence<T>* list) override{
        
    }
};