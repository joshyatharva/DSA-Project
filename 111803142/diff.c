#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void printline(char *str){ 
	int i = 0;							
	for(i = 0; i < strlen(str); i++)
		printf("%c", str[i]);
		printf("\n");
}

void print_with_spaces(char *str){
	int i = 0, l = 0;
	if(str == NULL){
		printf("\t\t\t\t\t\t\t\t");
		return;
	}
	l = strlen(str);
	for(i = 0; i < 48; i++){
		if(i < l){
			if(str[i] == '\t')
				printf(" ");
			else
				printf("%c", str[i]);
				
		}
		else
			printf(" ");
	}
	printf("\t\t");
}


void getdiff(list_lcs l, list l1, list l2){
	node_lcs *ptr = l.rear;
	int k1 = length(l1), k2 = length(l2);
	do{
		if(ptr == NULL){
			if(k1 == 1 && k2 == 1)
				printf("1c1\n");
			else if(k1 == 1 && k2 != 1)
				printf("1c1,%d\n", k2);
			else if(k2 == 1 && k1 != 1)
				printf("1,%dc1\n", k1);
			else
				printf("1,%dc1,%d\n", k1, k2);
			printfor_lcs(l1, 1, k1, '<');
			printf("---\n");
			printfor_lcs(l2, 1, k2, '>');
			exit(0);
		}
		
		if(ptr == l.rear){
			if(ptr->line1 > 1 && ptr->line2 == 1){
				if(ptr->line1 == 2)
					printf("%dd0\n", ptr->line1 - 1);
				else
					printf("1,%dd0\n", ptr->line1 - 1);

				printfor_lcs(l1, 1, ptr->line1-1, '<');
			}
			else if(ptr->line1 > 1 && ptr->line2 > 1){
				if(ptr->line1 == 2 && ptr->line2 == 2)
					printf("1c1\n");
				else if(ptr->line1 == 2 && ptr->line2 >2)
					printf("1c1,%d\n", ptr->line2 - 1);
				else if(ptr->line2 == 2 && ptr->line1 > 2)
					printf("1,%dc1\n", ptr->line1 - 1);
				else
					printf("1,%dc1,%d\n", ptr->line1, ptr->line2);
				
				printfor_lcs(l1, 1, ptr->line1-1, '<');
				printf("---\n");
				printfor_lcs(l2, 1, ptr->line2-1, '>');
			}
			else if(ptr->line1 == 1 && ptr->line2 > 1){
				if(ptr->line2 == 2)
					printf("0a1\n");
				else
					printf("0a1,%d\n", ptr->line2 - 1);
	
				printfor_lcs(l2, 1, ptr->line2-1, '>');
			}
		}
		
		
		else{
			if((ptr->line1 == (ptr->previous->line1 + 1)) && (ptr->line2 != (ptr->previous->line2 + 1))){
				if(ptr->line2 == ptr->previous->line2 + 2){
					printf("%da%d\n", ptr->line1-1, ptr->line2 - 1);
					
				}
				else if(ptr->line2 > ptr->previous->line2 + 2){
					printf("%da%d,%d\n", ptr->line1-1, ptr->previous->line2 + 1, ptr->line2-1);
					
				}
				
				printfor_lcs(l2, ptr->previous->line2+1, ptr->line2-1, '>');					 
			}
			
			else if((ptr->line2 == (ptr->previous->line2 + 1)) && (ptr->line1 > (ptr->previous->line1 + 1))){
				if(ptr->line1 == ptr->previous->line1 + 2)
					printf("%dd%d\n", ptr->line1-1, ptr->line2-1);
				else if(ptr->line1 > ptr->previous->line1 + 2)
					printf("%d,%dd%d\n", ptr->previous->line1+1, ptr->line1-1, ptr->line2-1);
					
				printfor_lcs(l1, ptr->previous->line1+1, ptr->line1-1, '<');	
			}
			
			else if((ptr->line1 != (ptr->previous->line1 + 1) ) && (ptr->line2 != (ptr->previous->line2 + 1)))
			{				
				if((ptr->line1 == (ptr->previous->line1+2)) && (ptr->line2 == (ptr->previous->line2+2)))
					printf("%dc%d\n", ptr->line1-1, ptr->line2-1);
				else if((ptr->line1 == (ptr->previous->line1+2)) && (ptr->line2 > (ptr->previous->line2+2)))
					printf("%dc%d,%d\n", ptr->line1-1, ptr->previous->line2+1, ptr->line2-1);
				else if((ptr->line1 > (ptr->previous->line1+2)) && (ptr->line2 == (ptr->previous->line2+2)))
					printf("%d,%dc%d\n", ptr->previous->line1+1, ptr->line1-1, ptr->line2-1);
				else if((ptr->line1 > (ptr->previous->line1+2)) && (ptr->line2 > (ptr->previous->line2+2)))
					printf("%d,%dc%d,%d\n", ptr->previous->line1+1, ptr->line1-1, ptr->previous->line2+1, ptr->line2-1);
					
				printfor_lcs(l1, ptr->previous->line1+1, ptr->line1-1, '<');
				printf("---\n");
				printfor_lcs(l2, ptr->previous->line2+1, ptr->line2-1, '>');
			}
		}
		
		if(ptr == l.front){
			if(ptr->line1 == k1 && ptr->line2 < k2){
				if(ptr->line2 == (k2 - 1))
					printf("%da%d\n", k1, k2);
				else
					printf("%da%d,%d\n", k1, ptr->line2 + 1, k2);
				
				printfor_lcs(l2, ptr->line2+1, k2, '>');
			}
			else if(ptr->line1 < k1 && ptr->line2 == k2){
				if(ptr->line1 == (k1 - 1))
					printf("%dd%d\n", k1, k2);
				else
					printf("%d,%dd%d\n", ptr->line1 + 1, k1, k2);
				
				printfor_lcs(l1, ptr->line1+1, k1, '<');
			}
			else if(ptr->line1 < k1 && ptr->line2 < k2){
				if(ptr->line1 == k1 - 1 && ptr->line2 == k2-1)
					printf("%dc%d\n", k1, k2);
				else if(ptr->line1 == k1 - 1 && ptr->line2 < k2-1)
					printf("%dc%d,%d\n", k1, ptr->line2+1, k2);
				else if(ptr->line1 < k1 - 1 && ptr->line2 == k2-1)
					printf("%d,%dc%d\n", ptr->line1+1, k1, k2);
				else 
					printf("%d,%dc%d,%d\n", ptr->line1+1, k1, ptr->line2+1, k2);
				
				
				printfor_lcs(l1, ptr->line1+1, k1, '<');
				printf("---\n");
				printfor_lcs(l2, ptr->line2+1, k2, '>');
			}
		}
		
		ptr = ptr->next;
	}while(ptr != l.rear);
}

void _cdiff(list_lcs l, list l1, list l2){
	int k1 = length(l1), k2 = length(l2), i = 0, j = 0;
	node_lcs *ptr = l.rear;
	node *qtr = NULL;
	short flag = 0;
	printf("k1  = %d\n", k1);
	printf("k2  = %d\n", k2);
	if(k1 == k2 && k1 == length_lcs(l))
		return;
	
	printf("***************\n");
	if(k1 == 0)
		printf("*** 0 ****\n");
	else if(k1 == 1)
		printf("*** 1 ****\n");
	else
		printf("*** 1,%d ****\n", k1);

	
	if(l.front == NULL && l.rear == NULL){
		if(l1.front == NULL && l2.front != NULL){
			qtr = l2.rear;
			if(k2 == 1)
				printf("--- 1 ----\n");
			else
				printf("--- 1,%d ----\n", k2);
			
			do{
				printf("+ ");
				printline(qtr->data);
				qtr = qtr->next;			
			}while(qtr != l2.rear);			
		}
		else if(l2.front == NULL && l1.front != NULL){
			qtr = l1.rear;
			do{
				printf("- ");
				printline(qtr->data);
				qtr = qtr->next;			
			}while(qtr != l1.rear);
			printf("--- 0 ----\n");
		}
		else{
			qtr = l1.rear;
			do{
				printf("! ");
				printline(qtr->data);
				qtr = qtr->next;			
			}while(qtr != l1.rear);
			
			if(k2 == 1)
				printf("--- 1 ----\n");
			
			else
				printf("--- 1,%d ----\n", k2);
			
			qtr = l2.rear;
			
			do{
				printf("! ");
				printline(qtr->data);
				qtr = qtr->next;			
			}while(qtr != l2.rear);
			
			
		}
	}
	else{
		qtr = l1.rear;
		do{
			
			if(strcmp(ptr->data, qtr->data) == 0){
				printf("  "); //2 spaces
				printline(qtr->data);
				if(ptr != l.front)
					ptr = ptr->next;
				qtr = qtr->next;
				continue;
			}
		
			else if(ptr == l.rear){
				if(ptr->line1 > qtr->line && ptr->line2 == 1){
					
					printf("- ");
					printline(qtr->data);
					qtr = qtr->next;
					continue;
				}
				else if(ptr->line1 > qtr->line && ptr->line2 > 1){
					printf("! ");
					printline(qtr->data);
					qtr = qtr->next;
					continue;
				}
			}
			else{
				if(ptr->line2 == ptr->previous->line2 + 1 && ptr->line1 > ptr->previous->line1 + 1){
					
					if(k2 > ptr->line2 && ptr == l.front){
						if(flag == 0)
							printf("- ");
						else
							printf("! ");
						flag = 1;
					}
					else
						printf("- ");
					printline(qtr->data);
					qtr = qtr->next;
					continue;
				}
				else if(ptr->line2 > ptr->previous->line2 + 1 && ptr->line1 > ptr->previous->line1 + 1){
					printf("! ");
					printline(qtr->data);
					qtr = qtr->next;
					continue;
				}
				
			}
			if(ptr == l.front){
				if(ptr->line2 == k2 && ptr->line1 < k1){
					
					printf("- ");
					printline(qtr->data);
				}
				else if(ptr->line2 < k2 && ptr->line1 < k1){
					printf("! ");
					printline(qtr->data);
				}
			}
			qtr = qtr->next;
			
		}while(qtr != l1.rear);
		
		printf("--- 1,%d ----\n", k2);
		qtr = l2.rear;
		ptr = l.rear;
		do{
			
			if(strcmp(ptr->data, qtr->data) == 0){
				printf("  "); //2 spaces
				printline(qtr->data);
				
				if(ptr != l.front)
					ptr = ptr->next;
			
				qtr = qtr->next;
				continue;
			}
			else if(ptr == l.rear){
					
					if(ptr->line1 == 1 && ptr->line2 > 1 || (ptr->line1 == k1 && ptr->line2 < qtr->line)){
						
						printf("+ ");
						printline(qtr->data);
						qtr = qtr->next;
						continue;				
					}
					else if(ptr->line1 > 1 && ptr->line2 > 1){
						
						printf("! ");
						printline(qtr->data);
						qtr = qtr->next;
						continue;
					}
				
			
			}
			else{
				
				if((ptr->line1 == (ptr->previous->line1 + 1)) && (ptr->line2 > (ptr->previous->line2 + 1))){
					
					printf("+ ");
					printline(qtr->data);
					qtr = qtr->next;
					continue;
				}	
				else if((ptr->line1 > (ptr->previous->line1 + 1)) && (ptr->line2 > (ptr->previous->line2 + 1))){
					
					printf("! ");
					printline(qtr->data);
					qtr = qtr->next;
					continue;
				}
				
			}
			if(ptr == l.front){
				
				if(ptr->line1 == k1 && ptr->line2 < k2){
					
					printf("+ ");
					printline(qtr->data);
				}
				else if(ptr->line1 < k1 && ptr->line2 < k2){
					
					printf("! ");
					printline(qtr->data);
				}
			}
			qtr = qtr->next;
		}while(qtr != l2.rear);
	}
		
}

void _ydiff(list_lcs l, list l1, list l2){
	int k1 = length(l1), k2 = length(l2), k = 0, k3, flag = 0, flag1 = 0, flag2 = 0;
	k1 > k2 ? (k3 = k1) : (k3 = k2);
	
	if(k1 == k2 && k1 == 0)
		return;
	node *ptr = l1.rear, *qtr = l2.rear;
	node_lcs *ltr = l.rear;

	if(k1 == k2 && k1 == length_lcs(l)){
		do{
			print_with_spaces(ptr->data);
			printf("  ");			
			printline(qtr->data);
			ptr = ptr->next;
			qtr = qtr->next;
		}while(ptr != l1.rear);
		return;	
	}
	else if(k1 == 0 && k2 != 0){
		do{
			
			print_with_spaces(NULL);										
			printf("> ");
			printline(qtr->data);
			
			qtr = qtr->next;
		}while(qtr != l2.rear);
		return;
	}
	
	else if(k2 == 0 && k1 != 0){
		do{
			print_with_spaces(ptr->data);
			printf("< \n");
			
			ptr = ptr->next;
			
		}while(ptr != l1.rear);
		return;
	}
	else{
		if(l.front == NULL){ 
			do{
				if(k1 < k2){
					if(ptr->line < k1){
						print_with_spaces(ptr->data);
						printf("| ");
						printline(qtr->data);
						ptr = ptr->next;
						qtr = qtr->next;	
					}
					else{
						if(flag1 == 0){
							print_with_spaces(ptr->data);
							printf("| ");
							printline(qtr->data);
							flag1 = 1;
							qtr = qtr->next;
						}
						else{
							if(qtr->line < k2){
								print_with_spaces(NULL);
								printf("> ");
								printline(qtr->data);
								qtr = qtr->next;
							}
							else{
								print_with_spaces(NULL);
								printf("> ");
								printline(qtr->data);
								flag2 = 1;
							}
						}
					}
				}
				else{
					if(qtr->line < k2){
						print_with_spaces(ptr->data);
						printf("| ");
						printline(qtr->data);
						ptr = ptr->next;
						qtr = qtr->next;
					}
					else{
						if(flag2 == 0){
							print_with_spaces(ptr->data);
							printf("| ");
							printline(qtr->data);
							if(ptr->line == k1)
								flag1 = 1;
							else
								ptr = ptr->next;
							flag2 = 1;
							
						}
						else{
							print_with_spaces(ptr->data);
							printf("< \n");
							if(ptr->line == k1)
								flag1 = 1;
							else
								ptr = ptr->next;
						}
					}
				}		
			}while(flag1 != 1 || flag2 != 1);
			
		}
		else if(l.front != NULL){
				do{
					if(ptr->line < ltr->line1){
						if(ltr->line2 == qtr->line){
								print_with_spaces(ptr->data);
								printf("< \n");
								if(ptr != l1.front)
									ptr = ptr->next;
						}
						else if(qtr->line < ltr->line2){	
							print_with_spaces(ptr->data);
							printf("| ");
							printline(qtr->data);
							ptr = ptr->next;
							qtr = qtr->next;
						}
					}
					else if(ptr->line == ltr->line1){
						if(qtr->line < ltr->line2){
							print_with_spaces(NULL);
							printf("> ");
							printline(qtr->data);
							qtr = qtr->next;
						}
						else if(qtr->line == ltr->line2){
							print_with_spaces(ptr->data);
							printf("  ");
							printline(qtr->data);
							if(ptr != l1.front)	
								ptr = ptr->next;
							else
								flag1 = 1;
							if(qtr != l2.front)
								qtr = qtr->next;
							else
								flag2 = 1;
							if(ltr != l.front)
								ltr = ltr->next;
						}
						else if(qtr->line > ltr->line2){
							print_with_spaces(NULL);
							printf("> ");
							printline(qtr->data);
							if(qtr != l2.front)
								qtr = qtr->next;
							else
								flag2 = 1;
						}
					}
					else if(ptr->line > ltr->line1){
						if(qtr->line > ltr->line2){
							if(ptr->line == k1){
								if(flag1 == 0){
									print_with_spaces(ptr->data);
									if(qtr->line == k2){
										if(flag2 == 0){
											printf("| ");
											printline(qtr->data);
											flag2 = 1;
										}
										else{
											printf("< \n");
										}
									}
									else{
										printf("| ");
										printline(qtr->data);
										qtr = qtr->next;
									}
									flag1 = 1;
								}
								else{
									print_with_spaces(NULL);
									printf("> ");
									printline(qtr->data);
									if(qtr->line == k2)
										flag2 = 1;
									else
										qtr = qtr->next;
								}
							}
							else{
								print_with_spaces(ptr->data);
								if(qtr->line < k2){
									printf("| ");
									printline(qtr->data);
									if(qtr != l2.front)
										qtr = qtr->next;
								}
								else{
									if(flag2 == 0){
										printf("| ");
										printline(qtr->data);
										flag2 = 1;
									}
									else{
										printf("< \n");
									}
								}
								ptr = ptr->next;
							}
						}
						else{
							print_with_spaces(ptr->data);
							if(flag2 == 0){
								printf("| ");
								printline(qtr->data);
								flag2 = 1;
							}
							else{
								printf("< \n");
								if(ptr->line == k1){
									flag1 = 1;
									//flag2 =1;
								}
							}
							ptr = ptr->next;
						}
					}
		
			}while(flag1 != 1 || flag2 != 1);
		}
	}
}
	
void _udiff(list_lcs l, list l1, list l2){
	int k1 = length(l1), k2 = length(l2), k3 = length_lcs(l), i = 0, j = 0;
	if(k1 == k2 && k1 == k3)
		return;
	
	node *ptr = l1.rear;
	node *qtr = l2.rear;
	node_lcs *ltr = l.rear;
	if(k1 == 1){
		if(k2 == 1)
			printf("@@ -1 +1 @@\n");
			
		else if(k2 == 0)
			printf("@@ -1 +0,0 @@\n");
		
		else
			printf("@@ -1 +1,%d @@\n", k2);
	}
	
	else if(k2 == 1){
		if(k1 == 0)
			printf("@@ -0,0 +1 @@\n");
		else		
			printf("@@ -1,%d +1 @@\n", k1);
	}
	
	else
		printf("@@ -1,%d +1,%d @@\n", k1, k2);
	
	if(l.rear == NULL){
		do{
			printf("-");
			printline(ptr->data);
			ptr = ptr->next;
		}while(ptr != l1.rear);
		ptr = l2.rear;
		do{
			printf("+");
			printline(ptr->data);
			ptr = ptr->next;
		}while(ptr != l2.rear);
	}
	
	else{
		for(i = 0; i < k3; i++){
			if(i != 0){
				for(j = ltr->previous->line1 + 1; j < ltr->line1; j++){
					printf("-");
					printline(ptr->data);
					ptr = ptr->next;
				}
				for(j = ltr->previous->line2 + 1; j < ltr->line2; j ++){
					printf("+");
					printline(qtr->data);
					qtr = qtr->next;
				}
			}
			else{
				for(j = 1; j < ltr->line1; j++){
					printf("-");
					printline(ptr->data);
					ptr = ptr->next;
				}
				for(j = 1; j < ltr->line2; j ++){
					printf("+");
					printline(qtr->data);
					qtr = qtr->next;
				}
			}
			printf(" ");
			printline(ltr->data);
			ltr = ltr->next;
			ptr = ptr->next;
			qtr = qtr->next;
		}
		if(ptr != l1.rear){
			while(ptr != l1.rear){
				printf("-");
				printline(ptr->data);
				ptr = ptr->next;
			}
		}
		if(qtr != l2.rear){
			while(qtr != l2.rear){
				printf("+");
				printline(qtr->data);
				qtr = qtr->next;
			}
		}
			
	}
}



