#include "Grafo.h"
#include <algorithm> // Para usar std::find_if, std::sort
#include <iostream>  // Para std::cerr, std::cout, std::endl
#include <set>       // Para o gerenciamento de memória no destrutor
#include <queue>     // Para std::priority_queue em Dijkstra
#include <stack>     // Para DFS iterativo
#include <limits>    // Para std::numeric_limits<int>::max()

//######################################################################################
//------------╔══════════════╗-------------
//------------║  CONSTRUTOR  ║-------------
//------------╚══════════════╝-------------
Grafo::Grafo() :
    // INICIALIZA AS PROPRIEDADES BOOLEANAS (FLAGS) DO GRAFO COMO FALSAS POR PADRÃO
    is_direcionado(false),
    is_ponderado_aresta(false),
    is_ponderado_vertice(false) {
}
//######################################################################################
//------------╔═════════════╗-------------
//------------║  DESTRUTOR  ║-------------
//------------╚═════════════╝-------------
Grafo::~Grafo() {
    std::set<Aresta*> arestas_para_deletar; // COLETA TODAS AS ARESTAS ÚNICAS EM UM 'SET'.
    for (No* no : lista_nos) { // LOOP PELOS NÓS DA lista_nos
        if (no) { // SE O NÓ EXISTE
            for (Aresta* aresta : no->getArestas()) { // PEGA A ARESTAS DO NÓ
                arestas_para_deletar.insert(aresta); // INSERE A ARRESTA EM arestas_para_deletar
            }
        }
    }
    for (Aresta* aresta : arestas_para_deletar) 
        delete aresta; // DELETA CADA ARESTA.
    for (No* no : lista_nos) 
        delete no; // DELETA CADA NÓ.
}
//######################################################################################
//------------╔══════════════════════════╗-------------
//------------║  MÉTODOS DE ADIÇÃO DE NÓ ║-------------
//------------╚══════════════════════════╝-------------
// ESTE MÉTODO ADICIONA UM NOVO NÓ (VÉRTICE) AO GRAFO.
// PRIMEIRO, ELE VERIFICA SE JÁ EXISTE UM NÓ COM O MESMO ID PARA EVITAR
// DUPLICATAS. SE NÃO EXISTIR, O NÓ É ADICIONADO À 'LISTA_NOS' E O
// MAPEAMENTO DE SEU ID PARA SEU ÍNDICE NO VETOR É CRIADO EM 'ID_PARA_INDICE'.
void Grafo::add_no(No *novo_no) {
    if (id_para_indice.count(novo_no->getId()) > 0) {
        std::cerr << "Erro: No com ID '" << novo_no->getId() << "' ja existe no grafo. No nao adicionado." << std::endl;
        delete novo_no;
        return;
    }
    int novo_indice = lista_nos.size();
    lista_nos.push_back(novo_no);
    id_para_indice[novo_no->getId()] = novo_indice;
}
//######################################################################################
//------------╔═════════════════════════════╗-------------
//------------║  MÉTODOS DE ADIÇÃO DE ARESTA║-------------
//------------╚═════════════════════════════╝-------------
void Grafo::add_aresta(char id_origem, char id_destino, int peso_aresta) {
    No* no_origem = getNo(id_origem);
    No* no_destino = getNo(id_destino);
    if (no_origem == nullptr || no_destino == nullptr) {
        std::cerr << "Erro: Tentativa de adicionar aresta com ID(s) de nó inválido(s) ("
                  << id_origem << " ou " << id_destino << " não encontrados)." << std::endl;
        return;
    }
    bool aresta_ja_existe = false;
    for(Aresta* a : no_origem->getArestas()){
        if(a->getNoAlvo()->getId() == id_destino){
            aresta_ja_existe = true;
            break;
        }
    }
    if (!aresta_ja_existe) {
        Aresta* aresta_saida = new Aresta(no_destino, peso_aresta);
        no_origem->add_aresta(aresta_saida);
        std::cout << "Aresta adicionada: " << no_origem->getId() << " -> " << no_destino->getId();
        if (is_ponderado_aresta) 
            std::cout << " (peso: " << peso_aresta << ")";
        std::cout << std::endl;
        if (!is_direcionado) {
            bool aresta_inversa_ja_existe = false;
            for(Aresta* a : no_destino->getArestas()){
                if(a->getNoAlvo()->getId() == id_origem){
                    aresta_inversa_ja_existe = true;
                    break;
                }
            }
            if (!aresta_inversa_ja_existe) {
                Aresta* aresta_entrada = new Aresta(no_origem, peso_aresta);
                no_destino->add_aresta(aresta_entrada);
                std::cout << "Aresta reversa adicionada: " << no_destino->getId() << " -> " << no_origem->getId();
                if (is_ponderado_aresta) 
                    std::cout << " (peso: " << peso_aresta << ")";
                std::cout << std::endl << std::endl;
            }
        }
    } else std::cout << "Aresta " << id_origem << " -> " << id_destino << " já existe. Não adicionada novamente." << std::endl;
}

//######################################################################################
//------------╔══════════════════════════════╗-------------
//------------║  MÉTODOS DE BUSCA DE NÓ (GET)║-------------
//------------╚══════════════════════════════╝-------------
No* Grafo::getNo(char id) const {
    auto it = id_para_indice.find(id);
    if (it != id_para_indice.end()) {
        int indice = it->second;
        return lista_nos[indice];
    }
    return nullptr;
}
//######################################################################################
//------------╔═════════════════════════════════════════════════════╗-------------
//------------║  LISTA DE ADJACÊNCIA DO GRAFO (IMPRESSÃO DO GRAFO)  ║-------------
//------------╚═════════════════════════════════════════════════════╝-------------
void Grafo::imprimirListaDeAdjacencia() const {
    std::cout << "\n--- LISTA DE ADJACENCIA DO GRAFO ---" << std::endl;
    for (const No* no_origem : this->lista_nos) {
        std::cout << no_origem->getId() << ": -> ";
        const std::vector<Aresta*>& arestas = no_origem->getArestas();
        if (arestas.empty()) {
            std::cout << "[NENHUMA CONEXAO]";
        } else {
            // USA UM LOOP COM ÍNDICE PARA SABER QUANDO NÃO COLOCAR A VÍRGULA
            for (size_t i = 0; i < arestas.size(); ++i) {
                const Aresta* aresta = arestas[i];
                No* no_destino = aresta->getNoAlvo();
                std::cout << "[" << no_destino->getId();
                // ADICIONA A INFORMAÇÃO DO PESO APENAS SE O GRAFO FOR PONDERADO
                if (isPonderadoAresta()) {
                    std::cout << " (Peso: " << aresta->getPeso() << ")";
                }
                std::cout << "]";
                // ADICIONA UMA VÍRGULA COMO SEPARADOR, EXCETO APÓS O ÚLTIMO ELEMENTO
                if (i < arestas.size() - 1) {
                    std::cout << " -> ";
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
}
//######################################################################################
//------------╔═════════════════════════════╗-------------
//------------║  IMPRESSÃO DA LISTA DE NÓS  ║-------------
//------------╚═════════════════════════════╝-------------
void Grafo::imprimirListaNos() const {
    std::cout << "\n--- CONJUNTO DE VERTICES DO GRAFO ---" << std::endl;
    const std::vector<No*>& nos = this->getListaNos();
    if (nos.empty()) {
        std::cout << "V = { }" << std::endl; // GRAFO VAZIO
        return;
    }
    std::cout << "V = { ";
    for (size_t i = 0; i < nos.size(); ++i) {
        std::cout << nos[i]->getId() << (i == nos.size() - 1 ? "" : ", ");
    }
    std::cout << " }" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
}