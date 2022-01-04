#ifndef ARVORE_H
#define ARVORE_H

#define MENSALIDADEPADRAO 100

NODE* inicializaArvore(){
    // cria um nó com matricula 0 para ser a raiz da árvore
    return(criaNovoNo(0));
}

// recebe uma matrícula e cria um novo nó
NODE* criaNovoNo(int matricula){
    NODE* novo = (NODE*)malloc(sizeof(NODE));
    novo->primeiroFilho = NULL;
    novo->proxIrmao = NULL;
    novo->matricula = matricula;
    novo->desconto = 0;
    return novo;
}

NODE* localizaPai(NODE* raiz, NODE* pai, unsigned int matriculaFilho, int nivel){
    NODE* locesq;
    NODE* locdir;
    locesq = NULL;
    locdir = NULL;
    if (raiz->matricula != matriculaFilho) {
        if (raiz->primeiroFilho != NULL){
            locesq = localizaPai(raiz->primeiroFilho, raiz, matriculaFilho, nivel + 1);
        }
        if (locesq == NULL) {
            if(raiz->proxIrmao != NULL){
                locdir = localizaPai(raiz->proxIrmao, pai, matriculaFilho, nivel);
            }
            if (locdir == NULL){
                return NULL;
            }
            else{
                return locdir;
            }
        }
        else{
            return locesq;
        }
    } 
    else{
        return pai;
    }
}

int inserirAluno(NODE* raiz, char novoNome[50], int matricula, int matriculaPai){
    // verifica se o pai existe
    NODE* pai = buscaMatricula(matriculaPai, raiz);
    if(pai == NULL){
        return -1;
    }

    // aloca memória para um novo node
    NODE* novoAluno = criaNovoNo(matricula);
    
    // atribui nome ao nó
    strcpy(novoAluno->nome, novoNome);
    novoAluno->mensalidade = MENSALIDADEPADRAO;
    novoAluno->desconto = 0;
    novoAluno->matriculaPai = matriculaPai;
    novoAluno->matricula = matricula;

    // verifica se o pai possui filhos
    NODE* p = pai->primeiroFilho;
    if(p == NULL){// se não possui, esse é o primeiro filho
        pai->primeiroFilho = novoAluno;
    }else{// caso possua, coloca como proxIrmao do ultimo irmao
        while(p->proxIrmao != NULL){
            p = p->proxIrmao;
        }
        p->proxIrmao = novoAluno;
    }

    return 1;
}

void imprimirArvore(NODE* raiz, int quantTab){
    if(raiz == NULL){
        return;
    }
    
    //só imprime se a matrícula não for igual a 0
    raiz->nome[strcspn(raiz->nome, "\n")] = 0;
    if(raiz->matricula != 0){
        printf("%s - %u - bônus: R$ %.2f\n", raiz->nome, raiz->matricula, raiz->desconto);
    }

    // verifica se o node tem filhos
    NODE* p = raiz->primeiroFilho;
    while(p){
        //imprime os tabs
		for(int i = 0; i < quantTab; i++){
			printf("\t");
        }
        printf("└-->");
        // faz isso para todos os irmãos e descendentes do node
        imprimirArvore(p, quantTab+1);
        p = p->proxIrmao;
    } 
}

// imprime das indicações de um aluno
void imprimirSubArvore(NODE* raiz){
    limpar_tela();
    int matriculaBusca;

    printf("----- INDICAÇÕES DE ALUNO -----\n");
    printf("Informe a matrícula do aluno: ");
    scanf("%d", &matriculaBusca);// recebe a matricula do aluno

    printf("\n");
    NODE* aluno = buscaMatricula(matriculaBusca, raiz);// busca pelo aluno
    imprimirArvore(aluno, 0);// imprime a árvore adotando ele como raiz
    getchar();
    getchar();
}

void liberaArvore(NODE* raiz){
    if(raiz == NULL){
        return;
    }
    liberaArvore(raiz->primeiroFilho);
    liberaArvore(raiz->proxIrmao);
    free(raiz);
}

#endif