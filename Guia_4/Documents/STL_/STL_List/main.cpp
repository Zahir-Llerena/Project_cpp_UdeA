#include <iostream>
#include <list>

int main() {
    // Crear una lista de strings
    std::list<std::string> nombres = {"Ana", "Carlos", "Diana"};

    // Agregar elementos al frente y al final
    nombres.push_front("Zoe");
    nombres.push_back("Eduardo");

    // Insertar en posición específica
    auto it = nombres.begin();
    std::advance(it, 2); // Mover el iterador a la posición 2
    nombres.insert(it, "Beatriz");

    // Iterar sobre la lista
    std::cout << "Nombres en la lista: ";
    for(const auto& nombre : nombres) {
        std::cout << nombre << " ";
    }
    std::cout << std::endl;

    // Eliminar elementos
    nombres.remove("Carlos"); // Elimina todos los "Carlos"
    nombres.pop_front();      // Elimina el elemento al frente

    return 0;
}
