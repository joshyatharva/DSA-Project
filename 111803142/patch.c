#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "list.h"
#include "file.h"

#include <sys/stat.h>
#include <sys/types.h>

#include <limits.h>

#define OPERAND 100
#define OPERATOR 200
#define ERROR 300
#define END 400

#define OPERAND 100
#define OPERATOR 200
#define ERROR 300
#define END 400

typedef struct token{
	int type;
	union data{
		int num;
		char op;
	}data;
}token;

enum states{START, DIG, OP, COMMA, ERR, STOP};

token getnext(char *str){
		token t;
		int no = 0;
		static int currstate = START, nextstate = START, i = 0;
		static char currchar;	
		while(1){
			currchar = str[i];
			switch(currstate){
			case START :
				switch(currchar){
					case '0' : case '1' : case '2' : case '3' : 
					case '4' : case '5' : case '6' : case '7' : 
					case '8' : case '9' :
						nextstate = DIG;
						break;
					
					case ',' :
						nextstate = ERR;
						break;
						
					case 'a' : case 'd' : case 'c' :
						nextstate = ERR;
						break;
						
					default :
						nextstate = ERR;
						break;
				}
				currstate = nextstate;
				break;
			case DIG :
				switch(currchar){
					case '0' : case '1' : case '2' : case '3' : 
					case '4' : case '5' : case '6' : case '7' : 
					case '8' : case '9' :
						nextstate = DIG;
						no = no * 10 + (currchar - '0');
						i++;
						nextstate = DIG;
						break;
					
					case ',' :
						t.type = OPERAND;
						t.data.num = no;
						nextstate = COMMA;
						i++;
						currstate = nextstate;
						return t;
						break;
						
					case 'a' : case 'd' : case 'c' :
						t.type = OPERAND;
						t.data.num = no;
						nextstate = OP;
						currstate = nextstate;
						return t;
						break;
					
					case '\0' :
						nextstate = STOP;
						break;
						
					default :
						nextstate = ERR;
						break;
				}
				currstate = nextstate;
				break;
				
			case OP :
				switch(currchar){
					case '0' : case '1' : case '2' : case '3' : 
					case '4' : case '5' : case '6' : case '7' : 
					case '8' : case '9' :
						nextstate = DIG;
						break;
					
					case ',' :
						nextstate = ERR;
						break;
						
					case 'a' : case 'd' : case 'c' :
						t.type = OPERATOR;
						t.data.op = currchar;
						nextstate = OP;
						currstate = nextstate;
						i++;
						return t;
						break;
					
					default :
						nextstate = ERR;
						break;
				}
				currstate = nextstate;
				break;
			case COMMA :
				switch(currchar){
					case '0' : case '1' : case '2' : case '3' : 
					case '4' : case '5' : case '6' : case '7' : 
					case '8' : case '9' :
						nextstate = DIG;
						break;
					
					case ',' :
						nextstate = ERR;
						break;
						
					case 'a' : case 'd' : case 'c' :
						nextstate = ERR;
						break;
					
					default :
						nextstate = ERR;
						break;
				}
				currstate = nextstate;
				break;
				
			case STOP :
					t.type = END;
					t.data.num = no;
					currstate = START;
					nextstate = START;
					i = 0;
					return t;
			break;
			
			case ERR :
				t.type = ERROR;
				t.data.num = INT_MIN;
				currstate = START;
				nextstate = START;
				i = 0;
				return t;
			break;
			
			default :
				nextstate = ERR;
				currstate = nextstate;
			break;									
	}
	}
}

int main(int argc, char *argv[]){
	int fd1, fd2, x, k = 0, j = 0, i = 0, f[4];
	short flag = 0, flag1 = 0;
	token t;
	list l1, l2, l3;
	init(&l1);
	init(&l2);
	init(&l3);
	node *ptr;
	char *line;
	line = (char *)malloc(sizeof(char) * 1000);

		
	if(argc < 3){
		printf("Less arguments\n");
		exit(0);
	}
	
	fd1 = open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);
	if(fd1 == -1){
		printf("%s not opened\n", argv[2]);
	}	
	
	x = countlines(fd1);
	lseek(fd1, SEEK_SET, 0);
	while(x){
		line = readline(fd1, 0);
		addnode(&l1, line);
		x--;
	}
	
	close(fd1);
	ptr = l1.rear;	
	fd2 = open(argv[2], O_RDONLY, S_IRUSR);
	if(fd2 == -1){
		printf("%s not opened\n", argv[1]);
	}
	
	ptr = l1.rear;
	x = countlines(fd2);
	lseek(fd2, SEEK_SET, 0);

	while(x){

		line = readline(fd2, 0);
		if(line[0] == '<'){
			x--;
			continue;
		}
		else if(line[0] == '>'){
			addnode(&l3, &line[2]);
		}
		else if(line[0] == '-'){
			if(strcmp(line, "---") != 0){
				exit(0);
			}
		}
		else{
			i = 0;
			while(1){
				t = getnext(line);
				if(t.type == END){
					f[i] = t.data.num;
					if(i == 2)
						f[3] = f[2];
					break;
				}
				if(t.type == ERROR){
					exit(0);
					break;
				}
				else{
					if(t.type == OPERAND){
						f[i] = t.data.num;
					}
					if(t.type == OPERATOR){
						if(i == 2)
							continue;
						else
							f[i] = f[i-1];
					}		
				}
				i ++;
			}			
			k = f[1] - f[0];
			j = f[2] - f[3];
			
			if(ptr->line < f[0]){
				while(ptr->line != f[0]){
					addnode(&l3, ptr->data);
					ptr = ptr->next;	
				}
			}
			if(f[0] != 0)
				for(i = 0; i <= k; i ++)  
					ptr = ptr->next;
			
		}
		x --;
		}
	close(fd2);
	if(ptr != l1.rear){
		while(ptr != l1.rear){
			addnode(&l3, ptr->data);
			ptr = ptr->next;
		}
	}
	
	FILE *fp = fopen(argv[1], "w");
	ptr = l3.rear;
	
	if(l3.rear != NULL){
		do{
			fprintf(fp, "%s", ptr->data);
			fprintf(fp, "\n");
			ptr = ptr->next;
		}while(ptr != l3.rear);
	}
	fclose(fp);			
	return 0;
}	

