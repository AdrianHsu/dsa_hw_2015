#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "avl.h"
#include "bst.h"
#include "rb.h"


#define MAX_STRLEN 150 //128 as MAX

void preorder_integer_avl(const struct avl_node *node)
{
	if(node == NULL)
		return;
	printf("%s ", (char *)node->avl_data);
	if(node->avl_link[0] != NULL || node->avl_link[1] != NULL)
	{
		putchar('(');
		preorder_integer_avl(node->avl_link[0]);
		putchar(',');
		putchar(' ');
		preorder_integer_avl(node->avl_link[1]);
		putchar(')');
	}
}
void preorder_integer_bst(const struct bst_node *node)
{
	if(node == NULL)
		return;
	printf("%s ", (char *)node->bst_data);
	if(node->bst_link[0] != NULL || node->bst_link[1] != NULL)
	{
		putchar('(');
		preorder_integer_bst(node->bst_link[0]);
		putchar(',');
		putchar(' ');
		preorder_integer_bst(node->bst_link[1]);
		putchar(')');
	}
}
void preorder_integer_rb(const struct rb_node *node)
{
	if(node == NULL)
		return;
	printf("%s ", (char *)node->rb_data);
	if(node->rb_link[0] != NULL || node->rb_link[1] != NULL)
	{
		putchar('(');
		preorder_integer_rb(node->rb_link[0]);
		putchar(',');
		putchar(' ');
		preorder_integer_rb(node->rb_link[1]);
		putchar(')');
	}
}
int dic_compare(const void *pa, const void *pb, void * param)
{
	const char* str1 = (const char*)pa;
	const char* str2 = (const char*)pb;	

	const int str1_len = strlen(str1);
	const int str2_len = strlen(str2);

	int i = 0;
	while(1)
	{
		if(i == str1_len && i == str2_len)
			return 0;

		if(i == str1_len)
			return -1;
		else if(i == str2_len)
			return +1;
		
		if(str1[i] < str2[i])
			return -1;
		else if(str1[i] > str2[i])
			return +1;

		i++;
	}
	printf("ERROR\n");
	return 0;

}

int main(){
	
	struct avl_table *avl_tree ;
	struct bst_table *bst_tree ;
	struct rb_table *rb_tree ;
	avl_tree = avl_create(dic_compare , NULL, NULL);
	bst_tree = bst_create(dic_compare , NULL, NULL);
	rb_tree = rb_create(dic_compare , NULL, NULL);
	
	for(int i = 0; i < 32; i++)
	{
		char *element = (char*)malloc(sizeof(char)* MAX_STRLEN);
		if(scanf("%s", element) == 1)
		{
			avl_probe(avl_tree, element);
			bst_probe(bst_tree, element);
			rb_probe(rb_tree, element);
		}
	}

	preorder_integer_avl(avl_tree->avl_root);
	puts("");
	preorder_integer_bst(bst_tree->bst_root);
	puts("");
	preorder_integer_rb(rb_tree->rb_root);
	puts("");
	return 0 ;
}