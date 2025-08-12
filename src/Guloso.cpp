#include "Guloso.h"
#include <iostream>  // Para std::cerr, std::cout, std::endl
#include <algorithm>
#include <random>
#include <limits>


//###############################################################################################
//-------------------------------╔════════════════════╗------------------------------------------
//-------------------------------║  ALGORTIMO GULOSO  ║------------------------------------------
//-------------------------------╚════════════════════╝------------------------------------------
std::vector<No*> Guloso::algoritmo_guloso(Grafo* grafo) {

    //===========================================================================================
    // =============================== GRAFOS NÃO DIRECIONADOS ======================================
    //===========================================================================================
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
    // ESCOLHER O PONTO DE PARTIDA, OU SEJA, O NÓ INICIAL
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
    // LOOP PRINCIPAL DO ALGORITMO GULOSO
    //----------------------------------------------------------------------------------

    // ESTE LOOP PRINCIPAL CONTINUA RODANDO ENQUANTO HOUVER NÓS A SEREM DOMINADOS
    while (static_cast<int>(dominados.size()) < total_nos) {
        
        // ZERA AS VARIÁVEIS DE CONTROLE A CADA NOVA RODADA DO LOOP
        No* melhor_candidato_conectado = nullptr;
        int max_grau_candidato = -1;

        // IDENTIFICAR OS CANDIDATOS 
        
        // VETOR VAZIO QUE IRÁ GUARDAR OS CANDIDATOS DESTA RODADA
        std::vector<No*> candidatos; 
        
        // TAMANHO ATUAL DA SOLUÇÃO 'S'
        int tamanho_S = S.size();

        // PARA CADA NÓ QUE JÁ ESTÁ NA SOLUÇÃO 'S'
        for (int i = 0; i < tamanho_S; i++) { 
            // PEGAMOS O PONTEIRO PARA O NÓ ATUAL EM 'S'
            No* no_em_s = S[i];
            
            // LISTA DE ARESTAS (VIZINHOS) DESTE 'no_em_s'
            const std::vector<Aresta*>& arestas_do_no_em_s = no_em_s->getArestas();
            int num_arestas = arestas_do_no_em_s.size();

            // PERCORRE ESSA LISTA DE VIZINHOS
            for (int j = 0; j < num_arestas; j++) {
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

        // APLICAR A HEURÍSTICA GULOSA 
        
        // LISTA DE CANDIDATOS ÚNICOS
        int num_candidatos = candidatos.size();

        // PARA CADA CANDIDATO NA LISTA
        for (int k = 0; k < num_candidatos; k++) {
            // PONTEIRO PARA O CANDIDATO ATUAL
            No* candidato = candidatos[k];
            
            // VERIFICAR SE O GRAU DELE É O MAIOR QUE JÁ VIMOS
            if (static_cast<int>(candidato->getArestas().size()) > max_grau_candidato) {
                // SE FOR, ELE SE TORNA O 'melhor_candidato_conectado' ATÉ O MOMENTO
                max_grau_candidato = candidato->getArestas().size();
                melhor_candidato_conectado = candidato;
            }
        }
        
        // ATUALIZAR A SOLUÇÃO 
        
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


//######################################################################################
//--------------------╔═══════════════════════════════════════════╗---------------------
//--------------------║  ALGORTIMO GULOSO RANDOMIZADO ADAPTATIVO  ║---------------------
//--------------------╚═══════════════════════════════════════════╝---------------------
std::vector<No*> Guloso::algoritmo_guloso_randomizado_adaptativo(Grafo* grafo) {
    //==================================================================================
    // INICIALIZAÇÃO  
    //==================================================================================
    const int max_iteracoes = 50;
    const double alfa = 0.2;

    std::vector<No*> melhor_solucao_global;
    int tamanho_melhor_solucao = std::numeric_limits<int>::max();
    int total_nos = grafo->getOrdem();
    const auto& nos_grafo = grafo->getListaNos();
    if (total_nos == 0) return melhor_solucao_global;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::cout << "\n--- EXECUTANDO GRASP PARA CONJUNTO DOMINANTE CONECTADO ---" << std::endl;
    std::cout << "Numero de iteracoes (fixo): " << max_iteracoes << ", Alfa (fixo): " << alfa << std::endl << std::endl;

    //==================================================================================
    // LOOP PRINCIPAL DO GRASP  
    //==================================================================================

    for (int i = 0; i < max_iteracoes; ++i) {
        //==================================================================================
        // CONSTRUÇÃO DA SOLUÇÃO (ESTRATÉGIA DE CRESCIMENTO)
        //==================================================================================
        std::vector<No*> solucao_atual;
        std::set<No*> dominados;
        
        // HEURÍSTICA: COMEÇAR PELO NÓ DE MAIOR GRAU PARA MAXIMIZAR A COBERTURA INICIAL.
        No* no_inicial = nullptr;
        int max_grau = -1;
        for(No* n : nos_grafo){
            if((int)n->getArestas().size() > max_grau){
                max_grau = n->getArestas().size();
                no_inicial = n;
            }
        }
        
        // ADICIONA O NÓ INICIAL À SOLUÇÃO E ATUALIZA.
        if (no_inicial) {
            solucao_atual.push_back(no_inicial);
            dominados.insert(no_inicial);
            for (Aresta* aresta : no_inicial->getArestas()) {
                dominados.insert(aresta->getNoAlvo());
            }
        }

        // --- LOOP DE CRESCIMENTO DA SOLUÇÃO ---
        // CONTINUA ATÉ QUE TODOS OS NÓS ESTEJAM DOMINADOS.
        while (dominados.size() < (size_t)total_nos) {
            std::map<No*, int> ganhos_candidatos;
            int ganho_max = -1;
            int ganho_min = std::numeric_limits<int>::max();

            // UM CANDIDATO VÁLIDO AGORA PRECISA SER VIZINHO DE ALGUÉM JÁ NA SOLUÇÃO
            // PARA GARANTIR QUE A SOLUÇÃO CRESÇA DE FORMA CONECTADA.
            std::set<No*> set_candidatos_conectados;
            for(No* no_em_s : solucao_atual) { // Para cada nó já na solução
                for(Aresta* aresta : no_em_s->getArestas()){ // Olhe seus vizinhos
                    No* vizinho = aresta->getNoAlvo();
                    // Se o vizinho ainda não está na solução, ele é um candidato válido.
                    if(std::find(solucao_atual.begin(), solucao_atual.end(), vizinho) == solucao_atual.end()){
                        set_candidatos_conectados.insert(vizinho);
                    }
                }
            }
            
            // SE NÃO HÁ CANDIDATOS PARA EXPANDIR A SOLUÇÃO, INTERROMPE A CONSTRUÇÃO.
            if(set_candidatos_conectados.empty()) break;

            // CALCULA O GANHO (NOVOS NÓS DOMINADOS) PARA CADA CANDIDATO VÁLIDO.
            for (No* candidato : set_candidatos_conectados) {
                int ganho_atual = 0;
                // O candidato em si não precisa ser verificado, pois ele já é vizinho de 'S' e,
                // portanto, já está dominado. Apenas seus vizinhos importam.
                for (Aresta* aresta : candidato->getArestas()) {
                    if (dominados.find(aresta->getNoAlvo()) == dominados.end()) {
                        ganho_atual++;
                    }
                }
                ganhos_candidatos[candidato] = ganho_atual;
                if (ganho_atual > ganho_max) ganho_max = ganho_atual;
                if (ganho_atual < ganho_min) ganho_min = ganho_atual;
            }

            if (ganho_max <= 0) break;

            // CONSTRÓI A LRC COM BASE NOS CANDIDATOS VÁLIDOS.
            double limiar = ganho_max - alfa * (ganho_max - ganho_min);
            std::vector<No*> lrc;
            for (auto const& [candidato, ganho] : ganhos_candidatos) {
                if (ganho >= limiar) lrc.push_back(candidato);
            }
            
            if (lrc.empty()) break;

            // SORTEIA UM NÓ DA LRC E O ADICIONA À SOLUÇÃO.
            std::uniform_int_distribution<> distrib(0, lrc.size() - 1);
            No* escolhido = lrc[distrib(gen)];
            solucao_atual.push_back(escolhido);
            dominados.insert(escolhido); // O nó escolhido agora também está dominado.
            for (Aresta* aresta : escolhido->getArestas()) {
                dominados.insert(aresta->getNoAlvo());
            }
        } 

        //==================================================================================
        // BUSCA LOCAL (COM VERIFICAÇÃO DE CONECTIVIDADE)
        //==================================================================================
        bool houve_melhora = true;
        while (houve_melhora) {
            houve_melhora = false;
            for (size_t k = 0; k < solucao_atual.size(); ++k) {
                No* no_a_remover = solucao_atual[k];
                std::vector<No*> solucao_temporaria;
                for(No* no : solucao_atual) if(no->getId() != no_a_remover->getId()) solucao_temporaria.push_back(no);

                // --- VERIFICAÇÃO 1: DOMINAÇÃO ---
                std::set<No*> nos_cobertos;
                for (No* n : solucao_temporaria) {
                    nos_cobertos.insert(n);
                    for (Aresta* a : n->getArestas()) nos_cobertos.insert(a->getNoAlvo());
                }
                
                // SE A DOMINAÇÃO FALHAR, A REMOÇÃO É INVÁLIDA.
                if (nos_cobertos.size() < (size_t)total_nos) continue;

                // --- VERIFICAÇÃO 2: CONECTIVIDADE ---
                bool eh_conectado = false;
                if(solucao_temporaria.empty() || solucao_temporaria.size() == 1){
                    eh_conectado = true; // Solução de 0 ou 1 nó é considerada conectada.
                } else {
                    // USA UMA BUSCA EM LARGURA (BFS) PARA VERIFICAR A CONECTIVIDADE.
                    std::set<No*> visitados_bfs;
                    std::queue<No*> fila_bfs;
                    
                    // INICIA A BUSCA A PARTIR DO PRIMEIRO NÓ DA SOLUÇÃO TEMPORÁRIA.
                    fila_bfs.push(solucao_temporaria[0]);
                    visitados_bfs.insert(solucao_temporaria[0]);
                    
                    while(!fila_bfs.empty()){
                        No* atual_bfs = fila_bfs.front();
                        fila_bfs.pop();

                        // OLHA OS VIZINHOS DO NÓ ATUAL DA BUSCA.
                        for(Aresta* aresta : atual_bfs->getArestas()){
                            No* vizinho_bfs = aresta->getNoAlvo();
                            
                            // VERIFICA SE O VIZINHO PERTENCE À SOLUÇÃO TEMPORÁRIA E AINDA NÃO FOI VISITADO.
                            bool esta_na_solucao_temp = std::find(solucao_temporaria.begin(), solucao_temporaria.end(), vizinho_bfs) != solucao_temporaria.end();
                            bool nao_foi_visitado = visitados_bfs.find(vizinho_bfs) == visitados_bfs.end();

                            if(esta_na_solucao_temp && nao_foi_visitado){
                                visitados_bfs.insert(vizinho_bfs);
                                fila_bfs.push(vizinho_bfs);
                            }
                        }
                    }
                    // SE O NÚMERO DE NÓS VISITADOS NA BUSCA FOR IGUAL AO TAMANHO DA SOLUÇÃO, ELA ESTÁ CONECTADA.
                    if(visitados_bfs.size() == solucao_temporaria.size()) eh_conectado = true;
                }

                // SE AMBAS AS CONDIÇÕES (DOMINAÇÃO E CONECTIVIDADE) FOREM VERDADEIRAS, A REMOÇÃO É VÁLIDA.
                if (eh_conectado) {
                    solucao_atual = solucao_temporaria;
                    houve_melhora = true;
                    break;
                }
            }
        }
        
        //==================================================================================
        // ATUALIZAÇÃO DA MELHOR SOLUÇÃO GLOBAL
        //==================================================================================
        if (solucao_atual.size() < (size_t)tamanho_melhor_solucao) {
            melhor_solucao_global = solucao_atual;
            tamanho_melhor_solucao = solucao_atual.size();
            std::cout << "Iteracao " << i + 1 << ": Nova melhor solucao CONECTADA encontrada (tamanho " << tamanho_melhor_solucao << ")" << std::endl;
        }
    }
    return melhor_solucao_global;
}



//######################################################################################
//------------╔═══════════════════════════════════════════════════╗-------------
//------------║  ALGORTIMO GULOSO RANDOMIZADO ADAPTATIVO REATIVO  ║-------------
//------------╚═══════════════════════════════════════════════════╝-------------
std::vector<No*> Guloso::algoritmo_guloso_randomizado_adaptativo_reativo(Grafo* grafo) {
    //######################################################################################
    //------------╔═════════════════════════════════╗-------------
    //------------║      ETAPA 1: INICIALIZAÇÃO     ║-------------
    //------------╚═════════════════════════════════╝-------------

    //--- PARÂMETROS FIXOS DO GRASP REATIVO ---
    const int max_iteracoes = 100; // AUMENTAMOS AS ITERAÇÕES PARA DAR TEMPO AO ALGORITMO DE APRENDER.
    const int intervalo_atualizacao = 20; // A CADA 20 ITERAÇÕES, AS PROBABILIDADES SERÃO RECALCULADAS.

    //--- MECANISMO REATIVO: CONJUNTO DE ALFAS E ESTATÍSTICAS ---
    // ESTE É O "CARDÁPIO" DE VALORES DE ALFA QUE O ALGORITMO PODE ESCOLHER.
    std::vector<double> conjunto_alfas = {0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40};
    // 'somas_solucoes' GUARDA A SOMA DOS TAMANHOS DE TODAS AS SOLUÇÕES GERADAS POR CADA ALFA.
    std::vector<double> somas_solucoes(conjunto_alfas.size(), 0.0);
    // 'usos_alfa' CONTA QUANTAS VEZES CADA ALFA FOI USADO.
    std::vector<int> usos_alfa(conjunto_alfas.size(), 0);
    // 'probabilidades_alfa' GUARDA A PROBABILIDADE DE CADA ALFA SER ESCOLHIDO. COMEÇA UNIFORME.
    std::vector<double> probabilidades_alfa(conjunto_alfas.size(), 1.0 / conjunto_alfas.size());

    //--- INICIALIZAÇÃO PADRÃO ---
    std::vector<No*> melhor_solucao_global;
    int tamanho_melhor_solucao = std::numeric_limits<int>::max();
    int total_nos = grafo->getOrdem();
    const auto& nos_grafo = grafo->getListaNos();
    if (total_nos == 0) return melhor_solucao_global;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::cout << "\n--- EXECUTANDO GRASP REATIVO PARA CDC ---" << std::endl;
    std::cout << "Numero de iteracoes: " << max_iteracoes << std::endl;

    //######################################################################################
    //------------╔═════════════════════════════════╗-------------
    //------------║   ETAPA 2: LOOP PRINCIPAL DO GRASP  ║-------------
    //------------╚═════════════════════════════════╝-------------
    for (int i = 0; i < max_iteracoes; ++i) {
        
        //--- SELEÇÃO REATIVA DO ALFA ---
        // SORTEIA UM ALFA DO CONJUNTO BASEADO NAS PROBABILIDADES ATUAIS.
        std::discrete_distribution<> dist_alfas(probabilidades_alfa.begin(), probabilidades_alfa.end());
        int indice_alfa_escolhido = dist_alfas(gen);
        double alfa = conjunto_alfas[indice_alfa_escolhido];

        //==================================================================================
        // FASE 2.1: CONSTRUÇÃO (IDÊNTICA À ANTERIOR, MAS USANDO O ALFA SORTEADO)
        //==================================================================================
        std::vector<No*> solucao_atual;
        std::set<No*> dominados;
        // (O restante da lógica de construção para CDC é exatamente o mesmo...)
        No* no_inicial = nullptr; int max_grau = -1;
        for(No* n : nos_grafo) if((int)n->getArestas().size() > max_grau){ max_grau = n->getArestas().size(); no_inicial = n; }
        if (no_inicial) {
            solucao_atual.push_back(no_inicial);
            dominados.insert(no_inicial);
            for (Aresta* aresta : no_inicial->getArestas()) dominados.insert(aresta->getNoAlvo());
        }
        while (dominados.size() < (size_t)total_nos) {
            std::map<No*, int> ganhos_candidatos; int ganho_max = -1; int ganho_min = std::numeric_limits<int>::max();
            std::set<No*> set_candidatos_conectados;
            for(No* no_em_s : solucao_atual) for(Aresta* aresta : no_em_s->getArestas()){ No* vizinho = aresta->getNoAlvo(); if(std::find(solucao_atual.begin(), solucao_atual.end(), vizinho) == solucao_atual.end()) set_candidatos_conectados.insert(vizinho); }
            if(set_candidatos_conectados.empty()) break;
            for (No* candidato : set_candidatos_conectados) {
                int ganho_atual = 0;
                for (Aresta* aresta : candidato->getArestas()) if (dominados.find(aresta->getNoAlvo()) == dominados.end()) ganho_atual++;
                ganhos_candidatos[candidato] = ganho_atual;
                if (ganho_atual > ganho_max) ganho_max = ganho_atual; if (ganho_atual < ganho_min) ganho_min = ganho_atual;
            }
            if (ganho_max <= 0) break;
            double limiar = ganho_max - alfa * (ganho_max - ganho_min);
            std::vector<No*> lrc;
            for (auto const& [candidato, ganho] : ganhos_candidatos) if (ganho >= limiar) lrc.push_back(candidato);
            if (lrc.empty()) break;
            std::uniform_int_distribution<> distrib(0, lrc.size() - 1);
            No* escolhido = lrc[distrib(gen)];
            solucao_atual.push_back(escolhido);
            dominados.insert(escolhido);
            for (Aresta* aresta : escolhido->getArestas()) dominados.insert(aresta->getNoAlvo());
        }

        //==================================================================================
        // FASE 2.2: BUSCA LOCAL (IDÊNTICA À ANTERIOR)
        //==================================================================================
        // (A lógica de Busca Local para CDC é exatamente a mesma...)
        bool houve_melhora = true;
        while (houve_melhora) {
            houve_melhora = false;
            for (size_t k = 0; k < solucao_atual.size(); ++k) {
                No* no_a_remover = solucao_atual[k];
                std::vector<No*> solucao_temporaria;
                for(No* no : solucao_atual) if(no->getId() != no_a_remover->getId()) solucao_temporaria.push_back(no);
                std::set<No*> nos_cobertos;
                for (No* n : solucao_temporaria) { nos_cobertos.insert(n); for (Aresta* a : n->getArestas()) nos_cobertos.insert(a->getNoAlvo()); }
                if (nos_cobertos.size() < (size_t)total_nos) continue;
                bool eh_conectado = false;
                if(solucao_temporaria.empty() || solucao_temporaria.size() == 1){ eh_conectado = true; } else {
                    std::set<No*> visitados_bfs; std::queue<No*> fila_bfs;
                    fila_bfs.push(solucao_temporaria[0]); visitados_bfs.insert(solucao_temporaria[0]);
                    while(!fila_bfs.empty()){
                        No* atual_bfs = fila_bfs.front(); fila_bfs.pop();
                        for(Aresta* aresta : atual_bfs->getArestas()){
                            No* vizinho_bfs = aresta->getNoAlvo();
                            bool esta_na_solucao_temp = std::find(solucao_temporaria.begin(), solucao_temporaria.end(), vizinho_bfs) != solucao_temporaria.end();
                            bool nao_foi_visitado = visitados_bfs.find(vizinho_bfs) == visitados_bfs.end();
                            if(esta_na_solucao_temp && nao_foi_visitado){ visitados_bfs.insert(vizinho_bfs); fila_bfs.push(vizinho_bfs); }
                        }
                    }
                    if(visitados_bfs.size() == solucao_temporaria.size()) eh_conectado = true;
                }
                if (eh_conectado) { solucao_atual = solucao_temporaria; houve_melhora = true; break; }
            }
        }
        
        //==================================================================================
        // FASE 2.3: ATUALIZAÇÃO DA MELHOR SOLUÇÃO E DO MECANISMO REATIVO
        //==================================================================================
        if (solucao_atual.size() < (size_t)tamanho_melhor_solucao) {
            melhor_solucao_global = solucao_atual;
            tamanho_melhor_solucao = solucao_atual.size();
            std::cout << "Iteracao " << i + 1 << ": Nova melhor solucao (tamanho " << tamanho_melhor_solucao << ") encontrada com alfa=" << alfa << std::endl;
        }

        //--- ATUALIZAÇÃO DAS ESTATÍSTICAS DO ALFA USADO ---
        somas_solucoes[indice_alfa_escolhido] += solucao_atual.size();
        usos_alfa[indice_alfa_escolhido]++;

        //--- ATUALIZAÇÃO PERIÓDICA DAS PROBABILIDADES (O "CORAÇÃO" REATIVO) ---
        if ((i + 1) % intervalo_atualizacao == 0 && i > 0) {
            std::vector<double> qualidades(conjunto_alfas.size());
            double soma_qualidades = 0;

            // CALCULA A QUALIDADE DE CADA ALFA (INVERSO DA MÉDIA DAS SOLUÇÕES).
            for(size_t j=0; j < conjunto_alfas.size(); ++j){
                if(usos_alfa[j] > 0){
                    double media = somas_solucoes[j] / usos_alfa[j];
                    qualidades[j] = 1.0 / media; // QUANTO MENOR A MÉDIA, MAIOR A QUALIDADE.
                } else {
                    qualidades[j] = 0; // SE UM ALFA NUNCA FOI USADO, QUALIDADE 0.
                }
                soma_qualidades += qualidades[j];
            }
            
            // NORMALIZA AS QUALIDADES PARA QUE SOMEM 1, GERANDO AS NOVAS PROBABILIDADES.
            if(soma_qualidades > 0){
                for(size_t j=0; j < conjunto_alfas.size(); ++j){
                    probabilidades_alfa[j] = qualidades[j] / soma_qualidades;
                }
            }
        }
    }
    return melhor_solucao_global;
}