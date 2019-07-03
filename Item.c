#include "Item.h"

void init_nullitem() { NULLitem.null = 0; }


Item create_item(Key chave, int unidades) 
{
	
	Item x;
	x.key = chave;
	x.units = unidades;
	x.null = 1;
	return x;
}


Item update_item(Item t, int unidades) 
{
	
	if(unidades < 0 && abs(unidades) > t.units) 
	{
		t.units = 0; 
		return t;
	}
	t.units += unidades;
	return t;
}


void print_item(Item a) 
{
	printf("%08x %d\n", a.key, a.units);
}


int cmp_item(Item a, Item b) 
{
	return a.key == b.key;
}