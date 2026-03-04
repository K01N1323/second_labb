#include <stdexcept>
template <class T>
struct Node{
    T num;
    Node* next;
}
class LinkedList{
    private:
        struct Node{
            T data;
            Node* next;

             Node (T value){
                this->data = value;
                this->next = nullptr;
            }
        };
        

        Node* head;
        Node* tail;

        int size
    public:
        LinkedList(){
            this->head = nullptr;
            this->tail = nullptr;
            this->size = 0;
        }
        LinkedList(T* items, int count){
            this->head = nullptr;
            this->tail = nullptr;
            this->size = 0;

            for (int index = 0; index < count; index++){

                Node* new_node = new Node(items[index]);

                if (head == nullptr){
                    head = new_node;
                    tail = new_node;
                }
                else{
                    tail->next = new_node;
                    tail = new_node;
                }
                size++;
            }
        }

}
