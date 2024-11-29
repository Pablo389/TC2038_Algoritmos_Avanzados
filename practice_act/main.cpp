#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: ./a.out <problema> <archivo_entrada.txt>" << std::endl;
        return 1;
    }

    std::string problem = argv[1];
    std::string input_file = argv[2];

    if (problem == "SheepFence") {
        std::string command = "g++ SheepFence.cpp -o s.out && ./s.out < " + input_file;
        system(command.c_str());
    } else if (problem == "TelecomTowers") {
        std::string command = "g++ TelecomTowers.cpp -o t.out && ./t.out < " + input_file;
        system(command.c_str());
    } else {
        std::cerr << "Problema desconocido. Debes especificar 'SheepFence' o 'TelecomTowers'." << std::endl;
        return 1;
    }

    return 0;
}
