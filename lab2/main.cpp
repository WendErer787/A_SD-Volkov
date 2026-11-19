#include "List.hpp"

int main () {
    try {
        LinkedList<int> list(10, 1, 100, 42);
        std::cout << "List: " << list << '\n';
        std::cout << "Reverse: ";
        print_reverse(list);

        int a = list[6];
        std::cout << "Element 6th: " << a << '\n';

        list.push_head(0);
        list.push_tail(101);
        list.delete_node(50);

        std::cout << "After changes: " << list << '\n';

        LinkedList<int> other(3, 1, 10, 7);
        list.push_head(other);

        std::cout << "After push_head(other): " << list << '\n';

        list.pop_heads();
        list.pop_tails();

        std::cout << "After pop: " << list << '\n';

        other = list;
        std::cout << "Other: " << other << '\n';

    } catch(const std::exception& error) {
        std::cout << "Error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}