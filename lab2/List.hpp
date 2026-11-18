#include <iostream>
#include <random>
#include <cstddef>
#include <stdexcept>

template <typename T>
class LinkedList {

    private:
    struct Node {
        T value;
        Node* next;
        explicit Node(const T& NewValue): value(NewValue), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t _size;

    void clear() noexcept {
        Node* cur = head;
        while(cur != nullptr){
            Node* p = cur->next;
            delete cur;
            cur = p;
        }
        head = nullptr;
        tail = nullptr;
        _size = 0;
    }

    public:
    LinkedList(): head(nullptr), tail(nullptr), _size(0) {}

    LinkedList(const LinkedList& other): head(nullptr), tail(nullptr), _size() {
        for(Node* current = other.head; current != nullptr; current = current->next){
            push_tail(current->value);
        }
    }

    LinkedList(std::size_t count, int minValue, int maxValue, unsigned int seed):
    head(nullptr), tail(nullptr), _size(0) {
        if(minValue > maxValue){
            throw std::invalid_argument("min_val > max_val");
        }
        std::mt19937 generator(seed);
        std::uniform_int_distribution<int> distribution(minValue, maxValue);
        for(std::size_t i = 0; i < count; ++i){
            push_tail(static_cast<T>(distribution(generator)));
        }
    }

    void push_tail(const T& value){
        Node* newNode = new Node(value);
        if(tail == nullptr){
            head = newNode;
        }else{
            tail->next = newNode;
        }
        tail = newNode;
        ++_size;
    }

    void push_tail(const LinkedList& other){
        LinkedList copy(other);
        for(Node* current = copy.head; current != nullptr; current = current->next){
            push_tail(current->value);
        }
    }

    ~LinkedList() { clear(); }

    void push_head(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;

        if (tail == nullptr) {
            tail = newNode;
        }

        ++_size;
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
        --_size;
        return value;
    }

    T pop_tails() {
        if (empty()) {
            throw std::out_of_range("pop_tails from empty list");
        }

        if (_size == 1) {
            return pop_heads();
        }

        Node* beforeTail = head;
        while (beforeTail->next != tail) {
            beforeTail = beforeTail->next;
        }
        
        T value = tail->value;
        delete tail;
        tail = beforeTail;
        tail->next = nullptr;
        --_size;
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

            std::size_t tempSize = _size;
            _size = copy._size;
            copy._size = tempSize;
        }
        return *this;
    }

    T& operator[](std::size_t index) {
        if (index >= _size) {
            throw std::out_of_range("index is out of range");
        }

        Node* current = head;
        for (std::size_t i = 0; i < index; ++i) {
            current = current->next;
        }

        return current->value;
    }

    const T& operator[](std::size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("index is out of range");
        }

        Node* current = head;
        for (std::size_t i = 0; i < index; ++i) {
            current = current->next;
        }

        return current->value;
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
                --_size;
            } else {
                previous = current;
                current = current->next;
            }
        }
    }


    bool empty() const noexcept {
        return _size == 0;
    }

    std::size_t size() const noexcept {
       return _size;
    }

    friend std::ostream& operator<<(std::ostream& out, const LinkedList& list) {
        out << '[';

        Node* current = list.head;
        bool first = true;

        while (current != nullptr) {
            if (!first) {
                out << ", ";
            }

            out << current->value;
            first = false;
            current = current->next;
        }

        out << ']';
        return out;
    }
};