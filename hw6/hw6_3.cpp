#include <iostream>
#include <string>
extern "C" {
	#include "avl_ntudsa.h"
	//#include "avl.h"
}

using namespace std;
#define _MAX_GAME 100010

typedef unsigned long long long_int;

int disjoint_Set[_MAX_GAME]; //disjoint_Set[i] means ith game owner
int _NUM_OF_OWNER = 0;
int _TOTAL_GAME = 0;
struct avl_table *avl_tree[_MAX_GAME ];
int int_compare(const void *pa, const void *pb, void * param)
{
	int a = *(int *)pa;
	int b = *(int *)pb;
	if(a < b) return -1;
	else if (a > b)return +1;
	else return -1;
}

//first_incident: function prototype declaration
int find_owner(int);
void first_incident(int , int);
void inorder_probe( const struct avl_node*, const int);

//second_incident: function prototype declaration
void second_incident(int , long_int);
void inorder_integer_avl(const struct avl_node *,const long_int,
						 long_int *, int *, int);

int main()
{
	for(int i = 0; i < _MAX_GAME; i++)
		avl_tree[ i ] = avl_create(int_compare , NULL, NULL);

	int n = 0, m = 0;
	scanf("%d%d",&n, &m);
	_TOTAL_GAME = _NUM_OF_OWNER = n;

	disjoint_Set[ 0 ] = -1;
	delete avl_tree[ 0 ];

	int price = 0;
	for(int i = 1; i <= _TOTAL_GAME; i++)
	{
		scanf("%d", &price);
		disjoint_Set[i] = i;
		avl_probe(avl_tree[ i ], price);
	}
	
	string incident;
	for(int counter = 0; counter < m; counter++)
	{
		cin >> incident;
		if(incident == "1")
		{
			int i = 0, j = 0;
			scanf("%d%d",&i, &j);
			first_incident(i, j);
		}
		else if(incident == "2")
		{
			int i = 0;
			long_int s = 0;
			scanf("%d%llu",&i, &s);
			second_incident(i, s);
		}
	}
	return 0;
}
int find_owner(int c)
{
	if(disjoint_Set[ c ] == c)
		return c;
	else
		return disjoint_Set[ c ] = find_owner( disjoint_Set[ c ] );
}
void first_incident(int i, int j)
{	
	// CASE1: If u also owns the j-th computer game, 
	// u will simply switch to play her/his j-th game.

	i = find_owner(i);
	j = find_owner(j);
	if(disjoint_Set[ i ] == disjoint_Set[ j ])
		return;

	// CASE2: If u doesn’t own the j-th computer game, 
	// u will visit the person who owns the j-th game,
	// say v, and borrow all v’s computer games.

	disjoint_Set[ j ] = i;
	inorder_probe(avl_tree[ j ]->avl_root, i);
	delete avl_tree[ j ];

	_NUM_OF_OWNER--;
}

void inorder_probe(const struct avl_node* node, const int i)
{
	if(node == NULL)
		return;
	if(node->avl_link[0] != NULL)
		inorder_probe(node->avl_link[0], i);
	avl_probe(avl_tree[ i ], node->avl_data);
	if(node->avl_link[1] != NULL)
		inorder_probe(node->avl_link[1], i);
}
void inorder_integer_avl(const struct avl_node* node, const long_int s,
						 long_int* total , int* k, int* _DONE)
{
	if(node == NULL)
		return;

	//add "_DONE" flag to cut down on redundant recursion
	if(node->avl_link[0] != NULL && *_DONE){
		inorder_integer_avl(node->avl_link[0], s, total, k, _DONE);
	}

	if(*_DONE)
	{
		*total += node->avl_data;
		(*k)++;

		if(*total == s)
		{
			*_DONE = 0;
			return;
		}
		else if(*total > s)
		{
			*_DONE = 0;
			(*k)--;
			return;
		}
	}
	if(node->avl_link[1] != NULL && *_DONE)
		inorder_integer_avl(node->avl_link[1], s, total, k, _DONE);
}

void second_incident(int i, long_int s)
{
	i = find_owner(i);

	long_int* total = new long_int(0);
	int* k = new int(0);
	int* _DONE = new int (1); //boolean, indicates that k is found

	inorder_integer_avl(avl_tree[ i ]->avl_root, s, total, k, _DONE);

	cout << i << " " << *k << endl;
	delete total;
	delete _DONE;
	delete k;
}
