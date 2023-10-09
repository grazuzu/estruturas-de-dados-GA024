# include <stdio.h>
# include <stdlib.h>
#include <unistd.h>

int counter = 0;

struct no {
    int iVal;
    struct no *pprox;
}**pilha[3];

int empilha(int iVal, struct no **source){
    struct no *aux;
    aux = (struct no*)malloc(sizeof(struct no));

    if (!aux) return -1;

    aux -> iVal = iVal;
    aux -> pprox = *source;

    *source = aux;

    return 0;
}

int desempilha(int *piVal, struct no *source, struct no **temp){
    struct no *aux;
    if(!source) return -2;

    aux = source;
    *temp = source -> pprox;
    *piVal = aux -> iVal;
    free(aux); /*?*/

    return 0;
}

void print_hanoi(struct no *pilha){
    if(!pilha){
        return;
    }
    print_hanoi(pilha -> pprox);
    printf("%d", pilha -> iVal);
}

void imprime_tower(){
    printf("\nO: ");
    print_hanoi(*pilha[0]);
    printf("\nA: ");
    print_hanoi(*pilha[1]);
    printf("\nD: ");
    print_hanoi(*pilha[2]);
}

int move_disk(struct no**source, struct no **dest, char source_name, char dest_name){
    int disk_number;
    counter += 1;

    desempilha(&disk_number, *source, source);
    empilha(disk_number, dest);
    printf("\n%c -> %c\n", source_name, dest_name);
    printf("Numero de movimentos: %d\n", counter);
    imprime_tower();
    printf("\n");
    sleep(1);

    return 0;
}

void hanoi_tower(int disk_number, struct no **source, struct no **aux, struct no **dest, char source_name, char aux_name, char dest_name){
    if(disk_number == 1){
        move_disk(source, dest, source_name, dest_name);

        return;
    }

    hanoi_tower(disk_number - 1, source, dest, aux, source_name, dest_name, aux_name);
    move_disk(source, dest, source_name, dest_name);
    hanoi_tower(disk_number - 1, aux, source, dest, aux_name, source_name, dest_name);
}

int main(){
    int disk_number;
    int i;
    printf("Programa para Resolver Torre de Hanoi utilizando pilha e recursao\n");
    printf("(O -> Origem  A -> Auxiliar  D -> Destino)\n");
    printf("Escolha a quantidade de discos: ");
    scanf("%d", &disk_number);

    struct no *source, *aux, *dest;

    for(i = disk_number; i > 0; i--)
        empilha(i, &source);
    
    pilha[0] = &source;
    pilha[1] = &aux;
    pilha[2] = &dest;

    char source_name = 'O';
    char aux_name = 'A';
    char dest_name = 'D';

    printf("Torre de Hanoi: ");
    imprime_tower();
    printf("\n");

    hanoi_tower(disk_number, &source, &aux, &dest, source_name, aux_name, dest_name);

    return 0;
}