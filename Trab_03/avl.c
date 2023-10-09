#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int valor;
    struct no *esquerdo, *direito;
    int altura;
}No;

/*
Função que cria um novo no 
recebe x -> valor a ser inserido no no
retorna o endereço do no criado
altura = 0 -> toda vez que insere um novo no, esse no é zero (folha)
*/

No* novoNo(int x){
    No *novo = malloc(sizeof(No));

    if (novo){
        novo -> valor = x;
        novo -> esquerdo = NULL;
        novo -> direito = NULL;
        novo -> altura = 0;
    }

    else{
        printf("\n ERRO ao alocar no em novoNo \n");
    }

    return novo;
}

/*
Função que retorna a altura de cada no
sendo o maior entre dois valores a e b
*/

int maior (int a, int b){
    return (a > b)? a: b; /*se a > b -> retorna a, se não, b*/
}

/*
Função que retorna a altura do no
*/

int alturaDoNo(No *no){
    if (no == NULL){
        return -1;
    }
    else{
        return no -> altura;/*retorna a altura desse no*/
    }
}

/*
Fator de balanceamento do no
pode ser + ou - que indica para onde a árvore está pendendo:
   fb - : pende para a direita -> nos a mais na subarvore
   fb + : pende para a esquerda
*/
int fatorBalance(No *no){
    if (no){
        return (alturaDoNo(no -> esquerdo) - alturaDoNo(no -> direito));
    }

    else{
        return 0;
    }
}

/*
Rotação a esquerda:
    devolve um ponteiro para o No que será a nova raiz
    o ponteiro para o no desbalanceado sera mandado para a rotação
    Cria:
        dois ponteiros auxiliares: y -> para o no desbalanceado
                                   f (filho) -> aponta para y -> esquerda
*/

No* rotEsq(No *raiz){
    No *y, *f;

    y = raiz -> direito;
    f = y -> esquerdo;

    y -> esquerdo = raiz;
    raiz -> direito = f;

    /*
    recalcular alturas apos a rotação
    */
    raiz -> altura = maior(alturaDoNo(raiz -> esquerdo), alturaDoNo(raiz -> direito)) + 1;
    y -> altura = maior(alturaDoNo(y -> esquerdo), alturaDoNo(y -> direito)) + 1;

    /*
    retorna nova raiz da arvore = y
    */
    return y;
}

/*
Rotação a direita:
    devolve um ponteiro para o No que será a nova raiz
    o ponteiro para o no desbalanceado sera mandado para a rotação
    Cria:
        dois ponteiros auxiliares: y -> para o no desbalanceado
                                   f (filho) -> aponta para y -> esquerda
*/

No* rotDir(No *raiz){
    No *y, *f;

    y = raiz -> esquerdo;
    f = y -> direito;

    y -> direito = raiz;
    raiz -> esquerdo = f;

    /*
    recalcular alturas apos a rotação
    */
    raiz -> altura = maior(alturaDoNo(raiz -> esquerdo), alturaDoNo(raiz -> direito)) + 1;
    y -> altura = maior(alturaDoNo(y -> esquerdo), alturaDoNo(y -> direito)) + 1;

    /*
    retorna nova raiz da arvore = y
    */
    return y;
}

/*
Rotação dupla direita esquerda
*/

No* rotDirEsq(No* raiz){
    raiz -> direito = rotDir(raiz -> direito);
    return rotEsq(raiz);
}

/*
Rotação dupla esquerda direita
*/

No* rotEsqDir(No* raiz){
    raiz -> esquerdo = rotEsq(raiz -> esquerdo);
    return rotDir(raiz);
}

/*
Balancear arvore apos inserção / remocao
    Recebe: no que esta desbalanceado
    Retorna: ponteiro para a nova raiz apos balancear
    se o fator de balanceamento fb for < 1, a arvore pende para a direita: 
        caso 1 <= 0: continua pendendo para a direita
        caso 2 > 0: fb + -> muda a direção e pende para a esquerda
*/

No* balancear(No *raiz){
    int fb = fatorBalance(raiz);

    /*rot esq*/
    if(fb < -1 && fatorBalance(raiz -> direito) <= 0){
        raiz = rotEsq(raiz);
    }

    /*rot dir*/
    else if(fb > 1 && fatorBalance(raiz -> esquerdo) >= 0){
        raiz = rotDir(raiz);
    }

    /*rot dupla esq*/
    else if(fb > 1 && fatorBalance(raiz -> esquerdo) < 0){
        raiz = rotEsqDir(raiz);
    }

    /*rot dupla dir*/
    else if(fb < -1 && fatorBalance(raiz -> direito) > 0){
        raiz = rotDirEsq(raiz);
    }

    return raiz;
}

/*
Inserção de novo no
x -> valor a ser inserido
retorna: endereço do novo no ou nova raiz balanceado
*/

No* inserir(No *raiz, int x){
    if(raiz == NULL){
        /*arvore vazia*/
        return novoNo(x);
    }
    else{ /*insercao a esq ou dir*/
        if(x < raiz -> valor){
            raiz -> esquerdo = inserir(raiz -> esquerdo, x);
        }
        else if(x > raiz -> valor){
            raiz -> direito = inserir(raiz -> direito, x);
        }
        else{
            printf("\n Insercao nao realizada - numero ja existe\n"); /*x não existe*/
        }
    }

    /*recalcula a altura dos nos entre a raiz e o novo no inserido*/
    raiz -> altura = maior(alturaDoNo(raiz -> esquerdo), alturaDoNo(raiz -> direito)) + 1;

    /*Verifica se precisa rebalancear a arvore*/
    raiz = balancear(raiz);

    return raiz;
}

/*
Na AVL é necessário recalcular a altura da árvore após a remoção
    - o elemento que se quer remover é trocado de posição com algum filho
    - transforma o no a ser removido em uma folha, facilitando a remoção
    - após a remoção, a arvore pode desbalancear (alteração na altura)
    - precisa recalcular altura e rebalancear, caso necessário
*/
No* remover(No *raiz, int chave){
    if(raiz == NULL){
        printf("Valor nao encontrado\n");
        return NULL;
    } else {
            /*procura do no a ser removido*/
            if(raiz -> valor == chave){
                /*remover folha*/
                if(raiz -> esquerdo == NULL && raiz -> direito == NULL){
                    free(raiz);
                    printf("Folha removida: %d \n", chave);
                    return NULL;
                } else {
                /*remover no que possui 2 filhos*/
                if(raiz -> esquerdo != NULL && raiz -> direito != NULL){
                    No *aux = raiz -> esquerdo; /* vai pra esq depois pro maior dos menores yes!*/
                    while (aux -> direito != NULL){
                        aux = aux -> direito;
                    }
                    raiz -> valor = aux -> valor;
                    aux -> valor = chave;
                    printf("Elemento realocado: %d \n", chave);
                    raiz -> esquerdo = remover(raiz -> esquerdo, chave);

                } else {
                /*Renove no com so 1 filho (esq ou dir)*/
                No *aux;
                if(raiz -> esquerdo != NULL){
                    aux = raiz -> esquerdo;
                } else {
                    aux = raiz -> direito;
                }
                free(raiz);
                printf("Elemento removido: %d \n", chave);

                return aux;
            }
        }
    } else {
        if(chave < raiz -> valor){
            raiz -> esquerdo = remover(raiz -> esquerdo, chave);
        } else{
            raiz -> direito = remover(raiz -> direito, chave);
        }
    }

    /*Recalcula a altura de todos os nos entre a raiz e o no inserido*/
    raiz -> altura = maior(alturaDoNo(raiz -> esquerdo), alturaDoNo(raiz -> direito)) + 1;

    /*Verifica se precisa balancear*/
    raiz = balancear(raiz);

    return raiz;
}
}
/*
Impressão
*/

void imprimir(No *raiz, int level){
    int i;
    if(raiz){
        imprimir(raiz -> direito, level + 1);
        printf("\n\n");
    
        for(i = 0; i < level; i++){
            printf("\t");
        }

        printf("%d", raiz -> valor);
        imprimir(raiz -> esquerdo, level + 1);
    
    }
}


int main(){
    int option, valor;
    No *raiz = NULL;

    do{
        printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n\n");
        scanf("%d", &option);

        switch (option)
        {
        case 0:
            printf("Saida!");
            break;
        
        case 1:
            printf("Inserir\n");
            printf("\tDigite o valor a ser inserido na arvore AVL:\t");
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
            imprimir(raiz, 1);
            break;
        
        case 2:
            printf("\tDigite o valor a ser removido da arvore AVL:\t");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            imprimir(raiz, 1);
            break;
        
        case 3:
            printf("\tImpressao AVL:\t");
            imprimir(raiz, 1);
            break;
        
        default:
            printf("\tOpcao Invalida\n");
        }
    }while(option != 0);

    return 0;
}
