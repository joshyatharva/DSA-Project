#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "list.h"

int countlines(int fd) {
	int count = 0;
	char ch;
	while(read(fd, &ch, 1)) {
		if(ch == '\n')
			count++;
	}
	return count;
}
char *readline(int fd, int flag_w) {
	char ch;
	int i = 0;
	char *s = (char *)malloc(sizeof(char)*1000);
	while(read(fd, &ch, 1)) {
		if(flag_w == 1) {
			if(ch != '\n')
				if(ch != ' ' && ch != 9)
					s[i++] = ch;
				else
					continue;
			else {
				s[i++] = '\0';
				break;
			}
		}
		else {
			if(ch != '\n')
				s[i++] = ch;
			else {
				s[i++] = '\0';
				break;
			}
		
		}
	}
	return s;
}

