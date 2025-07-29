#ifndef GRAFO_H
#define GRAFO_H

#include "No.h" // Inclui a definição da classe No
#include <vector>
#include <map>
#include <string>
#include <set>       // Para o gerenciamento de memória no destrutor
#include <limits>    // Para std::numeric_limits<int>::max() em Dijkstra/Floyd
#include <queue>     // Para std::priority_queue em Dijkstra


class Grafo {
    public:
        Grafo();  // CONSTRUTOR
        ~Grafo(); // DESTRUTOR
        //#######################################################################################################################################################
        // MÉTODOS PARA ADICIONA NÓS E ARESTAS
        void add_no(No *novo_no);                                               // ADICIONA NÓ
        void add_aresta(char id_origem, char id_destino, int peso_aresta = 0);  // ADICIONA ARESTA
        //#######################################################################################################################################################
        // SETTERS PARA AS PROPRIEDADES DOS GRAFOS
        void setDirecionado(bool b) { is_direcionado = b; }                     // SETAR GRAFO DIRECIONADO
        void setPonderadoAresta(bool b) { is_ponderado_aresta = b; }            // SETAR ARESTA PONDERADA
        void setPonderadoVertice(bool b) { is_ponderado_vertice = b; }          // SETAR VÉRTICE PONDERADO
        //#######################################################################################################################################################
        // GETTERS PARA AS PROPRIEDADES DOS GRAFOS
        bool isDirecionado() const { return is_direcionado; }                   // VERIFICA SE É DIRECIONADO
        bool isPonderadoAresta() const { return is_ponderado_aresta; }          // VERIFICA SE ARESTA É PONDERADA
        bool isPonderadoVertice() const { return is_ponderado_vertice; }        // VERIFICA SE VÉRTICE É PONDERADO
        int getOrdem() const { return lista_nos.size(); }                       // RETORNA A QUANTIDADE DE VÉRTICES
        No* getNo(char id) const;                                               // RETORNA O NÓ PELO SEU ID
        const std::vector<No*>& getListaNos() const { return lista_nos; }       // RETORNA A LISTA DE NÓS DO GRAFO
        //#######################################################################################################################################################
        // MÉTODOS AUXILIARES
        void imprimirListaDeAdjacencia() const;                                 // IMPRIME O GRAFO EM FORMA DE LISTA DE ADJACENCIA
        void imprimirListaNos() const;                                          // IMPRIME O CONJUNTO DE VÉRTICES DO GRAFO
    private:
        // VARIÁVEIS
        bool is_direcionado;                                                    // VARIAVEL BOOLEANA QUE DIZ SE O GRAFO É DIRECIONADO OU NÃO
        bool is_ponderado_aresta;                                               // VARIAVEL BOOLEANA QUE DIZ SE UMA ARESTA É PONDERADA OU NÃO
        bool is_ponderado_vertice;                                              // VARIAVEL BOOLEANA QUE DIZ SE UM VÉRTICE É PONDERADO OU NÃO
        std::vector<No*> lista_nos;                                             // LISTA QUE ARMAZENA TODOS OS NÓS DO GRAFO
        //#######################################################################################################################################################
        // MAPEAMENTOS
        std::map<char, int> id_para_indice;                                     // MAPEIA O ID (char) DE UM NÓ PARRA SEU ÍNDICE NA lista_nos
};

#endif // GRAFO_H
