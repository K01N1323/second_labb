#include <stdexcept>

template <class T>
class MutableArraySequence: public Sequence<T>{
    private:
        DynamicArray<T>* items;
    public:
        // constructor
        ArraySequence():ArraySequence(nullptr, 0){}

        ArraySequence(T* items, int count){
            if (items == nullptr){
                this->items = new DynamicArray<T>(0);
            }else{
                this->items = new DynamicArray<T>(items, count)
            }
        }
        // distructor
        ~ArraySequence(){
            delete this->items;
        }
        // getters
        int GetLength()const override{
            return this->items->GetSize();
        }

        const T& Get(int index)const override{
            return this->items->Get(index);
        }
        // setters
        // вставка в конец
        Sequence<T>* Append(T item) override{
            items->Resize(items->GetSize() + 1);
            items->Set(this->GetSize() - 1, item);

            return this;
        }
        // вставка в начало
        Sequence<T>* Prepend(T item) override{
            items->Resize(items->GetSize() + 1);

            for (int index = (items->GetSize() - 1); index > 0; index--){
                items->Set(index, items->Get(index - 1));
            }
            
            items->Set(0, item);

            return this;
        }
        // вставка по индексу
        Sequence<T>* InsertAt(T item, int index) override{
            if (index < 0 || index >= this->items->GetSize()){
                throw std::out_of_range("Индекс вне диапазона");
            }

            items->Resize(items->GetSize() + 1);

            for (int ind = (items->GetSize() - 1); index > 0; ind--){
                if (ind == index) break;
                items->Set(ind, items->Get(ind - 1));
            }

            items->Set(index, item);

            return this;
        }
}