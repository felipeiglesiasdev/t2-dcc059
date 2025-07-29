#ifndef GERENCIADOR_H
#define GERENCIADOR_H
#include "Guloso.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Para std::find
#include "Grafo.h"   // Inclui Grafo.h

// Evitar 'using namespace std;' em arquivos .h
class Gerenciador {
public:
    static void comandos(Grafo* grafo);
    static char get_id_entrada();
    static std::vector<char> get_conjunto_ids(Grafo* grafo, int tam);
};

#endif //GERENCIADOR_H