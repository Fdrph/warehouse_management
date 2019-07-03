#ifndef _ITEM_H
#define _ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define MAX_POSSIBLE_KEY 0xFFFFFFFF

#define key(a)    (a.key)
#define units(a)  (a.units)
#define null(a)   (a.null == 0)

typedef uint32_t Key;

/*
 chave = sequencia de 8 chars 
 -> 8 bytes em memoria por chave - 64bits
 chave = numero positivo hexadecimal 8 casas (uint32_t tem sempre 32 bits)
 -> 4 bytes em memoria por chave - 32bits
 logo tamanho Item(8bytes) = tamanho de um pointer *Item x64
 logo pointer e desnecessario
*/
typedef struct item {
    Key      key;
    int16_t  units;
    int8_t  null;
}Item;

Item NULLitem;

/* Inizializa a flag null do NULLitem a 0 */
void init_nullitem();

/* Criar um novo Item */
Item create_item(Key a, int b);

/* Renovar as unidades de um Item */
Item update_item(Item a, int b);

/* Imprime um Item para o ecra */
void print_item(Item a);

/* Compara as keys de dois Items */
int cmp_item(Item a, Item b);


#endif