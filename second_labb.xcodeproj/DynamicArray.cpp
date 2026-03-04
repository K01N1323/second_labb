#include <stdexcept>
template <class T>

class DynamicArray{
    private:
        T* items;
        int size;
    public:
        // setters
        DynamicArray(int size){
            this->size = size;
            this->items = new T[size];
        }
        DynamicArray(T* items, int count){
            this->size = count;
            this->items = new T[size];

            for (int element = 0; element < size; element++){
                this->items[element] = items[element];
            }
        }
        DynamicArray(const DynamicArray<T>& dynamic_array){
            this->size = dynamic_array.size;
            this->items = new T[size];

            for (int element = 0; element < size; element++){
                items[element] = dynamic_array.items[element];
            }
        }
        // getters
        int GetSize(){
            return this->size;
        }
        T Get(int index){
            if (index < 0 || index >= size){
                throw std::out_of_range("Индекс невалиден");
            }
            return items[index];
        }
        // setters
        void Set(int index, T value){
            if (index < 0 || index >= size){
                throw std::out_of_range("Индекс невалиден");
            }
            items[index] = value;
        }
        // methods
        void Resize(int new_size){
            T* new_items = new T[new_size];
            
            int elements_to_copy = (new_size < size) ? new_size : size;
            for (int element = 0; element < elenents_to_copy; element++){
                new_items[element] = items[element];
            }

            delete[] items;

            this->size = new_size;
            this->items = new_items;
        }
}