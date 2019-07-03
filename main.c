#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <ctype.h>
#include "ADT.h"
#include "Item.h"

#define MASK 0x000000FF

/* 
 retirar 8 bits que comecam na posicao p:
 ->     11 01010101 10010010
 1. >> 8*1
 ->     00 00000011 01010101
 2. AND 00 00000000 11111111   mask
 ->     00 00000000 01010101
*/
#define get8bits(a, p) (( a >> 8*p )&(MASK))

/* Prototipos */
void comando_A(Key a, int b);
void comando_L();
void comando_M();
void comando_R(Key a);
void comando_X();


int main()
{
    /* Inicializacao */
    HT_init(MAX_SIZE);
    init_nullitem();

    Key chave;
    int unidades;
    char c;
    while(1)
    {
        c = getchar();

        switch(c)
        {
            case 'a':
                scanf("%x", &chave);
                scanf("%d", &unidades);
                comando_A(chave, unidades);
                getchar();
                break;
            case 'l':
                comando_L();
                getchar();
                break;
            case 'm':
                comando_M();
                getchar();
                break;
            case 'r':
                scanf("%x", &chave);
                comando_R(chave);
                getchar();
                break;
            case 'x':
                comando_X();
                return EXIT_SUCCESS;
            default:
                printf("ERRO: Comando desconhecido\n");
                getchar();
        }
    }
    return EXIT_FAILURE;
}



void comando_A(Key chave, int unidades) 
{
    Item t = create_item(chave, unidades);
    HT_insert(t);

    /* 
       precisamos de percorrer a hash table toda
       so se o item que e' max atual for alterado
       de forma a que o seu valor diminua
    */
    if (chave == key(Max_item) && unidades < 0)
        get_new_max();
}


/* 
 Implementa radix sort LSD com counting sort
 queremos ordenar nr de 32 bits ou 8 casas hexadecimais:
 .aplicamos counting sort a pares de 2 casas hexadecimais
       FF FF FF FF
 .entao fazemos no total 4 passes de counting sort
 .FF = 256, entao complexidade = 4 * (nr_elem + 256) = O(4N + 1024) = O(N)
*/
void comando_L() 
{

    int n = nr_elem; // tamanho do vetor de items a ordenar
    Item *items = malloc(n * sizeof(Item));
    Item *aux = malloc(n * sizeof(Item));
    
    int i, c = 0;
    for (i = 0; i < M; i++)
    {
        if( !null(Table[i]) ) 
        {
            items[c] = Table[i];
            c++;
        }
    }

    int b = 8;  // nr bits por cada counting sort pass
    int p;      // nr passes do counting sort
    for (p = 0; p < 32/b; p++) // 4 passes porque 32bits/8
    {
        int count[256] = {0}; // 2^8, todos numeros possiveis c 8 bits
        // guarda o nr de ocorrencias em count[]
        for (i = 0; i < n; i++)
            count[ get8bits(key(items[i]), p) ]++;
        for (i = 1; i < 1<<b; i++)
            count[i] += count[i - 1];
        // constroi vetor ordenado
        for (i = n - 1; i >= 0; i--)
            aux[--count[ get8bits(key(items[i]), p) ] ] = items[i];
        // copyback
        for (i = 0; i < n; i++)
            items[i] = aux[i];
    }
    
    print_array_items(items);
    free(items); free(aux);
}


void comando_M() 
{
    if(max_not_empty)
        print_item(Max_item);
}


void comando_R(Key chave)
{
    HT_delete(chave);

    /* 
       precisamos de percorrer a hash table toda
       se o item que e max atual for removido
    */
    if (chave == key(Max_item))
        get_new_max();
}


void comando_X() 
{
    free(Table);
    printf("%d\n", nr_elem);
}



