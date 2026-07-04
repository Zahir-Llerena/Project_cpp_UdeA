#include <iostream>
#include <vector>

int main() {
    // Crear un vector de enteros
    std::vector<int> numeros = {1, 2, 3, 4, 5};

    std::cout << "Elementos del vector: ";
    for(int num : numeros) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Agregar elementos
    numeros.push_back(6);
    numeros.push_back(7);

    // Acceder a elementos
    std::cout << "Primer elemento: " << numeros[0] << std::endl;
    std::cout << "Tercer elemento: " << numeros.at(2) << std::endl;

    // Iterar sobre el vector
    std::cout << "Elementos del vector: ";
    for(int num : numeros) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Tamaño y capacidad
    std::cout << "Tamano: " << numeros.size() << std::endl;
    std::cout << "Capacidad: " << numeros.capacity() << std::endl;

    // Eliminar el último elemento
    numeros.pop_back();

    return 0;
}
