#include "Guloso.h"
#include <iostream>  // Para std::cerr, std::cout, std::endl
#include <algorithm>


//######################################################################################
//------------╔════════════════════╗-------------
//------------║  ALGORTIMO GULOSO  ║-------------
//------------╚════════════════════╝-------------
std::vector<No*> Guloso::algoritmo_guloso(Grafo* grafo) {
    //###########################################################################################
    // FALTA IMPLEMENTAR PARA GRAFOS DIRECIONADOS
    if (grafo->isDirecionado()) {
        std::cout << "ALGORITMO IMPLEMENTADO APENAS PARA GRAFOS NAO DIRECIONADOS." << std::endl;
    }
    //###########################################################################################

    // 'S' É O VETOR QUE GUARDARÁ OS NÓS DA SOLUÇÃO FINAL.
    std::vector<No*> S;

    // 'dominados' É UM CONJUNTO (SET) QUE ARMAZENA PONTEIROS PARA OS NÓS JÁ COBERTOS.
    std::set<No*> dominados;

    // 'total_nos' ARMAZENA A ORDEM DO GRAFO (NÚMERO TOTAL DE VÉRTICES).
    int total_nos = grafo->getOrdem();

    // SE O GRAFO ESTIVER VAZIO (NENHUM NÓ), NÃO FAZ NADA.
    if (total_nos == 0) {
        return S;
    }

    //----------------------------------------------------------------------------------
    // ETAPA 1: ESCOLHER O PONTO DE PARTIDA, OU SEJA, O NÓ INICIAL
    //----------------------------------------------------------------------------------

    // VARIÁVEIS PARA GUARDAR O NÓ INICIAL E SEU GRAU
    No* no_inicial = nullptr;
    int max_grau_inicial = -1;

    // PRIMEIRO, PEGAMOS A LISTA DE NÓS E SEU TAMANHO
    const std::vector<No*>& nos_grafo = grafo->getListaNos();
    int num_nos = nos_grafo.size();

    // PERCORRE A LISTA DE NÓS
    for (int i = 0; i < num_nos; ++i) {
        // PEGAMOS O NÓ CORRESPONDENTE AO ÍNDICE 'i'
        No* no_atual = nos_grafo[i];

        // VERIFICAR SE O GRAU DO NÓ ATUAL É O MAIOR JÁ VISTO
        if (static_cast<int>(no_atual->getArestas().size()) > max_grau_inicial) {
            max_grau_inicial = no_atual->getArestas().size();
            no_inicial = no_atual;
        }
    }

    // APÓS ACHAR O NÓ DE MAIOR GRAU, INICIAMOS A SOLUÇÃO COM ELE
    if (no_inicial) {
        S.push_back(no_inicial);
        dominados.insert(no_inicial);
        for (Aresta* aresta : no_inicial->getArestas()) {
            dominados.insert(aresta->getNoAlvo());
        }
    }

    //----------------------------------------------------------------------------------
    // ETAPA 2: LOOP PRINCIPAL DO ALGORITMO GULOSO
    //----------------------------------------------------------------------------------

    // ESTE LOOP PRINCIPAL CONTINUA RODANDO ENQUANTO HOUVER NÓS A SEREM DOMINADOS
    while (static_cast<int>(dominados.size()) < total_nos) {
        
        // ZERA AS VARIÁVEIS DE CONTROLE A CADA NOVA RODADA DO LOOP
        No* melhor_candidato_conectado = nullptr;
        int max_grau_candidato = -1;

        // --- SUB-ETAPA 2.1: IDENTIFICAR OS CANDIDATOS ---
        
        // VETOR VAZIO QUE IRÁ GUARDAR OS CANDIDATOS DESTA RODADA
        std::vector<No*> candidatos; 
        
        // TAMANHO ATUAL DA SOLUÇÃO 'S'
        int tamanho_S = S.size();

        // PARA CADA NÓ QUE JÁ ESTÁ NA SOLUÇÃO 'S'
        for (int i = 0; i < tamanho_S; ++i) { 
            // PEGAMOS O PONTEIRO PARA O NÓ ATUAL EM 'S'
            No* no_em_s = S[i];
            
            // LISTA DE ARESTAS (VIZINHOS) DESTE 'no_em_s'
            const std::vector<Aresta*>& arestas_do_no_em_s = no_em_s->getArestas();
            int num_arestas = arestas_do_no_em_s.size();

            // PERCORRE ESSA LISTA DE VIZINHOS
            for (int j = 0; j < num_arestas; ++j) {
                // PEGAMOS O PONTEIRO PARA O NÓ VIZINHO
                No* vizinho = arestas_do_no_em_s[j]->getNoAlvo();
                
                // VERIFICAR DUAS CONDIÇÕES PARA QUE O 'vizinho' SEJA UM CANDIDATO VÁLIDO:

                // 1. ELE NÃO PODE JÁ ESTAR NA SOLUÇÃO 'S'
                bool vizinho_nao_esta_em_S = (std::find(S.begin(), S.end(), vizinho) == S.end());

                // 2. ELE NÃO PODE JÁ ESTAR NA LISTA DE CANDIDATOS (PARA EVITAR REPETIÇÃO)
                bool vizinho_nao_e_candidato = (std::find(candidatos.begin(), candidatos.end(), vizinho) == candidatos.end());

                // SE AMBAS AS CONDIÇÕES FOREM VERDADEIRAS
                if (vizinho_nao_esta_em_S && vizinho_nao_e_candidato) {
                    // ADICIONA O 'vizinho' À LISTA DE CANDIDATOS!
                    candidatos.push_back(vizinho);
                }
            }
        }

        // --- SUB-ETAPA 2.2: APLICAR A HEURÍSTICA GULOSA ---
        
        // LISTA DE CANDIDATOS ÚNICOS
        int num_candidatos = candidatos.size();

        // PARA CADA CANDIDATO NA LISTA
        for (int k = 0; k < num_candidatos; ++k) {
            // PONTEIRO PARA O CANDIDATO ATUAL
            No* candidato = candidatos[k];
            
            // VERIFICAR SE O GRAU DELE É O MAIOR QUE JÁ VIMOS
            if (static_cast<int>(candidato->getArestas().size()) > max_grau_candidato) {
                // SE FOR, ELE SE TORNA O 'melhor_candidato_conectado' ATÉ O MOMENTO
                max_grau_candidato = candidato->getArestas().size();
                melhor_candidato_conectado = candidato;
            }
        }
        
        // --- SUB-ETAPA 2.3: ATUALIZAR A SOLUÇÃO ---
        
        // AO FINAL, VERIFICA SE ENCONTROU UM MELHOR CANDIDATO
        if (melhor_candidato_conectado) {
            // SE SIM, O ADICIONA À SOLUÇÃO FINAL 'S'
            S.push_back(melhor_candidato_conectado);
            // MARCAR ELE E SEUS VIZINHOS COMO DOMINADOS
            dominados.insert(melhor_candidato_conectado);
            for (Aresta* aresta : melhor_candidato_conectado->getArestas()) {
                dominados.insert(aresta->getNoAlvo());
            }
        } else {
            // SE NÃO ACHOU NENHUM CANDIDATO, SIGNIFICA QUE NÃO HÁ COMO EXPANDIR
            break;
        }
    }

    // RETORNA A SOLUÇÃO ENCONTRADA
    return S;
}

/*
//######################################################################################
//------------╔═══════════════════════════════════════════╗-------------
//------------║  ALGORTIMO GULOSO RANDOMIZADO ADAPTATIVO  ║-------------
//------------╚═══════════════════════════════════════════╝-------------
Grafo* Guloso::algoritmo_guloso_randomizado_adaptativo(){

}
//######################################################################################
//------------╔═══════════════════════════════════════════════════╗-------------
//------------║  ALGORTIMO GULOSO RANDOMIZADO ADAPTATIVO REATIVO  ║-------------
//------------╚═══════════════════════════════════════════════════╝-------------
Grafo* Guloso::algoritmo_guloso_randomizado_adaptativo_reativo(){

}
*/