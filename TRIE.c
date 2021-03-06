#include <stdio.h>
#include <stdlib.h>

typedef struct Trie 
{ 
	char ch;
	int  count;
	struct trie *subtrie; /* subtrie node */
	struct trie *child; /* First child node */
} Trie; 


Trie *trieInsert(Trie *root, char *key); // функция вставки узла
Trie *trieDelete(Trie *root, char *key); // удаление по ключу
void triePrint(Trie *root); // печать дерева
Trie *Destroy(Trie *root);

int main()
{
	 int i=0, k=0;
	 Trie *root = NULL;
	char arr[k][k],s;
 	FILE *ptrfile;
 	ptrfile=fopen( "mass.txt", "r");
	while ((fscanf(ptrfile, "%c",&s)!=EOF))
		{    if(!ptrfile) break;    //чтобы не делал лишнего
        k+=1;
		}

	rewind(ptrfile);    //перематываем файл для повторного чтения
 	while (!feof(ptrfile)){
        fscanf(ptrfile,"%s",arr[i]);
        if (i=0){
        	root = trieInsert(NULL, arr[i]);
        }
        else{
			root = trieInsert(root, arr[i]);
		}
       i++;
       }
	fclose(ptrfile);
	triePrint(root);
	Destroy(root);
	//triePrint(root);
}

//Создает пустой узел
Trie* trieCreate()
{
	Trie* node;
	if ( (node = malloc(sizeof(*node))) == NULL)
		return NULL;

	node->ch = '\0';
	node->count = 0;
	node->subtrie = NULL;
	node->child = NULL;

	return node;
}

//Поиск узла в Trie по ключу
/*
char *trie_lookup(Trie *root, char *key)
{
	Trie *node, *list;
	for (list = root; *key != '\0'; key++) {
		for (node = list; node != NULL; node = node->subtrie)
		{
			if (node->ch == *key)
			break;
		}
	if (node != NULL)
		list = node->child;
	else
		return NULL;
	}
		/* Check: Node must be a leaf node! */
/*	return node->value;
}*/

//Вставка узла в Trie
Trie *trieInsert(Trie *root, char *key)
{
	Trie *node, *father, *list;
	father = NULL;
	list = root;
	for (; *key != '\0'; key++) {
	/* Ищем узел subtrie */
		for (node = list; node != NULL; node = node->subtrie)
		{	
			if (node->ch == *key)
				break;
		}
		if (node == NULL) {
	/* Не нашли узел, добавляем новый*/
			node = trieCreate();
			node->ch = *key;
			node->count = 1;
			node->subtrie = list;
			if (father != NULL)
				father->child = node;
			else
				root = node;
				list = NULL;
		} else {
	/* Нашли узел. Переходим на следующий уровень.*/
			node->count++;
			list = node->child;
		}
		father = node;
	}
		return root;
} 

Trie *nodeDelete(Trie *root, Trie *father, char *key, int *found)
{
	Trie*node, *prev = NULL;
	*found = (*key == '\0' && root == NULL) ? 1 : 0;
	if (root == NULL || *key == '\0')
		return root;
	for (node = root; node != NULL;node = node->subtrie)
	{
		if (node->ch == *key)
			break;
		prev = node;
	}
	if (node == NULL)
		return root;
	nodeDelete(node->child, node, key + 1, found);
	if (*found > 0 && node->child == NULL) {
	/* Удаляем узел */
		if (prev != NULL)
			prev->subtrie = node->subtrie;
		else {
			if (father != NULL)
				father->child = node->subtrie;
			else
				root = node->subtrie;
		}
		free(node);
	}
	return root;
}

Trie *trieDestroy(Trie *root, Trie *father){
	Trie *node, *prev = NULL;

	if (root == NULL)
		return root;
	for (node = root; node != NULL;node = node->subtrie)
	{
		//printf("%x\n", node->subtrie);
		//printf("%c\n", node->ch);
		if (node->child != NULL)
			break;
		prev = node;
	}
	if (node == NULL)
	return root;
		//printf("child %c\n", node->ch);
	trieDestroy(node->child, node);
	if (node->child == NULL) {
	/* Удаляем узел */
		//printf("child %c\n", node->ch);
		if (prev != NULL)
			prev->subtrie = node->subtrie;
		else {
			if (father != NULL)
				father->child = node->subtrie;
			else
				root = node->subtrie;
		}
		free(node);
	}
	return root;
}

Trie *Destroy(Trie *root){
	return trieDestroy(root, NULL);
}

Trie *trieDelete(Trie *root, char *key)
{
	int found;
	return nodeDelete(root, NULL, key, &found);
}

void triePrint(Trie *root){

	int level = 0;
	return trie_print( root, level);
}

void trie_print(Trie *root, int level)
{
	Trie *node = root;
	int i;
	for (; node != NULL; node = node->subtrie)
	{
		for (i = 0; i < level; i++)
			printf(" ");
			printf("%c %d \n", node->ch, node->count);
		if (node->child != NULL)
			trie_print(node->child, level + 1);
	}
}