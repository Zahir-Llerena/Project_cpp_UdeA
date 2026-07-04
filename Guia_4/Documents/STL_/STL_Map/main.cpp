#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> edades;

    // Insertar pares clave-valor
    edades["Ana"] = 25;
    edades["Carlos"] = 30;
    edades.insert(std::make_pair("Diana", 28));

    // Acceder a valores
    std::cout << "Edad de Ana: " << edades["Ana"] << std::endl;

    // Buscar elementos
    auto it = edades.find("Carlos");
    if (it != edades.end()) {
        std::cout << "Carlos encontrado, edad: " << it->second << std::endl;
    }

    // Iterar sobre el map
    std::cout << "Edades registradas:" << std::endl;
    for(const auto& par : edades) {
        std::cout << par.first << ": " << par.second << std::endl;
    }

    // Eliminar elemento
    edades.erase("Diana");

    return 0;
}
