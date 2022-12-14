//Avaliação Bases de Programação
//Professor Denis Cople
//Alunos:
//Artur B.W. Zainotti
//Jéssica Ribeiro Filho
//
//Programa para ler,gravar, inserir, excluir, editar e calcular notas de alunos.
//Consiste em pedir ao usuario inserir nome de aluno, sua matricula e suas notas.
//Cada aluno também terá um codigo unico.
//O calculo da média é baseado nas 2 notas obrigatorias que precisam ser inseridas pelo usuario.
//Todas os dados inseridos serao armazenados em um arquivo .csv, para facil formatação
//em Excel, podendo criar planilhas, tabelas e gráficos.

#include <iostream>
#include <fstream>
#include <locale.h>
#include <cstdio>
#include <stdlib.h>

using namespace std;

//Colocar o caminho para onder o arquivo .csv será criado.
const char* dir_arq = "C:\\Users\\";
char nome_arq[255];

// Repositório interno
const int REGS = 100; // Número de registros

int codigo[REGS];
char nome[REGS][50];
int matricula[REGS];
double nota1[REGS];
double nota2[REGS];
double media[REGS];

int posicao = -1; // Posição no vetor (-1 será vazio)

// Tratamento de arquivos (leitura e gravação)
void tratar_linha(char buffer[]) {
    posicao++;
    char* token;
    char* next_token = NULL;
    token = strtok_s(buffer, ";", &next_token);
    codigo[posicao] = atoi(token); // Converte texto para int
    token = strtok_s(NULL, ";", &next_token);
    strcpy_s(nome[posicao], token);
    token = strtok_s(NULL, ";", &next_token);
    matricula[posicao] = atoi(token);
    token = strtok_s(NULL, ";", &next_token);
    nota1[posicao] = atof(token);
    token = strtok_s(NULL, ";", &next_token);
    nota2[posicao] = atof(token);
    token = strtok_s(NULL, ";", &next_token);
    media[posicao] = atof(token);
}

void ler_arq() {
    posicao = -1;
    cout << "Nome do arquivo: ";
    cin >> nome_arq;
    char arq_entrada[255];
    strcpy_s(arq_entrada, dir_arq);
    strcat_s(arq_entrada, nome_arq);
    strcat_s(arq_entrada, ".csv");
    ifstream fin(arq_entrada);
    char linha[255];
    while (!fin.eof()) {
        if (fin >> linha) {
            tratar_linha(linha);
        }
    }
    fin.close();
}

void salvar_arq() {
    cout << "Nome do arquivo: ";
    cin >> nome_arq;
    char arq_saida[255];
    strcpy_s(arq_saida, dir_arq);
    strcat_s(arq_saida, nome_arq);
    strcat_s(arq_saida, ".csv");
    ofstream fout(arq_saida);
    for (int i = 0; i <= posicao; i++) {
        fout << codigo[i] << ";" << nome[i]
            << ";" << matricula[i] << ";" << nota1[i] << ";" << nota2[i] << ";" << media[i] << endl;
    }
    fout.flush();
    fout.close();
}

// Gerenciamento de registros
bool inserir() {
    if (posicao == (REGS - 1))
        return false;
    posicao++;
    cout << "codigo: ";
    cin >> codigo[posicao];
    cout << "Nome: ";
    cin >> nome[posicao];
    cout << "Matricula: ";
    cin >> matricula[posicao];
    cout << "Nota 1: ";
    cin >> nota1[posicao];
    cout << "Nota 2: ";
    cin >> nota2[posicao];

    media[posicao] = (nota1[posicao] + nota2[posicao]) / 2;

    return true;
}

void imprimir() {
    printf("%-10s%-20s%-10s%-10s%-10s%-10s\n", "Codigo", "Nome", "Matricula", "Nota 1", "Nota 2", "Media");
    for (int i = 0; i <= posicao; i++)
        printf("%-10d%-20s%-10d%-10.2f%-10.2f%-10.2f\n",
            codigo[i], nome[i], matricula[i], nota1[i], nota2[i], media[i]);
}

int localizar(int cod_aux) {
    int pos_aux = -1;
    for (int i = 0; i <= posicao; i++) {
        if (codigo[i] == cod_aux) {
            pos_aux = i;
            break;
        }
    }
    return pos_aux;
}

void pesquisar() {
    cout << "Codigo do aluno: ";
    int cod_aux;
    cin >> cod_aux;
    int pos_vetor = localizar(cod_aux);
    if (pos_vetor == -1) {
        cout << "Nao encontrado!!!!" << endl;
    }
    else {
        printf("%-10s%-20s%-10s%-10s%-10s%-10s\n", "Codigo", "Nome", "Matricula", "Nota 1", "Nota 2", "Media");
        printf("%-10d%-20s%-10d%-10.2f%-10.2f%-10.2f\n",
            codigo[pos_vetor], nome[pos_vetor], matricula[pos_vetor], nota1[pos_vetor], nota2[pos_vetor], media[pos_vetor]);
    }
}

void alterar() {
    cout << "Codigo do aluno a ser ALTERADO: ";
    int cod_aux;
    cin >> cod_aux;
    int pos_vetor = localizar(cod_aux);
    if (pos_vetor == -1) {
        cout << "Nao encontrado!" << endl;
    }
    else {
        cout << "Novo nome: ";
        cin >> nome[cod_aux - 1];
        cout << "Nova matricula: ";
        cin >> matricula[cod_aux - 1];
        cout << "Nova nota 1: ";
        cin >> nota1[cod_aux - 1];
        cout << "Nova nota 2: ";
        cin >> nota2[cod_aux - 1];

        media[cod_aux - 1] = (nota1[cod_aux - 1] + nota2[cod_aux - 1]) / 2;
    }

}

void remover() {
    cout << "codigo do aluno a ser REMOVIDO: ";
    int cod_aux;
    cin >> cod_aux;
    int pos_vetor = localizar(cod_aux);
    if (pos_vetor == -1) {
        cout << "Nao encontrado!!!!" << endl;
    }
    else {
        for (int i = pos_vetor; i < posicao; i++) {
            codigo[i] = codigo[i + 1];
            strcpy_s(nome[i], nome[i + 1]);
            matricula[i] = matricula[i + 1];
            nota1[i] = nota1[i + 1];
            nota2[i] = nota2[i + 1];
            media[i] = media[i + 1];
        }
        posicao--;
    }
}

// Funções de ordenação
void trocar(int pos1, int pos2) {
    int cod_aux = codigo[pos1];
    char nome_aux[50];
    strcpy_s(nome_aux, nome[pos1]);
    int mat_aux = matricula[pos1];
    double nota1_aux = nota1[pos1];
    double nota2_aux = nota2[pos1];
    double media_aux = media[pos1];

    codigo[pos1] = codigo[pos2];
    strcpy_s(nome[pos1], nome[pos2]);
    matricula[pos1] = matricula[pos2];
    nota1[pos1] = nota1[pos2];
    nota2[pos1] = nota2[pos2];
    media[pos1] = media[pos2];

    codigo[pos2] = cod_aux;
    strcpy_s(nome[pos2], nome_aux);
    matricula[pos2] = mat_aux;
    nota1[pos2] = nota1_aux;
    nota2[pos2] = nota2_aux;
    media[pos2] = media_aux;
}

//Ordenar por nome.
void ordenar_bubble_str() {
    bool ordenado;
    do {
        ordenado = true;
        for (int i = 0; i < posicao; i++) {
            if (strcmp(nome[i], nome[i + 1]) > 0) {
                trocar(i, i + 1);
                ordenado = false;
            }
        }
    } while (!ordenado);
    imprimir();
}

//Ordenar por codigo.
void ordenar_bubble() {
    bool ordenado;
    do {
        ordenado = true;
        for (int i = 0; i < posicao; i++) {
            if (codigo[i] > codigo[i + 1]) {
                trocar(i, i + 1);
                ordenado = false;
            }
        }
    } while (!ordenado);
    imprimir();
}

//Ordenar por Nota 1.
void ordenar_bubble_nota1() {
    bool ordenado;
    do {
        ordenado = true;
        for (int i = 0; i < posicao; i++) {
            if (nota1[i] < nota1[i + 1]) {
                trocar(i, i + 1);
                ordenado = false;
            }
        }
    } while (!ordenado);
    imprimir();
}

//Ordenar por Nota 2.
void ordenar_bubble_nota2() {
    bool ordenado;
    do {
        ordenado = true;
        for (int i = 0; i < posicao; i++) {
            if (nota2[i] < nota2[i + 1]) {
                trocar(i, i + 1);
                ordenado = false;
            }
        }
    } while (!ordenado);
    imprimir();
}

//Ordenar por Media.
void ordenar_bubble_media() {
    bool ordenado;
    do {
        ordenado = true;
        for (int i = 0; i < posicao; i++) {
            if (media[i] < media[i + 1]) {
                trocar(i, i + 1);
                ordenado = false;
            }
        }
    } while (!ordenado);
    imprimir();
}

//Remover todos os registros e deixar o arquivo em branco.
void remover_tudo() {
    cout << "Tem certeza que deseja remover todos os registros ? - 0 NAO - 1 SIM  " << endl;
    bool confirma;
    cin >> confirma;
    if (confirma == 1) {

        for (int i = 0; i < REGS; i++) {
            codigo[i] = codigo[i + 1];
            strcpy_s(nome[i], nome[i + 1]);
            matricula[i] = matricula[i + 1];
            nota1[i] = nota1[i + 1];
            nota2[i] = nota2[i + 1];
            media[i] = media[i + 1];
            posicao--;
        }
        cout << "Remocao completa concluida" << endl;
    }
}

// Menu e Programa Principal
int menu() {
    cout << "1 - Ler Arquivo" << endl;
    cout << "2 - Grava Arquivo" << endl;
    cout << "3 - Inserir" << endl;
    cout << "4 - Imprimir" << endl;
    cout << "5 - Ordenar por codigo" << endl;
    cout << "6 - Ordenar por letra" << endl;
    cout << "7 - Ordenar por nota 1" << endl;
    cout << "8 - Ordenar por nota 2" << endl;
    cout << "9 - Ordenar por media" << endl;
    cout << "10 - Pesquisar" << endl;
    cout << "11 - Alterar" << endl;
    cout << "12 - Remover" << endl;
    cout << "13 - Excluir todos os registros" << endl;
    cout << "0 - Sair" << endl;
    cout << "Sua opcao: ";
    int opcao;
    cin >> opcao;
    return opcao;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    while ((opcao = menu()) != 0) {
        switch (opcao) {
        case 1:
            ler_arq(); break;
        case 2:
            salvar_arq(); break;
        case 3:
            inserir(); break;
        case 4:
            imprimir(); break;
        case 5:
            ordenar_bubble(); break;
        case 6:
            ordenar_bubble_str(); break;
        case 7:
            ordenar_bubble_nota1(); break;
        case 8:
            ordenar_bubble_nota2(); break;
        case 9:
            ordenar_bubble_media(); break;
        case 10:
            pesquisar(); break;
        case 11:
            alterar(); break;
        case 12:
            remover(); break;
        case 13:
            remover_tudo(); break;
        }
    }
}

