/*Give two file names as arguments*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include "list.h"
#include "file.h"
#include <sys/stat.h>





int main(int argc, char* argv[]){
	list l1, l2;
	list_lcs l;
	init(&l1);
	init(&l2);
	init_lcs(&l);
	char ch;
	int fd1, fd2, j = 0, k1 = 0, k2 = 0;
	char *line;
	line = (char *)malloc(sizeof(char) * 1000);	
	int x;
	int len1, len2, fd[5];
    char st[5][100];
    int  flag_c = 0, flag_t = 0, flag_w = 0, flag_b = 0, flag_i = 0, i, flag_u = 0, flag_y = 0;
    int opt;
    int error = 0;
    while((opt = getopt(argc, argv, ":yctwbiu")) != -1) {
    	switch(opt) {
    		case 'y':
    			flag_y = 1;
    			break;
    		case 'c':
    			flag_c = 1;
    			break;
    		
    		case 't':
    			flag_t = 1;
    			break;
    			
    		case 'w':
    			flag_w = 1;
    			break;
    			
    		case 'b':
    			flag_b = 1;
    			break;
    			
    		case 'i':
    			flag_i = 1;
    			break;
    			
			case 'u':
				flag_u = 1;
				break;
			
			default:
				error = 1;
				break;
    	}
    }
	if(error){
		printf("Invalid options\n");
		return 0;
	}

	if(optind == argc) /*sanity check*/ {
		printf("Insufficient arguments : ");
		exit(0);
	}
	if(argc < 3 || argc > 4){
		if(argc < 3)
			printf("Less arguments\n");
		else
			printf("Too much arguments\n");
		
		exit(0);
	}
	/*printf("argv[0] = %s\n", argv[0]);
	printf("argv[1] = %s\n", argv[1]);
	printf("argv[2] = %s\n", argv[2]);*/
	
	/*if(argc == 3)
		ch = '0';
		
	else
		ch = argv[1][1]; // e.g. c for -c*/
	int k = 0;
	for(i = optind; i < argc; i++) {
		fd[k++] = open(argv[i], O_RDONLY, S_IRUSR);
	}
	//if(argc == 3)
		//fd1 = open(argv[1], O_RDONLY, S_IRUSR);
	
	//else
		//fd1 = open(argv[2], O_RDONLY, S_IRUSR);
	
	if(fd[0] == -1){
		printf("First file not opened\n");
		exit(0);
	}
	x = countlines(fd[0]);
	k1 = x;
	if(x == 0)		
		l1.front = l1.rear = NULL;
	else{	
		lseek(fd[0], SEEK_SET, 0);
		while(x){
			line = readline(fd[0], 0);
			addnode(&l1, line);
			x--;
		}
	}
	close(fd[0]);
	
	//if(argc == 3)
		//fd[1] = open(argv[2], O_RDONLY, S_IRUSR);
	
	//else
		//fd2 = open(argv[3], O_RDONLY, S_IRUSR);
	
	if(fd[1] == -1){
		printf("Second file not opened\n");
		exit(0);
	}
	x = countlines(fd[1]);
	k2 = x;
	if(x == 0)
		l2.front = l2.rear = NULL;
	else{	
		lseek(fd[1], SEEK_SET, 0);
		while(x){
			line = readline(fd[1], 0);
			addnode(&l2, line);	
			x--;
		}
	}
	close(fd[1]);
	//if(k1 != 0 && k2 != 0)
	//l = lcs(l1, l2, ch);
	if(flag_c == 1){
		l = lcs(l1, l2, 'c');
		_cdiff(l, l1, l2);
	}
	else if(flag_y == 1){
		l = lcs(l1, l2, 'y');
		_ydiff(l, l1, l2);
	}
	else if(flag_u){
		l = lcs(l1, l2, 'u');
		_udiff(l, l1, l2);
	}
	else if(flag_i || flag_w || flag_b ){
		if(flag_i == 1)
			ch = 'i';
		else if(flag_w == 1)
			ch = 'w';
		else
			ch = 'b';
		l = lcs(l1, l2, ch);
		getdiff(l, l1, l2);
	}
	else{
		l = lcs(l1, l2, '0');
		getdiff(l, l1, l2);
	}
		
			//if(ch == 'u')
		//_udiff(l, l1, l2);
	//while((opt = getopt(argc, )))
	/*if(argc == 3){
		getdiff(l, l1, l2);
	}*/
	/*else{
		if(ch == 'c')
			_cdiff(l, l1, l2);
		if(ch == 'y')
			_ydiff(l, l1, l2);
		if(ch == 'i' || ch == 'w' || ch == 'b')
			getdiff(l, l1, l2);
		if(ch == 'u')
			_udiff(l, l1, l2);
	}*/
	/*printlist_lcs(l);
	printf("\n\n");
	l = lcs(l2, l1);
	printlist_lcs(l);
	*/
	//k1 = length(l1);
	//k2 = length(l2);
	//getdiff(l, l1, l2);
	//_cdiff(l, l1, l2);
	//_ydiff(l, l1, l2);	
		return 0;
}
