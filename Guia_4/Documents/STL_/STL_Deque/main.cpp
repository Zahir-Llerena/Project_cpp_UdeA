#include <iostream>
#include <deque>

int main() {
    std::deque<int> dq = {2, 3, 4};

    // Agregar elementos en ambos extremos
    dq.push_front(1);
    dq.push_back(5);

    // Acceder a elementos
    std::cout << "Primer elemento: " << dq.front() << std::endl;
    std::cout << "Último elemento: " << dq.back() << std::endl;

    // Iterar con iteradores
    std::cout << "Elementos del deque: ";
    for(auto it = dq.begin(); it != dq.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Eliminar elementos
    dq.pop_front();
    dq.pop_back();

    return 0;
}
