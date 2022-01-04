#include "main.h"
#include "arvore.h"

int main(int argv, const char *argc[]){
    setlocale(LC_ALL, "");

    // cria o node raiz
    NODE* raiz = inicializaArvore();

    // carrega os alunos do arquivo
    carregarDoArquivo(raiz);

    // loop principal
    menu(raiz);

    // libera a árvore
    liberaArvore(raiz);

    limpar_tela();
	return 0;
}

void menu(NODE* raiz){
    int escolha;
    //desenha o menu principal
    do{
        desenharMenu();
        //printf("MENSALIDADE: %f", carregarMensalidadePadrao());
        scanf("%d", &escolha);

        // funções do menu principal
        switch(escolha){
            case 0:
                salvaArquivo(raiz);
                return;
                break;
            case 1:
                matricularAluno(raiz);
                break;
            case 2:
                menuPagamento(raiz);
                break;
            case 3:
                imprimirTodosAlunos(raiz);
                break;
            case 4:
                imprimirSubArvore(raiz);
                break;
            case 5:
                localizarIndicador(raiz);
                break;
            default:
                limpar_tela();
                printf("[!] Opção inválida.");
                limpar_stdin();
                getchar();
                break;
        }
    }while(escolha != 0);
}

void menuPagamento(NODE* raiz){
    int escolha;
    //desenha o menu principal
    do{
        desenharMenuPagamentos();
        scanf("%d", &escolha);

        // funções do menu principal
        switch(escolha){
            case 0:
                return;
                break;
            case 1:
                mensalidadeAluno(raiz);
                break;
            case 2:
                venderProduto(raiz);
                break;
            case 3:
                valorVendas(raiz);
                break;
            default:
                limpar_tela();
                printf("[!] Opção inválida.");
                limpar_stdin();
                getchar();
                break;
        }
    }while(escolha != 0);
}

// imprimem os menus
void desenharMenu(){
    limpar_tela();
    printf("----- MENU PRINCIPAL -----\n");
    printf("1 - Matricular aluno\n");
    printf("2 - Pagamentos\n");
    printf("3 - Imprimir todos os alunos\n");
    printf("4 - Imprimir sub árvore de um aluno\n");
    printf("5 - Localizar Indicador do aluno\n");
    printf("0 - Sair\n");
    printf("\nEscolha: ");
}

void desenharMenuPagamentos(){
    limpar_tela();
    printf("----- PAGAMENTOS -----\n");
    printf("1 - Mensalidade do aluno\n");
    printf("2 - Vender produto\n");
    printf("3 - Valor das vendas\n");
    printf("0 - Voltar\n");
    printf("\nEscolha: ");
}

int matricularAluno(NODE* raiz){
    limpar_tela();
    limpar_stdin();

    unsigned int novaMatricula; // matricula que será cadastrada
    char novoNome[50];          // nome do aluno que será matriculado
    int resposta = 0, matriculaIndicador; // matricula de quem indicou o aluno

    printf("----- ADICIONAR ALUNO -----\n");
    printf("Informe o nome do aluno: ");
    fgets(novoNome, 50, stdin); // recebe o nome do novo aluno
    printf("\nInforme a matrícula: ");
    scanf("%d", &novaMatricula);// recebe a matricula do novo aluno

    // verificando se a matricula a matricula atribuída ao novo aluno já existe no sistema
    int res = verificaMatricula(novaMatricula, raiz);
    if(res == 1){
        printf("\n[!] Já existe essa matrícula no sistema, insira outra.\n");
        limpar_stdin();
        getchar();
        matricularAluno(raiz);
        return 0;
    }

    // verificando se o aluno foi indicado por alguem já matriculado
    do{
        printf("\nO aluno foi incado por alguém? \n1 - Sim\n2 - Não\n3 - Cancelar\nResposta: ");
        scanf("%d", &resposta);
        switch (resposta){
            // caso o aluno tenha sido indicado:
            case 1:
                printf("\nDigite a matrícula do aluno que indicou: ");
                scanf("%d", &matriculaIndicador);

                // verifica se a matricula do indicador existe e caso exista matricula o
                // aluno como filho dele e apresenta a mensagem de sucesso
                if(inserirAluno(raiz, novoNome, novaMatricula, matriculaIndicador) == -1){
                    limpar_tela();
                    printf("[!] Não existe nenhum aluno com essa matrícula. Insira uma matrícula válida.");
                    getchar();
                    getchar();
                    return -1;
                }

                limpar_tela();
                atualizarDesconto(raiz, novaMatricula, MENSALIDADEPADRAO);
                printf("[*] O aluno foi matriculado com sucesso.");
                getchar();
                getchar();
                return 1;
                break;

            // caso o aluno não tenha sido indicado por ninguém:
            case 2:
                // ele será filho da raiz (matricula 0)
                matriculaIndicador = 0;
                inserirAluno(raiz, novoNome, novaMatricula, 0);
                limpar_tela();
                atualizarDesconto(raiz, novaMatricula, MENSALIDADEPADRAO);
                printf("[*] O aluno foi matriculado com sucesso.");
                getchar();
                getchar();
                return 1;
                break;

            // caso o usuário desista de cadastrar
            case 3:
                return 0;
                break;
            default:
                limpar_tela();
                printf("\n[!] Opção inválida.\n");
                getchar();
                getchar();
                break;
        }
    }while(resposta != 3);
    return 0;
}

int venderProduto(NODE* raiz){
    limpar_tela();
    float preco;
    int matricula;

    printf("----- VENDER PRODUTO -----\n");
    printf("Preço: ");
    scanf("%f", &preco);
    printf("Matricula: ");
    scanf("%d", &matricula);

    NODE* aluno = buscaMatricula(matricula, raiz);
    aluno->valorAberto += preco;

    atualizarDesconto(raiz, matricula, preco);

    return 0;
}

void valorVendas(NODE* raiz){
    limpar_tela();
    int matricula;

    printf("----- VALOR DAS VENDAS -----\n");
    printf("Matricula: ");
    scanf("%d", &matricula);

    NODE* aluno = buscaMatricula(matricula, raiz);

    printf("O valor em aberto do aluno é: R$ %.2f\n\nEnter para continuar...", aluno->valorAberto);
    limpar_stdin();
    getchar();
}

int localizarIndicador(NODE* raiz){
    limpar_tela();
    unsigned int matriculaFilho;

    printf("----- LOCALIZAR INDICADOR -----\n");
    printf("Informe a matrícula do aluno que deseja encontrar o indicador: ");
    scanf("%d", &matriculaFilho);
    NODE* pai;
    pai = localizaPai(raiz, NULL, matriculaFilho, 0);
    if(pai){
        unsigned int res = pai->matricula;
        printf("\nIndicador do aluno: %u", res);
        limpar_stdin();
        getchar();
        return 1;
    }
    else{
        printf("\n[!] Não existe indicador desse esse aluno.");
        limpar_stdin();
        getchar();
        return 0;
    }
}

// verifica se uma matrícula existe no sistema, retorna 1 se existir
int verificaMatricula(unsigned int matricula, NODE* raiz){
    NODE* busca = buscaMatricula(matricula, raiz);
    if(busca != NULL){
        return 1;       
    }
    return 0;
}

// consulta a mensalidade e desconto do aluno
void mensalidadeAluno(NODE* raiz){
    limpar_tela();
    unsigned int matricula;
    printf("----- MENSALIDADE DO ALUNO -----\n");
    printf("Informe a matrícula do aluno: ");
    scanf("%d", &matricula);

    if(verificaMatricula(matricula, raiz) == 1){
        NODE* aluno = buscaMatricula(matricula, raiz);
        printf("\nMensalidade do aluno: R$ %.2f\n", aluno->mensalidade);
        printf("Desconto do aluno:  %.2f\n", aluno->desconto);
        printf("\n\nEnter para continuar ");
        limpar_stdin();
        getchar();
    }else{
        printf("\n[!] Não existe essa matrícula no sistema.");
        printf("\n\nEnter para continuar ");
        limpar_stdin();
        getchar();
    }
}

void imprimirTodosAlunos(NODE* raiz){
    limpar_tela();
    printf("----- TODOS OS ALUNOS -----\n");
    imprimirArvore(raiz, 0);
    printf("\nAperte Enter para continuar.");
    getchar();
    getchar();
}

// verifica se existe uma certa matrícula na árvore, retorna um ponteiro para o aluno
NODE* buscaMatricula(int matricula, NODE* raiz){
    NODE* p = (NODE*)malloc(sizeof(NODE));
    
    if(raiz == NULL){
        return NULL;
    }

    // retorna o node cuja matrícula é igual a que se busca
    if(raiz->matricula == matricula){
        return raiz;
    }
    
    //verifica se o node possui filhos
    p = raiz->primeiroFilho;
    while(p){
        // chama a função para todos os filhos do node 
        NODE* aux = buscaMatricula(matricula, p);
        if(aux != NULL){
            return aux;
        }
        p = p->proxIrmao;
    }
    return NULL;
}

// imprime alunos em arquivo
void salvaItens(NODE* raiz, NODE* subArv, FILE *f){
    NODE* pai = (NODE*)malloc(sizeof(NODE));

    if (subArv != NULL){
        pai = localizaPai(raiz, NULL, subArv->matricula, 0);
        
        if (pai!= NULL){
            fwrite(subArv, sizeof(NODE), 1, f);
        }
        salvaItens(raiz, subArv->primeiroFilho, f);
        salvaItens(raiz, subArv->proxIrmao, f);
    }
}

// salva o arquivo 
void salvaArquivo(NODE* raiz){
    FILE* f;
    f = fopen("alunos.txt", "wb");

    salvaItens(raiz,raiz->primeiroFilho, f);
    salvaItens(raiz,raiz->proxIrmao, f);
    
    fclose(f);
}

// lê do arquivo
void carregarDoArquivo(NODE* raiz){
    FILE* f;
    f = fopen("alunos.txt", "rb");

    if(f == NULL){
        limpar_tela();
        printf("[!] Não foi possível abrir o arquivo 'alunos.txt'.");
        printf("\n[*] Criando arquivo 'alunos.txt'\n");
        if(fopen("alunos.txt", "wb")){
            printf("[*] Arquivo criado.\n\n");
            
        }else{
            printf("\n[!] Não é possível criar o arquivo.");
            getchar();
            exit(-1);
        }
    }

    NODE c;
    f = fopen("alunos.txt", "rb");

    while(!feof(f)){
        if(fread(&c, sizeof(NODE), 1, f) == true){
            char nome[50];
            strcpy(nome, c.nome);
            unsigned int matricula = c.matricula;
            unsigned int matriculaPai = c.matriculaPai;
            float desconto = c.desconto; 
            float valorAberto = c.valorAberto;
            
            inserirAluno(raiz, nome, matricula, matriculaPai);
            
            NODE* aluno = (NODE*)malloc(sizeof(NODE));
            aluno = buscaMatricula(matricula, raiz);
            
            aluno->desconto = desconto;
            aluno->valorAberto = valorAberto;
        }
    }
    fclose(f);
}

// atualiza o desconto atual
int atualizarDesconto(NODE* raiz, unsigned int matricula, float preco){
    int x = 5;
    NODE* pai = (NODE*)malloc(sizeof(NODE));

    for (int i = 1; i <= 3; i++){
        pai = localizaPai(raiz, NULL, matricula, 0);
        if(pai->matricula != 0){
            if(pai != NULL){
                float aux = pai->desconto + preco * ((float) x / 100);
                pai->desconto = aux;
                x = x - 2;
                matricula = pai->matricula;
            }else{ 
                break;
            }
        }
    }
    return 1;
}

void limpar_tela(){
    #if defined(_WIN32) || defined(_WIN64)
	system("cls");
	#endif
	#if defined(__linux__) || defined(__unix__)
	system("clear");
	#endif
}

void limpar_stdin(){
    int c;
    do{
        c = getchar();
    }while (c != '\n' && c != EOF);
}
