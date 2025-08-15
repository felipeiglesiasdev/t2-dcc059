#include "Gerenciador.h"
#include <fstream>  // Para std::ofstream
#include <limits>   // Para std::numeric_limits
#include <vector>   // Para std::vector
#include <iostream> // Para std::cout, std::endl, std::cerr
#include <algorithm> // Para std::find
#include <numeric>

void Gerenciador::comandos(Grafo* grafo) {
    while (true) {
        std::cout << "Digite uma das opcoes abaixo e pressione enter:" << std::endl << std::endl;
        std::cout << "(a) Algoritmo Guloso;" << std::endl;
        std::cout << "(b) Algoritmo Guloso Randomizado Adaptativo;" << std::endl;
        std::cout << "(c) Algoritmo Guloso Randomizado Adaptativo Reativo;" << std::endl;
        std::cout << "(d) Media do Algoritmo Guloso (10 execucoes)\n";
        std::cout << "(e) Media do Algoritmo Guloso Randomizado Adaptativo (10 execucoes)\n";
        std::cout << "(f) Media do Algoritmo Guloso Randomizado Adaptativo Reativo (10 execucoes)\n";
        std::cout << "(0) Sair;" << std::endl << std::endl;

        char resp;
        std::cin >> resp;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (resp) {
            // ALGORITMO GULOSO
            case 'a': {
                // INICIALIZAÇÃO DA INSTÂNCIA "Guloso"
                Guloso guloso;
                // CHAMA O ALGORITMO E ARMAZENA O RESULTADO
                std::vector<No*> conjunto_dominante = guloso.algoritmo_guloso(grafo);
                std::cout << "#########################################" << std::endl;
                // IMPRIME O CONJUNTO DE VÉRTICES DO GRAFO 
                grafo->imprimirListaNos();
                // IMPRIME A LISTA DE ADJACÊNCIA DO GRAFO 
                grafo->imprimirListaDeAdjacencia();
                // EXIBIÇÃO DO RESULTADO DO ALGORITMO GULOSO
                std::cout << "\n--- RESULTADO DO ALGORITMO GULOSO ---" << std::endl;
                std::cout << "O conjunto dominante encontrado tem " << conjunto_dominante.size() << " vertices." << std::endl;
                std::cout << "Conjunto S = { ";
                for (size_t i = 0; i < conjunto_dominante.size(); ++i) {
                    std::cout << conjunto_dominante[i]->getId() << (i == conjunto_dominante.size() - 1 ? "" : ", ");
                }
                std::cout << " }" << std::endl << std::endl;
                std::cout << "#########################################" << std::endl;
                break;
            }

            // ALGORITMO GULOSO RANDOMIZADO ADAPTATIVO
            case 'b': {
                // INICIALIZAÇÃO DA INSTÂNCIA "Guloso"
                Guloso guloso;
                // CHAMA O ALGORITMO E ARMAZENA O RESULTADO
                std::vector<No*> conjunto_dominante = guloso.algoritmo_guloso_randomizado_adaptativo(grafo);
                std::cout << "#########################################" << std::endl;
                // IMPRIME O CONJUNTO DE VÉRTICES DO GRAFO 
                grafo->imprimirListaNos();
                // IMPRIME A LISTA DE ADJACÊNCIA DO GRAFO 
                grafo->imprimirListaDeAdjacencia();
                // EXIBIÇÃO DO RESULTADO DO ALGORITMO GULOSO RANDOMIZADO ADAPTATIVO
                std::cout << "\n--- RESULTADO DO ALGORITMO GULOSO RANDOMIZADO ADAPTATIVO ---" << std::endl;
                std::cout << "O conjunto dominante encontrado tem " << conjunto_dominante.size() << " vertices." << std::endl;
                std::cout << "Conjunto S = { ";
                for (size_t i = 0; i < conjunto_dominante.size(); ++i) {
                    std::cout << conjunto_dominante[i]->getId() << (i == conjunto_dominante.size() - 1 ? "" : ", ");
                }
                std::cout << " }" << std::endl << std::endl;
                std::cout << "#########################################" << std::endl;
                break;
            }
            // ALGORITMO GULOSO RANDOMIZADO ADAPTATIVO REATIVO
            case 'c': {
                // INICIALIZAÇÃO DA INSTÂNCIA "Guloso"
                Guloso guloso;
                // CHAMA O ALGORITMO E ARMAZENA O RESULTADO
                std::vector<No*> conjunto_dominante = guloso.algoritmo_guloso_randomizado_adaptativo_reativo(grafo);
                std::cout << "#########################################" << std::endl;
                // IMPRIME O CONJUNTO DE VÉRTICES DO GRAFO 
                grafo->imprimirListaNos();
                // IMPRIME A LISTA DE ADJACÊNCIA DO GRAFO 
                grafo->imprimirListaDeAdjacencia();
                // EXIBIÇÃO DO RESULTADO DO ALGORITMO GULOSO RANDOMIZADO ADAPTATIVO REATIVO
                std::cout << "\n--- RESULTADO DO ALGORITMO GULOSO RANDOMIZADO ADAPTATIVO REATIVO---" << std::endl;
                std::cout << "O conjunto dominante encontrado tem " << conjunto_dominante.size() << " vertices." << std::endl;
                std::cout << "Conjunto S = { ";
                for (size_t i = 0; i < conjunto_dominante.size(); ++i) {
                    std::cout << conjunto_dominante[i]->getId() << (i == conjunto_dominante.size() - 1 ? "" : ", ");
                }
                std::cout << " }" << std::endl << std::endl;
                std::cout << "#########################################" << std::endl;
                break;
            }

            case 'd': {
                std::cout << "###############################################################" << std::endl;
                std::cout << "\n--- MEDIA DO RESULTADO DO ALGORITMO GULOSO (10 EXECUCOES) ---" << std::endl;
                Guloso guloso;
                std::vector<int> tamanhos;
                for (int i = 0; i < 10; ++i) {
                    std::vector<No*> solucao;
                    solucao = guloso.algoritmo_guloso(grafo);
                    int tamanho = solucao.size();
                    tamanhos.push_back(tamanho);
                }
                double media = std::accumulate(tamanhos.begin(), tamanhos.end(), 0.0) / 10.0;
                std::cout << "Para o algoritmo guloso, a media de 10 execucoes eh de " << media << " vertices." << std::endl;
                std::cout << "\n###############################################################" << std::endl;
                break;
            }

            case 'e': {
                std::cout << "###############################################################" << std::endl;
                std::cout << "\n--- MEDIA DO RESULTADO DO ALGORITMO GULOSO RANDOMIZADO ADAPTATIVO (10 EXECUCOES) ---" << std::endl;
                Guloso guloso;
                std::vector<int> tamanhos;
                for (int i = 0; i < 10; ++i) {
                    std::vector<No*> solucao;
                    solucao = guloso.algoritmo_guloso_randomizado_adaptativo(grafo);
                    int tamanho = solucao.size();
                    tamanhos.push_back(tamanho);
                }
                double media = std::accumulate(tamanhos.begin(), tamanhos.end(), 0.0) / 10.0;
                std::cout << "Para o algoritmo guloso randomizado adaptativo, a media de 10 execucoes eh de " << media << " vertices." << std::endl;
                std::cout << "\n###############################################################" << std::endl;
                break;
            }

            case 'f': {
                std::cout << "###############################################################" << std::endl;
                std::cout << "\n--- MEDIA DO RESULTADO DO ALGORITMO GULOSO RANDOMIZADO ADAPTATIVO REATIVO (10 EXECUCOES) ---" << std::endl;
                Guloso guloso;
                std::vector<int> tamanhos;
                for (int i = 0; i < 10; ++i) {
                    std::vector<No*> solucao3;
                    solucao3 = guloso.algoritmo_guloso_randomizado_adaptativo_reativo(grafo);
                    int tamanho = solucao3.size();
                    tamanhos.push_back(tamanho);
                }
                double media = std::accumulate(tamanhos.begin(), tamanhos.end(), 0.000) / 10.00;
                std::cout << "Para o algoritmo guloso randomizado adaptativo reativo, a media de 10 execucoes eh de " << media << " vertices." << std::endl;
                std::cout << "\n###############################################################" << std::endl;
                break;
            }


            // SAIR DO PROGRAMA
            case '0': {
                return;
            }
            // OPÇÃO INVÁLIDA
            default: {
                std::cout << "Opcao invalida" << std::endl;
            }
        }
        std::cout << std::endl;
    }
}

char Gerenciador::get_id_entrada() {
    std::cout << "Digite o id de um no: ";
    char id;
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << std::endl;
    return id;
}

std::vector<char> Gerenciador::get_conjunto_ids(Grafo *grafo, int tam) {
    std::vector<char> ids = {};
    while(static_cast<int>(ids.size()) < tam) { // Corrigido warning de signed/unsigned
        char id_no = get_id_entrada();
        bool existe = false;
        // CORREÇÃO: Usar o método público getNo para verificar a existência do nó
        if (grafo->getNo(id_no) != nullptr) {
            existe = true;
        }

        if(!existe){
            std::cout << "Vertice nao existe no grafo." << std::endl;
        }else{
            bool repetido = std::find(ids.begin(), ids.end(), id_no) != ids.end();
            if(repetido) {
                std::cout << "Valor repetido no subconjunto." << std::endl;
            }else {
                ids.push_back(id_no);
            }
        }
    }
    return ids;
}


