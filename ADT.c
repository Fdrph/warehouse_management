#include "ADT.h"

void print_array_items(Item a[]) {
    int i;
    for(i = 0; i < nr_elem;i++) {
        print_item(a[i]);
    }
}


int hash(Key v, int len) { return v % len; }


void HT_init(int max) 
{
    Max_item = create_item(MAX_POSSIBLE_KEY, 0);
    max_not_empty = 0; //false


    nr_elem = 0;
    M = max;
    Table = (Item*)malloc(M*sizeof(Item));
    int i;
    for (i = 0; i < M; i++)
    {
        Table[i] = NULLitem;
    }
}


void update_max(Item new) 
{
    /* (unidades iguais E key novo < key antigo) OU unidades novo > unidades antigo */
    if ( units(new) > units(Max_item) || 
         (units(new) == units(Max_item) && key(new) < key(Max_item)) )
    {
        Max_item = new;
        max_not_empty = 1;
    }
}


void get_new_max() {
    max_not_empty = 0;
    Max_item = create_item(MAX_POSSIBLE_KEY, 0);
    int i;
    for (i = 0; i < M; i++)
    {
        if( !null(Table[i]) ) 
        {
            update_max(Table[i]);
        }
    }
}


int HT_insert(Item item)
{
    Key v = key(item);
    int i = hash(v, M);

    while ( !null(Table[i]) )
    {
        if ( v == key(Table[i]) )
        {
            Item new = update_item(Table[i], units(item));
            Table[i] = new;
            update_max(new);
            return 0;
        }
        i = (i+1) % M;
    }
    update_max(item);
    Table[i] = item;
    nr_elem++;
    if (nr_elem > LOAD_FACTOR*M)
        HT_expand();
    return 0;
}


int HT_delete(Key chave)
{

    int i = hash(chave, M);

    while ( !null(Table[i]) )
        if ( chave == key(Table[i]) )
            break;
        else 
            i = (i+1) % M;
    
    if ( null(Table[i]) )
        return -1;
    
    Table[i] = NULLitem;
    nr_elem--;

    Item t;
    int j;
    for (j = (i+1) % M; !null(Table[j]); j = (j+1) % M, nr_elem--) 
    {
        t = Table[j];
        Table[j] = NULLitem;
        HT_insert(t);
    }
    return 0;
}


Item HT_search(Key v)
{
    int i = hash(v, M);
    while ( !null(Table[i]) )
    {
        if ( v == key(Table[i]) )
            return Table[i];
        else
            i = (i+1) % M;
    }
    return NULLitem;
}

void HT_expand() {

    Item *t = Table;
    HT_init(2*M);
    int i;
    for(i = 0; i < M/2; i++) 
    {
        if (key(t[i]) != key(NULLitem))
            HT_insert(t[i]);
    }
    free(t);
}