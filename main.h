#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

// NODE
typedef struct NODE{
    unsigned int matricula;
    unsigned int matriculaPai;
    float desconto;
    float mensalidade;
    float valorAberto;
    char nome[50];
    struct NODE* primeiroFilho;
    struct NODE* proxIrmao;
}NODE;

// PROTÓTIPOS
NODE* criaNovoNo(int matricula);

NODE* inicializaArvore();

NODE* buscaMatricula(int matricula, NODE* raiz);

NODE* localizaPai(NODE* raiz, NODE* pai, unsigned int matriculaFilho, int nivel);

int inserirAluno(NODE* raiz, char novoNome[50], int matricula, int chavePai);

int matricularAluno(NODE* raiz);

int verificaMatricula(unsigned int matricula, NODE* raiz);

int localizarIndicador(NODE* raiz);

int venderProduto(NODE* raiz);

int atualizarDesconto(NODE* raiz, unsigned int matricula, float preco);

void imprimirArvore(NODE* raiz, int quantTab);

void menu(NODE* raiz);

void menuPagamento(NODE* raiz);

void desenharMenu();

void desenharMenuPagamentos();

void imprimirSubArvore(NODE* raiz);

void imprimirTodosAlunos(NODE* raiz);

void mensalidadeAluno(NODE* raiz);

void valorVendas(NODE* raiz);

void salvaItens(NODE* raiz, NODE* subArv, FILE *f);

void salvaArquivo(NODE* raiz);

void carregarDoArquivo(NODE* raiz);

void limpar_tela();

void limpar_stdin();

#endif