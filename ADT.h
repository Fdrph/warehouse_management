#ifndef _ADT_H
#define _ADT_H

#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

#define MAX_SIZE 	 150000
#define LOAD_FACTOR  0.65

/*
 A hash table implementada e' de procura linear.
 A localidade de referencia inerente a uma tabela
 sem pointeiros e cujos valores estao todos num vetor
 previne cache misses e torna este tipo de tabela
 muito rapido.
*/

int nr_elem, M;
Item *Table;

Item Max_item;
int max_not_empty;


/* Imprime para o ecra um vetor de Items */
void print_array_items(Item a[]);

/* Calcula a simples hash function (a mod b) */
int hash(Key a, int b);

/* Inicializa os valores de controlo e aloca memoria para a hash table */
void HT_init(int max);

/* Inserir um novo item na hash table ou renovar o seu valor se for encontrado */
int HT_insert(Item a);

/* Retirar um item da hash table */
int HT_delete(Key a);

/* Procurar pelo item que corresponde a key dada, devolvendo-o */
Item HT_search(Key a);

/* Faz rehash da tabela, construindo uma 2 vezes maior */
void HT_expand();

/* Percorrer a hash table toda, obter o item maximo */
void get_new_max();

/* Comparar com o Max_item atual, substituir se valor maior ou key menor*/
void update_max(Item a);

#endif