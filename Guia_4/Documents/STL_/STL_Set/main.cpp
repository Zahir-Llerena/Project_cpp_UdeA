#include <iostream>
#include <set>

int main() {
    std::set<int> conjunto = {5, 2, 8, 2, 1}; // El 2 duplicado se ignora

    // Insertar elementos
    conjunto.insert(3);
    conjunto.insert(7);

    // Buscar elementos
    auto search = conjunto.find(5);
    if (search != conjunto.end()) {
        std::cout << "5 encontrado en el conjunto" << std::endl;
    }

    // Iterar (los elementos están ordenados)
    std::cout << "Elementos del conjunto: ";
    for(int num : conjunto) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Eliminar elemento
    conjunto.erase(2);

    std::cout << "Elementos del conjunto: ";
    for(int num : conjunto) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
