template <typename T>
class LinkedList {
    private:
    struct Node{
        T val;
        Node* next;
        explicit Node(const T& NewValue): value(NewValue); next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

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
    LinkedList(): head(nullptr); tail(nullptr); size(0) {}

    ~LinkedList() { clear() }
};