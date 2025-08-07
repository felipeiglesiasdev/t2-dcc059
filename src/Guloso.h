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
        std::vector<No*> algoritmo_guloso_randomizado_adaptativo(Grafo* grafo);
        //
        std::vector<No*> algoritmo_guloso_randomizado_adaptativo_reativo(Grafo* grafo) ;

};




#endif // GULOSO_H
