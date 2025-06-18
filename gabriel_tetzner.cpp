#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

#include "gabriel_tetzner.h"

int main()
{
    Solucao s;
    ler_dados("i13206.txt");
   // testar_dados("");

    //---

	// UTILIZE ESSA AREA PARA TESTE
    heu_con_gu(s);
    calcular_fo(s);
    escrever_solucao(s, "");

    //---
    delete[] vet_qtd_conf;
    for(int i = 0; i < num_ids; i++)
        delete[] mat_conflitos[i];
    delete[] mat_conflitos;
    return 0;
}

//----------------------------------------------------------------------------------------------------------

// INSIRA SEU CODIGO AQUI

void gerar_vizinho(Solucao& s){

    int ponto, posicao;

    ponto = rand() % num_pts;

    do{
       posicao = rand() % num_pos;
    } while(posicao == s.vet_sol[ponto]);

    s.vet_sol[ponto] = posicao;
    calcular_fo(s);
}

void heu_con_ale(Solucao& s){
    for(int i = 0; i < num_pts; i++) s.vet_sol[i] = rand() % num_pos;
}
/*
void procura_menor_qtd_conflito(int& id, int& pos_menor){
    int menor = vet_qtd_conf[mat_conflitos[id][0]];
    int pos = get_posicao(mat_conflitos[id][0]);
    for(int k = 0; k < vet_qtd_conf[id]; k++){
         if(menor > vet_qtd_conf[mat_conflitos[id][k]]){
            menor = vet_qtd_conf[mat_conflitos[id][k]];
            pos = get_posicao(mat_conflitos[id][k]);
         }
    }

    pos_menor = pos;
}*/

void heu_con_gu(Solucao& s){

    int id, pos = 0, qtd_menor, conflito;
    s.vet_sol[0] = 0;
    for (int i = 1; i < num_pts; i++)
    {
       // procura_menor_qtd_conflito(id, pos_menor);
        id = get_id(i-1, s.vet_sol[i-1]);
        pos = get_posicao(mat_conflitos[id][0]);
        qtd_menor = vet_qtd_conf[mat_conflitos[id][0]];
        for(int j = 0; j < vet_qtd_conf[id]; j++){
             if(qtd_menor > vet_qtd_conf[mat_conflitos[id][j]]){
                qtd_menor = vet_qtd_conf[mat_conflitos[id][j]];
                pos = get_posicao(mat_conflitos[id][j]);
             }
        }
        s.vet_sol[i] = pos;
    }
}

//----------------------------------------------------------------------------------------------------------

void calcular_fo(Solucao& s)
{
    int id, pt, pos, conflito;
    s.fo = num_pts;                                  // considera que todos os pontos estao livres (sem conflito)
    for (int i = 0; i < num_pts; i++)                // para cada ponto
    {
        id = get_id(i, s.vet_sol[i]);                // pega o id da posicao candidata selecionada para o ponto na solucao
        conflito = 0;                                // considera que o ponto esta livre (nao esta em conflito)
        for (int j = 0; j < vet_qtd_conf[id]; j++)   // para cada possivel conflito do id (posicao selecionada do ponto)
        {
            pt = get_ponto(mat_conflitos[id][j]);    // pega o ponto do possivel conflito
            pos = get_posicao(mat_conflitos[id][j]); // pega a posicao candidata do possivel conflito
            if (s.vet_sol[pt] == pos)                // verifica se na solucao para o ponto foi selecionada a posicao candidata confitante
            {
                conflito = 1;                        // o ponto nao esta livre, ha pelo menos um conflito
                break;
            }
        }
        s.fo -= conflito;                            // atualiza a fo
    }
}

// recebe um ponto (0 a num_pts - 1) e uma posicao candidata (0 a num_pos - 1) e retorna o id (0 a num_ids - 1)
int get_id(const int& pt, const int& pos)
{
    return (pt * num_pos) + pos;
}

// recebe um id (0 a num_ids - 1) e retorna o ponto (0 a num_pts - 1)
int get_ponto(const int& id)
{
    return id / num_pos;
}

// recebe um id (0 a num_ids - 1) e retorna a posicao candidata (0 a num_pos - 1)
int get_posicao(const int& id)
{
    return id % num_pos;
}

void escrever_solucao(const Solucao& s, char* arq)
{
    FILE* f;
    if (arq == "")
        f = stdout;
    else
        f = fopen(arq, "w");
    fprintf(f, "\n\nFO: %d\n", s.fo);
    for (int i = 0; i < num_pts; i++)
        fprintf(f, "Ponto: %d\tPos: %d\n", i + 1, s.vet_sol[i] + 1); // os ids no arquivo de entrada comecam em 1 (ao inves de 0)
    if (arq != "")
        fclose(f);
}

void testar_dados(char* arq)
{
    FILE* f;
    if (arq == "")
        f = stdout;
    else
        f = fopen(arq, "w");
    fprintf(f, "%d\n%d", num_pts, num_pos);
    for(int i = 0; i < num_ids; i++)
    {
        fprintf(f, "\n%d\n", vet_qtd_conf[i]);
        for(int j = 0; j < vet_qtd_conf[i]; j++)
            fprintf(f, "%d ", mat_conflitos[i][j] + 1); // os ids no arquivo de entrada comecam em 1 (ao inves de 0)
    }
    if (arq != "")
        fclose(f);
}

void ler_dados(char* arq)
{
    FILE* f = fopen(arq, "r");
    fscanf(f, "%d %d", &num_pts, &num_pos);
    num_ids = num_pts * num_pos;
    vet_qtd_conf = new int[num_ids];
    mat_conflitos = new int*[num_ids];
    for(int i = 0; i < num_ids; i++)
    {
        fscanf(f, "%d", &vet_qtd_conf[i]);
        mat_conflitos[i] = new int[vet_qtd_conf[i]];
        for(int j = 0; j < vet_qtd_conf[i]; j++)
        {
            fscanf(f, "%d", &mat_conflitos[i][j]);
            mat_conflitos[i][j]--; // os ids no arquivo de entrada comecam em 1 (ao inves de 0)
        }
    }
    fclose(f);
}
