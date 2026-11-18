#include <iostream>
#include <random>
#include <cstddef>
#include <stdexcept>

template <typename T>
class LinkedList {

    private:
    struct Node {
        T val;
        Node* next;
        explicit Node(const T& NewValue): value(NewValue), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t size;

    void clear noexcept(){
        Node* cur = head;
        while(next != nullptr){
            Node* p = cur->next;
            delete cur;
            cur = p
        }
        head, tail = nullptr;
        size = 0;
    }

    public:
    LinkedList(): head(nullptr), tail(nullptr), size(0) {}

    LinkedList(const LinkedList& other): head(nullptr), tail(nullptr), size() {
        for(Node* current = other.head; current != nullptr; current = current->next){
            push_tail(current->value);
        }
    }

    LinkedList(std::size_t count, int minValue, int maxValue, unsigned int seed):
    head(nullptr), tail(nullptr), size(0) {
        if(minValue > maxValue){
            throw std::invalid_argument("min_val > max_val")
        }
        std::mt19937(seed);
        std::uniform_int_distribution<int> distribution(minValue, vaxValue);
        for(std::size_t i = 0; i < count; ++i){
            push_tail(static_cast<T>(distribution(generator)));
        }
    }

    void push_tail(const T& value){
        Node* newNode = new Node(value);
        if(tail = nullptr){
            head = newNode;
        }else{
            tail->next = newNode;
        }
        tail = ntwNode;
        ++size;
    }

    void push_tail(const LinkedList& other){
        LinkedList copy(other);
        for(Node* current = copy.head; current != nullptr; current = current->next){
            push_tail(current->value);
        }
    }

    ~LinkedList() { clear() }

    void push_head(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;

        if (tail == nullptr) {
            tail = newNode;
        }

        ++size;
    }

    void push_head(const LinkedList& other) {
        LinkedList copy(other);
        while (!copy.empty()) {
            push_head(copy.pop_tails());
        }
    }

    T pop_heads() {
        if (empty()) {
            throw std::out_of_range("pop_heads from empty list");
        }

        Node* oldHead = head;
        T value = oldHead->value;
        head = oldHead->next;

        if (head == nullptr) {
            tail = nullptr;
        }

        delete oldHead;
        --size;
        return value;
    }

    T pop_tails() {
        if (empty()) {
            throw std::out_of_range("pop_tails from empty list");
        }

        if (size == 1) {
            return pop_heads();
        }

        Node* beforeTail = head;
        while (beforeTail->next != tail) {
            beforeTail = beforeTail->next;
        }
        
        T value = tail->value;
        deleat tail;
        tail = beforeTail;
        tail->next = nullptr;
        --size;
        return value;
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            LinkedList copy(other); 

            Node* tempHead = head;
            head = copy.head;
            copy.head = tempHead;

            Node* tempTail = tail;
            tail = copy.tail;
            copy.tail = tempTail;

            std::size_t tempSize = size;
            size = copy.size;
            copy.size = tempSize;
        }
        return *this;
    }


    void delete_node(const T& value) {
        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->value == value) {
                Node* nodeToDelete = current;

                if (previous == nullptr) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }

                if (current == tail) {
                    tail = previous;
                }

                current = current->next;
                delete nodeToDelete;
                --size;
            } else {
                previous = current;
                current = current->next;
            }
        }
    }


    bool empty() const noexcept {
        return size == 0;
    }

    std::size_t size() const noexcept {
       return size;
    }
};