#include <stdexcept>

template <class T>
class ImmutableListSequence: public Sequence<T>{
    private:
        LinkedList<T>* items;
    public:
        // constructors
        ImmutableListSequence():ImmutableListSequence(nullptr, 0){}

        ImmutableListSequence(T* items, int count){
            if (items == nullptr){
                this->items = new LinkedList<T>();
            }else{
                this->items = new LinkedList<T>(items, count);
            }
        }

        ImmutableListSequence(const LinkedList<T>& list){
            this->items = new LinkedList<T>(list);
        }
        // distructor 
        ~ImmutableListSequence(){
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
            ImmutableListSequence<T>* sub_list_sequence = new ImmutableListSequence(*this);

            sub_list_sequence->items->Append(item);

            return sub_list_sequence;
        }

        Sequence<T>* Prepend(T item) override{
            ImmutableListSequence<T>* sub_list_sequence = new ImmutableListSequence(*this);

            sub_list_sequence->items->Prepend(item);

            return sub_list_sequence;
        }

        Sequence<T>* InsertAt(T item, int index) override{
            ImmutableListSequence<T>* sub_list_sequence = new ImmutableListSequence(*this);

            sub_list_sequence->items->InsertAt(item, index);

            return sub_list_sequence;    
        }

}