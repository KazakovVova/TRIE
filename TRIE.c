#include <stdio.h>
#include <stdlib.h>

typedef struct Trie 
{ 
	char *value;
	char ch;
	struct trie *sibling; /* Sibling node */
	struct trie *child; /* First child node */
} Trie; 


//Создает пустой узел Trie
Trie* trie_create()
{
	Trie* node;
	if ( (node = malloc(sizeof(*node))) == NULL)
		return NULL;
	node->ch = '\0';
	node->value = NULL;
	node->sibling = NULL;
	node->child = NULL;
	return node;
}

//Поиск узла в Trie по ключу
char *trie_lookup(Trie *root, char *key)
{
	Trie *node, *list;
	for (list = root; *key != '\0'; key++) {
		for (node = list; node != NULL;
			node = node->sibling)
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
	return node->value;
}

//Вставка узла в Trie
Trie *trie_insert(Trie *root, char *key, char *value)
{
	Trie *node, *parent, *list;
	parent = NULL;
	list = root;
	for (; *key != '\0'; key++) {
	/* Lookup sibling node */
		for (node = list; node != NULL;
			node = node->sibling)
		{
			if (node->ch == *key)
				break;
		}
		if (node == NULL) {
	/* Node not found. Add new node */
			node = trie_create();
			node->ch = *key;
			node->sibling = list;
			if (parent != NULL)
				parent->child = node;
			else
				root = node;
				list = NULL;
		} else {
	/* Node found. Move to next level */
			list = node->child;
		}
		parent = node;
	}
	/* Update value in leaf */
	if (node->value != NULL)
		free(node->value);
		node->value = strdup(value);
		return root;
} 

Trie *trie_delete_dfs(Trie *root, Trie *parent, char *key, int *found)
{
	Trie*node, *prev = NULL;
	*found = (*key == '\0' && root == NULL) ? 1 : 0;
	if (root == NULL || *key == '\0')
		return root;
	for (node = root; node != NULL;node = node->sibling)
	{
		if (node->ch == *key)
			break;
		prev = node;
	}
	if (node == NULL)
		return root;
	trie_delete_dfs(node->child, node, key + 1, found);
	if (*found > 0 && node->child == NULL) {
	/* Delete node */
		if (prev != NULL)
			prev->sibling = node->sibling;
		else {
			if (parent != NULL)
				parent->child = node->sibling;
			else
				root = node->sibling;
		}
		free(node->value);
		free(node);
	}
	return root;
}

Trie *trie_delete(Trie *root, char *key)
{
	int found;
	return trie_delete_dfs(root, NULL, key, &found);
}

void trie_print(Trie *root, int level)
{
	Trie *node;
	int i;
	for (node = root; node != NULL; node = node->sibling)
	{
		for (i = 0; i < level; i++)
			printf(" ");
		if (node->value != NULL)
			printf("%c (%s)\n", node->ch, node->value);
		else
			printf("%c \n", node->ch);
		if (node->child != NULL)
			trie_print(node->child, level + 1);
	}
}


int main()
{
	Trie *root = NULL;
	root = trie_insert(NULL, "bars", "60");
	//root = trie_insert(root, "baribal", "100");
	//root = trie_insert(root, "kit", "3000");
	//root = trie_insert(root, "lev", "500");
	//root = trie_insert(root, "bars", "70");
	trie_print(root, 0);
	//printf("Lookup 'bars': %s\n",trie_lookup(root, "bars"));
	root = trie_delete(root, "bars");
	printf("Delete\n");
	trie_print(root, 0);
	return 0;
}
