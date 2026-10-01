#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

#define MAX_ALUNOS 100
#define MAX_DISCIPLINAS 8
#define ARQUIVO "data/alunos.dat"

typedef struct {
    int codigo;
    char nome[80];
    char curso[80];
    char email[100];
    float notas[MAX_DISCIPLINAS];
    int quantidade_notas;
} Aluno;

Aluno alunos[MAX_ALUNOS];
int total_alunos = 0;

void limpar_buffer(void);
void salvar(void);
void carregar(void);
void cadastrar_aluno(void);
void listar_alunos(void);
void buscar_aluno(void);
void registrar_nota(void);
void remover_aluno(void);
void mostrar_situacao(Aluno *a);
float calcular_media(Aluno *a);

int main(void) {
    int opcao;
#ifdef _WIN32
    _mkdir("data");
#else
    mkdir("data", 0777);
#endif

    carregar();

    do {
        printf("\n=== SISTEMA DE CONTROLE ACADEMICO ===\n");
        printf("1 - Cadastrar aluno\n");
        printf("2 - Listar alunos\n");
        printf("3 - Buscar aluno\n");
        printf("4 - Registrar nota\n");
        printf("5 - Remover aluno\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1) {
            limpar_buffer();
            opcao = -1;
        }
        limpar_buffer();

        switch (opcao) {
            case 1: cadastrar_aluno(); break;
            case 2: listar_alunos(); break;
            case 3: buscar_aluno(); break;
            case 4: registrar_nota(); break;
            case 5: remover_aluno(); break;
            case 0: salvar(); printf("Dados salvos.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void salvar(void) {
    FILE *arquivo = fopen(ARQUIVO, "wb");
    if (!arquivo) {
        perror("Erro ao salvar");
        return;
    }
    fwrite(&total_alunos, sizeof(int), 1, arquivo);
    fwrite(alunos, sizeof(Aluno), total_alunos, arquivo);
    fclose(arquivo);
}

void carregar(void) {
    FILE *arquivo = fopen(ARQUIVO, "rb");
    if (!arquivo) return;

    fread(&total_alunos, sizeof(int), 1, arquivo);
    if (total_alunos < 0 || total_alunos > MAX_ALUNOS) {
        total_alunos = 0;
        fclose(arquivo);
        return;
    }

    fread(alunos, sizeof(Aluno), total_alunos, arquivo);
    fclose(arquivo);
}

void cadastrar_aluno(void) {
    if (total_alunos >= MAX_ALUNOS) {
        printf("Limite de alunos atingido.\n");
        return;
    }

    Aluno *a = &alunos[total_alunos];

    printf("Matricula: ");
    scanf("%d", &a->codigo);
    limpar_buffer();

    printf("Nome: ");
    fgets(a->nome, sizeof(a->nome), stdin);
    a->nome[strcspn(a->nome, "\n")] = '\0';

    printf("Curso: ");
    fgets(a->curso, sizeof(a->curso), stdin);
    a->curso[strcspn(a->curso, "\n")] = '\0';

    printf("Email: ");
    fgets(a->email, sizeof(a->email), stdin);
    a->email[strcspn(a->email, "\n")] = '\0';

    a->quantidade_notas = 0;
    total_alunos++;
    salvar();

    printf("Aluno cadastrado com sucesso.\n");
}

void listar_alunos(void) {
    if (total_alunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    printf("\n--- ALUNOS ---\n");
    for (int i = 0; i < total_alunos; i++) {
        printf("\nMatricula: %d\n", alunos[i].codigo);
        printf("Nome: %s\n", alunos[i].nome);
        printf("Curso: %s\n", alunos[i].curso);

        if (alunos[i].quantidade_notas > 0) {
            printf("Media: %.2f | ", calcular_media(&alunos[i]));
            mostrar_situacao(&alunos[i]);
        } else {
            printf("Sem notas registradas.\n");
        }
    }
}

void buscar_aluno(void) {
    int codigo;
    printf("Digite a matricula: ");
    scanf("%d", &codigo);
    limpar_buffer();

    for (int i = 0; i < total_alunos; i++) {
        if (alunos[i].codigo == codigo) {
            printf("\nAluno encontrado!\n");
            printf("Nome: %s\nCurso: %s\nEmail: %s\n", alunos[i].nome, alunos[i].curso, alunos[i].email);
            printf("Notas: ");
            for (int j = 0; j < alunos[i].quantidade_notas; j++)
                printf("%.1f ", alunos[i].notas[j]);
            printf("\n");
            return;
        }
    }

    printf("Aluno nao encontrado.\n");
}

void registrar_nota(void) {
    int codigo;
    float nota;

    printf("Matricula: ");
    scanf("%d", &codigo);

    for (int i = 0; i < total_alunos; i++) {
        if (alunos[i].codigo == codigo) {
            if (alunos[i].quantidade_notas >= MAX_DISCIPLINAS) {
                printf("Limite de notas atingido.\n");
                limpar_buffer();
                return;
            }

            printf("Nota (0 a 10): ");
            scanf("%f", &nota);
            limpar_buffer();

            if (nota < 0 || nota > 10) {
                printf("Nota invalida.\n");
                return;
            }

            alunos[i].notas[alunos[i].quantidade_notas++] = nota;
            salvar();
            printf("Nota registrada. Media atual: %.2f\n", calcular_media(&alunos[i]));
            return;
        }
    }

    limpar_buffer();
    printf("Aluno nao encontrado.\n");
}

void remover_aluno(void) {
    int codigo;
    printf("Matricula do aluno a remover: ");
    scanf("%d", &codigo);
    limpar_buffer();

    for (int i = 0; i < total_alunos; i++) {
        if (alunos[i].codigo == codigo) {
            for (int j = i; j < total_alunos - 1; j++)
                alunos[j] = alunos[j + 1];

            total_alunos--;
            salvar();
            printf("Aluno removido.\n");
            return;
        }
    }

    printf("Aluno nao encontrado.\n");
}

float calcular_media(Aluno *a) {
    if (a->quantidade_notas == 0) return 0;

    float soma = 0;
    for (int i = 0; i < a->quantidade_notas; i++)
        soma += a->notas[i];

    return soma / a->quantidade_notas;
}

void mostrar_situacao(Aluno *a) {
    float media = calcular_media(a);

    if (media >= 7)
        printf("Aprovado\n");
    else if (media >= 5)
        printf("Recuperacao\n");
    else
        printf("Reprovado\n");
}
