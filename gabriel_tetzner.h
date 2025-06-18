#ifndef GABRIEL_TETZNER_H_INCLUDED
#define GABRIEL_TETZNER_H_INCLUDED

#define MAX_PTS 14000 // maximo de pontos a serem rotulados

typedef struct tSolucao
{
    int vet_sol[MAX_PTS];
    int fo;
}Solucao;

int num_pts;         // numero de pontos
int num_pos;         // numero de posicoes candidatas por ponto
int num_ids;         // numero total (num_pts * num_pos) de identificadores (posicoes possiveis)
int* vet_qtd_conf;   // vetor com a quantidade de conflitos de cada identificador
int** mat_conflitos; // matriz com o "id" dos conflitos de cada identificador
//----------------------------------------------------------------------------------------------------------

// INSIRA SEU CODIGO AQUI
void gerar_vizinho(Solucao& s);
void heu_con_ale(Solucao& s);
void heu_con_gu(Solucao& s);

//----------------------------------------------------------------------------------------------------------
void calcular_fo(Solucao& s);
int get_ponto(const int& id);
int get_posicao(const int& id);
int get_id(const int& pt, const int& pos);
void escrever_solucao(const Solucao& s, char* arq);
void testar_dados(char* arq);
void ler_dados(char* arq);

#endif // GABRIEL_TETZNER_H_INCLUDED
