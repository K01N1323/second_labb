#include <stdexcept>
#include "LinkedList.cpp"
#include "Sequence.cpp"

template <class T>
class MutableListSequence: public Sequence<T>{
    private:
        LinkedList<T>* items;
    public:
        // constructors
        MutableListSequence():MutableListSequence(nullptr, 0){}

        MutableListSequence(T* items, int count){
            if (items == nullptr){
                this->items = new LinkedList<T>();
            }else{
                this->items = new LinkedList<T>(items, count);
            }
        }

        MutableListSequence(const LinkedList<T>& list){
            this->items = new LinkedList<T>(list);
        }
        // distructor 
        ~MutableListSequence(){
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
        // map
        template <typename T2>
        Sequence<T2>* Map(T2 (*mapper)(T)) const {
            MutableListSequence<T2>* new_list = new MutableListSequence<T2>();

            for (int index = 0; index < this->GetLength(); index++){
                new_list->Append(mapper(this->Get(index)));
            }

            return new_list;
        }
        // where 
        Sequence<T>* Where(bool (*where)(T)) const {
            MutableListSequence<T>* new_list = new MutableListSequence<T>();

            for (int index = 0; index < this->GetLength(); index++){
                if (where(this->Get(index))){
                    new_list->Append(this->Get(index));
                }
            }
            
            return new_list;
        }

};