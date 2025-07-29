#ifndef GULOSO_H
#define GULOSO_H
#include <iostream>
#include <vector>
#include <string>
#include "Grafo.h"

class Guloso
{
    private:
        
    public:
        Guloso()  = default;                                               // CONSTRUTOR
        ~Guloso() = default;                                               // DESTRUTOR

        // RECEBE UM GRAFO E RETORNA O CONJUNTO DE NÓS DA SOLUÇÃO
        std::vector<No*> algoritmo_guloso(Grafo* grafo);
        //       
        //Grafo* algoritmo_guloso_randomizado_adaptativo();
        //
        //Grafo* algoritmo_guloso_randomizado_adaptativo_reativo();       
};




#endif // GULOSO_H
