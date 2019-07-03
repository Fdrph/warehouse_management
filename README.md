# Warehouse Tracker

Programa que permite
registar as entradas e saídas de produtos num armazém. Cada produto
possui um código identificativo (que também designaremos
por chave) e a existência actual, expressa em número de unidades.
O programa deverá receber como input um conjunto de linhas que
começam com um dos caracteres listados na Tabela em baixo e que
indicam as operações a executar. Dada uma chave, a opção a permite
introduzir novas existências de um produto. A opção l permite listar as existências de cada produto,
enquanto que a opção m lista o produto com maior número de unidades em stock. A opção r permite
eliminar uma chave. Por fim, o comando x deverá terminar o programa, escrevendo o número de
produtos (ou chaves) diferentes guardados no sistema.
A chave representa o código identificativo ou chave de um produto. Corresponde a uma
sequência de 8 caracteres (sem espaços) sobre o alfabeto
Σ = {0,1, 2,3, 4, 5, 6, 7,8, 9, a, b, c, d, e, f }. O valor é um número inteiro representando o
número de unidades adicionadas ou removidas desse produto1
. Se valor for positivo
deverá incrementar esse número às existências desse produto.

Para isto foi implementada uma hash table linear para evitar cache misses sem ponteiros e radix sort LSD com counting sort
para a maior eficiencia possivel.
## Comandos
a - Incrementa ou reduz o número de unidades
associadas ao produto com o código dado. Se
o código não existir deverá ser criado um novo
produto com esse código.

l - Lista alfabeticamente todos os produtos.

m - Escreve o produto com o maior número de
unidades em stock.
r - Remove o produto com o código dado.
x - Termina o programa



Input:
a 60fdba63 4\
a c614e44d 149\
a ff4095a1 38\
a 60fdba63 -5\
l\
r c614e44d\
a 90adba63 4\
l\
x

Output:
60fdba63 0\
c614e44d 149\
ff4095a1 38\
60fdba63 0\
90adba63 4\
ff4095a1 38\
3
