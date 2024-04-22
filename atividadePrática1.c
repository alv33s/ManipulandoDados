#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 94
#define MAX_NOME 20
#define MAX_NOTAS 10

typedef struct {
    char nome[MAX_NOME];
    char telefone[15]; 
    char curso[MAX_NOME];
    float notas[MAX_NOTAS];
    int num_notas;
    float media;
    char situacao[10];
} Aluno;

int lerAlunos(Aluno alunos[]);

int main() {
    Aluno alunos[MAX_ALUNOS];
    int num_alunos;

    num_alunos = lerAlunos(alunos);
    FILE *arquivo;
    arquivo = fopen("SituacaoFinal.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de saída.\n");
        exit(1);
    }

    for (int i = 0; i < num_alunos; i++) {
        fprintf(arquivo, "%s\n", alunos[i].nome);
    }

    fclose(arquivo);
   


    return 0;
}

int lerAlunos(Aluno alunos[]) {
    FILE *arquivo;
    char linha[1024];
    int num_alunos = 0;
    int primeira_linha = 1;

    arquivo = fopen("DadosEntrada.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {

        if (primeira_linha) {
            primeira_linha = 0;
            continue;
        }

        char *token;
        token = strtok(linha, ",");
        strcpy(alunos[num_alunos].nome, token);

        token = strtok(NULL, ",");
        strcpy(alunos[num_alunos].telefone, token);

        token = strtok(NULL, ",");
        strcpy(alunos[num_alunos].curso, token);

        alunos[num_alunos].num_notas = 0;
        while ((token = strtok(NULL, ",")) != NULL && alunos[num_alunos].num_notas < MAX_NOTAS) {
            alunos[num_alunos].notas[alunos[num_alunos].num_notas++] = atof(token);
        }

        num_alunos++;
    }

    fclose(arquivo);

    return num_alunos;
}
