#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int mystrcmp(char *str1, char *str2, char ch){
	if(ch == 'w' || ch == 'b'){
		return own_str_cmp(str1, str2, ch);
	}
	
	if(ch == 'i')
		return strcasecmp(str1, str2);
	
	else
		return strcmp(str1, str2);
}

int own_str_cmp(char *str1, char *str2, char ch){ 
	short l1, l2, i = 0, j = 0;
	l1 = strlen(str1);
	l2 = strlen(str2);
	if(ch == 'w'){	
		while(i < l1 || j < l2){
			while(str1[i] == ' ')
				i++;
			while(str2[j] == ' ')
				j++;
				
			if(str1[i] == str2[j]){
				i++;
				//increment j
				j++;
			}
			else
				return 1;
				
			if(i == l1 + 1)
				i = l1;
			if(j == l2 + 1)
				j = l2;			
		} 
	}
	
	else if(ch == 'b'){
		short flag1 = 0, flag2 = 0;	

		while(i < l1 || j < l2){
			while(str1[i] == ' '){
				flag1 ++;
				i++;
			}
			
			while(str2[j] == ' '){
				flag2 ++;
				j++;
			}
			
			if((flag1 >= 1 && flag2 == 0) || (flag2 >= 1 && flag1 == 0))
				return 1;
					
			if(str1[i] == str2[j]){
				i++; 
				j++;
			}
			else
				return 1;
			
			flag1 = 0;
			flag2 = 0;
				
			if(i == l1 + 1)
				i = l1;
			if(j == l2 + 1)
				j = l2;			
		} 
	}
	
	
	return 0;
	
}

void init(list *l){
	l->front = NULL;
	l->rear = NULL;
}


void addnode(list *l, char *str){
	node *newnode = (node*)malloc(sizeof(node));
	strcpy(newnode->data, str);
	if(l->rear == NULL){
		newnode->line = 1;
		l->rear = newnode;
		newnode->previous = newnode;
		newnode->next = newnode;
		l->front = newnode;
	}
	else {
		newnode->line = l->front->line + 1;
		newnode->next = l->rear;
		l->rear->previous = newnode;
		l->front->next = newnode;
		newnode->previous = l->front;
		l->front = newnode;
	}
	
}

void init_lcs(list_lcs *l){
	l->front = NULL;
	l->rear = NULL;
}

void addnode_lcs(list_lcs *l, char *str, int l1, int l2){
	node_lcs *newnode = (node_lcs*)malloc(sizeof(node_lcs));
	strcpy(newnode->data, str);
	newnode->line1 = l1;
	newnode->line2 = l2;
	if(l->rear == NULL){
		l->rear = newnode;
		newnode->previous = newnode;
		newnode->next = newnode;
		l->front = newnode;
	}
	else{
		newnode->next = l->rear;
		newnode->previous = l->front;
		l->rear->previous = newnode;
		l->front->next = newnode;
		l->rear = newnode;
	}
}


int length(list l){
	int len = 0;
	node* ptr = l.rear;
	if(l.rear == NULL)
		return 0;
	
	do{
		len++;
		ptr = ptr->next;
	}while(ptr != l.rear);
	
	return len;
}


void printlist(list l){
	node *ptr = l.rear;
	int i = 0;
	if(l.rear == NULL)
		printf("\n");
	else{	
		do{
			for(i = 0; i < strlen(ptr->data); i++){
				printf("%c", ptr->data[i]);
			}
			printf("\n");
			ptr = ptr->next;
		}while(ptr != l.rear);
	}
}

void printlist_lcs(list_lcs l){
	node_lcs *ptr = l.rear;
	int i = 0;
	if(l.rear == NULL)
		printf("\n");
	else{	
		do{
			for(i = 0; i < strlen(ptr->data); i++){
				printf("%c", ptr->data[i]);
			}
			printf("\t(%d, %d)\n", ptr->line1, ptr->line2);
			ptr = ptr->next;
		}while(ptr != l.rear);
	}
}


int larger(int a, int b){
	if(a >= b)
		return a;
	else 
		return b;
}

list_lcs lcs(list l1, list l2, char ch){
	list_lcs l;
	init_lcs(&l);
	int k1 = length(l1), k2 = length(l2);
	if(k1 == 0 || k2 == 0)
		return l;	
	int i = 0, j = 0, lenlcs = 0, result = 0;
	int **table;
	table = (int **)malloc(sizeof(int *) * (k1+1));
	for(i = 0; i < k1 + 1; i++){
		table[i] = (int *)malloc(sizeof(int) * (k2 + 1));
		if(table[i] == NULL){
			printf("Memory allocation failed\n");
			exit(0);
		}
	}
	node *ptr = l1.rear;
	node *qtr = l2.rear;

	for(i = 0; i <= k1; i++){
		qtr = l2.rear;
		for(j = 0; j <= k2; j++){
			if(i == 0 || j == 0){
				table[i][j] = 0;
			}		
			else if(mystrcmp(ptr->previous->data, qtr->previous->data, ch) == 0){
				table[i][j] = 1 + table[i-1][j-1];
			}
			else{
				table[i][j] = larger(table[i-1][j], table[i][j-1]);
			}
			qtr = qtr->next;
		}
		ptr = ptr->next;
	}
	lenlcs = table[i-1][j-1];
	i = k1;
	j = k2;
	ptr = l1.front;
	qtr = l2.front;
	while(table[i][j]){
		if(table[i][j] != larger(table[i][j-1], table[i-1][j])){
			addnode_lcs(&l, ptr->data, ptr->line, qtr->line);
			ptr = ptr->previous;
			qtr = qtr->previous;
			i--;
			j--;
		}
		
		else{
			if(table[i][j] == table[i - 1][j]){
				ptr = ptr->previous;
				i--;

			}
			
			else{
				qtr = qtr->previous;
				j--;		
			}
	}	
	}
	
	
	return l;
}

void printfor_lcs(list l, int from, int to, char ch){
	node *ptr = l.rear;
	int i = 0, j = 0;
	while(ptr->line != from){
		if(ptr == l.front && l.front->line != from)
			break;
		ptr = ptr->next;
	}
	for(i = from; i < to + 1; i++){
		printf("%c ", ch);
		for(j = 0; j < strlen(ptr->data); j++)
			printf("%c", ptr->data[j]);
		printf("\n");
		ptr = ptr->next;
	}
}

int length_lcs(list_lcs l){
	int len = 0;
	node_lcs* ptr = l.rear;
	if(l.rear == NULL)
		return 0;
	
	do{
		len++;
		ptr = ptr->next;
	}while(ptr != l.rear);
	
	return len;
}

