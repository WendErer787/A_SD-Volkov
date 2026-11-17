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

    bool empty() const noexcept {
        return size == 0;
    }

    std::size_t size() const noexcept {
       return size_;
    }
};