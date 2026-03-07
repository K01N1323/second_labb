#include <stdexcept>
#include "LinkedList.cpp"
#include "Sequence.cpp"

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

        Sequence<T>* GetSubsequence(int start_index, int end_index) const override{
            LinkedList<T>* raw_list = this->items->GetSubList(start_index, end_index);

            ImmutableListSequence<T>* new_list = new ImmutableListSequence<T>(*raw_list);

            delete raw_list;
            
            return new_list;
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
        // конкатинация 
        Sequence<T>* Concat(Sequence<T>* list) override{
            LinkedList<T>* raw_list = this->items->Concat(list);

            ImmutableListSequence<T>* new_list = new ImmutableListSequence(*raw_list);

            return new_list;
        }
        // map
        template <typename T2>
        Sequence<T2>* Map(T2 (*mapper)(T)) const {
            ImmutableListSequence<T2>* new_list = new ImmutableListSequence<T2>();

            for (int index = 0; index < this->GetLength(); index++){
                new_list->Append(mapper(this->Get(index)));
            }

            return new_list;
        }
        // where 
        Sequence<T>* Where(bool (*where)(T)) const {
            ImmutableListSequence<T>* new_list = new ImmutableListSequence<T>();

            for (int index = 0; index < this->GetLength(); index++){
                if (where(this->Get(index))){
                    new_list->Append(this->Get(index));
                }
            }
            
            return new_list;
        }    
};