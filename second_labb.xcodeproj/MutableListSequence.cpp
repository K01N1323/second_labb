#include <stdexcept>

template <class T>
class MutableListSequence: public Sequence<T>{
    private:
        LinkedList<T>* items;
    public:
        // constructors
        ListSequence():ListSequence(nullptr, 0){}

        ListSequence(T* items, int count){
            if (items == nullptr){
                this->items = new LinkedList<T>();
            }else{
                this->items = new LinkedList<T>(items, count);
            }
        }

        ListSequence(const LinkedList<T>& list){
            this->items = new LinkedList<T>(list);
        }
        // distructor 
        ~ListSequence(){
            delete this->items;
        }
        // getters
        const T& GetFirst() const override{
            return this->items->GetFirst();
        }

        const T& GetLast() const override{
            return this->items->GetLast();
        }

        const T& Get(int index) const override{
            return this->items->Get(index);
        }

        int GetLength() const override{
            return this->items->GetLength();
        }
        // setters
        Sequence<T>* Append(T item) override{
            this->items->Append(item);

            return this;
        }

        Sequence<T>* Prepend(T item) override{
            this->items->Prepend(item);

            return this;
        }

        Sequence<T>* InsertAt(T item, int index) override{
            this->items->InsertAt(item, index);

            return this;
        }

}